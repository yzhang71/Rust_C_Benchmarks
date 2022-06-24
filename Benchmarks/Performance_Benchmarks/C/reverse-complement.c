#define COMPLEMENT_LOOKUP \
  "          \n                                                     "\
  /*ABCDEFGHIJ KLMNOPQRSTUVWXYZ      abcdefghij klmnopqrstuvwxyz*/\
  " TVGH  CD \nM KN   YSAABW R       TVGH  CD \nM KN   YSAABW R"

// This controls the size of reads from the input and is also used as the
// initial sequence_Capacity.
#define READ_SIZE 65536

// This defines how many characters (including the newline) a full line of input
// should have.
#define LINE_LENGTH 61

// While reverse complementing a sequence, the sequence is broken up into chunks
// which can be processed in parallel on computers with multiple CPU cores.
// LINES_PER_CHUNK will set the maximum amount of lines that are allowed in each
// chunk and consequently the maximum size of each chunk will be equal to
// LINES_PER_CHUNK*LINE_LENGTH bytes in size. Each thread will create an array
// on the stack that is large enough to contain these chunks so LINES_PER_CHUNK
// must be set small enough to allow this array to fit inside the stack. For
// best performance, this value should probably be set so that the maximum chunk
// size is somewhere between the L1 data cache size and
// 1/(2*NUMBER_OF_CPU_CORES) of the last level cache size (assuming each CPU
// core has its own L1 cache and the last level cache is shared between CPU
// cores).
#define LINES_PER_CHUNK 8192

#include <stdint.h>
#include <pthread.h>
#include <semaphore.h>
#include <immintrin.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// uintptr_t should be the native integer type on most sane systems.
typedef uintptr_t uintnative_t;


// REVERSE_COMPLEMENT_LOOKUP will be used by the
// reverse_Complement_And_Move_Span() function to help speed up reverse
// complementing by allowing two characters to be reversed and complemented at
// once.
uint16_t REVERSE_COMPLEMENT_LOOKUP[65536];


// Since sequences can be broken up into chunks that can be processed in
// parallel by multiple threads, we need a few shared variables amongst the
// threads to coordinate the processing. shared_Variables_Mutex is used to make
// sure only one thread is reading/writing the other variables at a time.
// sequence_Characters_Left_To_Process is self explanatory. Processing of the
// sequence starts at the rear and proceeds to the header_Newline in front of
// the sequence, front_Character_Of_Last_Assigned_Chunk
// keeps track of this position
pthread_mutex_t shared_Variables_Mutex=PTHREAD_MUTEX_INITIALIZER;
uintnative_t sequence_Characters_Left_To_Process;
uint8_t * front_Character_Of_Last_Assigned_Chunk;
sem_t * semaphore_For_Signaling_Last_Assigned_Chunk_Written;


// Reverse complement and move a span of characters. The span to be reverse
// complemented ends just before character_After_Src_Rear_Character and the
// reverse complemented span is moved so that its first character will be at
// dst_Front_Character. The size of the spans is span_Length characters long.
void reverse_Complement_And_Move_Span(uint8_t * dst_Front_Character
  , uint8_t * character_After_Src_Rear_Character, uintnative_t span_Length){

  // The loops farther down below will simultaneously reverse complement and
  // move either sixteen or two characters so consequently they can only
  // properly handle even span_Lengths. If the span_Lengths are odd, then this
  // if block below will do a single preliminary complement and move to make
  // the remaining span_Lengths an even number that the last loop can handle.
  if(span_Length%2){
    *dst_Front_Character++
      =COMPLEMENT_LOOKUP[*--character_After_Src_Rear_Character];
    span_Length--;
  }


  // If this program is compiled for an architecture that supports SSE 4.1,
  // then this loop can use it to simultaneously reverse complement and move a
  // sixteen character subspan at a time if the span_Length is at least that
  // large.
  #ifdef __SSE4_1__
    for(; span_Length>=16; span_Length-=16, dst_Front_Character+=16){

      // Load the subspan before character_After_Src_Rear_Character.
      __m128i subspan=_mm_lddqu_si128(
        (__m128i *)(character_After_Src_Rear_Character-=16));


      // Reverse the subspan.
      subspan=_mm_shuffle_epi8(subspan,_mm_set_epi8(
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15));


      // AND all the characters in the subspan with 0b11111 which will
      // cause the values for the ASCII letters A to Z AND a to z to
      // change to 1 to 26. This allows a smaller lookup table to be used
      // which is useful here because we are going to be using 128 bit
      // (e.g. sixteen eight bit characters) SSE registers as lookup
      // tables which means we'll need to use at least two SSE registers,
      // do two lookups, and then select the appropriate result to use.
      // Larger lookup tables would require using more registers and doing
      // more lookups which will result in slower code.
      subspan=_mm_and_si128(subspan, _mm_set1_epi8(0b11111));


      // Now we load two sixteen character lookup tables into two SSE
      // registers, lookup each character of the subspan in both lookup
      // tables, and then figure out which lookup table has the correct
      // complement for the character based on whether the character's
      // lower five bits value was 0-15 or 16-31. Finally we write the
      // reverse complemented subspan to dst_Front_Character.
      //
      // Note that if the below lookup tables are changed, then the
      // COMPLEMENT_LOOKUP table up above should also be changed. It would
      // also be a good idea to read the comment above the
      // COMPLEMENT_LOOKUP table for why there is a newline in this lookup
      // table and why it is set as the complement of the letter J.
      __m128i complements_For_0_To_15_Values
        =_mm_shuffle_epi8(_mm_setr_epi8(
        //      A    B    C    D    E    F    G
           0 , 'T', 'V', 'G', 'H',  0 ,  0 , 'C'
        // H    I    J    K    L    M    N    O
        , 'D',  0 ,'\n', 'M',  0 , 'K', 'N',  0), subspan);
      __m128i complements_For_16_To_31_Values
        =_mm_shuffle_epi8(_mm_setr_epi8(
        // P    Q    R    S    T    U    V    W
           0 ,  0 , 'Y', 'S', 'A', 'A', 'B', 'W'
        // X    Y    Z
        ,  0 , 'R',  0 ,  0 ,  0 ,  0 ,  0 ,  0), subspan);
      __m128i mask_To_Select_complements_For_16_To_31_Values
        =_mm_cmpgt_epi8(subspan, _mm_set1_epi8(15));
      _mm_storeu_si128((__m128i *)dst_Front_Character
        , _mm_blendv_epi8(complements_For_0_To_15_Values
        , complements_For_16_To_31_Values
        , mask_To_Select_complements_For_16_To_31_Values));
    }
  #endif


  // Reverse complement and move any remaining characters and use the
  // REVERSE_COMPLEMENT_LOOKUP table that was set up during startup to allow
  // us to reverse complement two characters at a time. This is faster than
  // just complementing and moving one character at a time and at least for
  // some older architectures it isn't much slower than using the more complex
  // SSE code above, this can really help out when compiling for architectures
  // that don't support SSE 4.1.
  for(; span_Length>=2; span_Length-=2, dst_Front_Character+=2)
    *(uint16_t *)dst_Front_Character=REVERSE_COMPLEMENT_LOOKUP[
      *(uint16_t *)(character_After_Src_Rear_Character-=2)];
}


// Look for chunks to reverse complement and reverse complement and write them
// in order until there are no more sequence_Characters_Left_To_Process.
void * write_Reverse_Complements_Of_Chunks(
  void * initial_Semaphore_For_Signaling_Chunk_Written){

  sem_t * semaphore_For_Signaling_Chunk_Written
    =initial_Semaphore_For_Signaling_Chunk_Written;

  // Instead of doing an in-place reverse complement of the sequence, we
  // instead write the reverse complement of a smaller chunk to chunk_To_Write
  // and then we write chunk_To_Write after we finish reverse complementing
  // the chunk and all prior chunks have been written. By writing/reading to/
  // from chunk_To_Write, which should be mostly cached, we avoid having to
  // do another write/read of the entire sequence to/from main memory.
  uint8_t chunk_To_Write[LINES_PER_CHUNK*LINE_LENGTH];


  // Keep reverse complementing and writing chunks until there are no
  // sequence_Characters_Left_To_Process.
  for(;;){

    pthread_mutex_lock(&shared_Variables_Mutex);

      // full_Line_Front_Span_Length is the number of nucleobases that
      // show up on the last line of the chunk (and also the sequence).
      // If the last line of the chunk is a non-full line, then
      // full_Line_Rear_Span_Length is the number of nucleobases that
      // would be required to be added to make it a full line, otherwise
      // it will be zero if the last line is a full line.
      uintnative_t full_Line_Front_Span_Length
        =(sequence_Characters_Left_To_Process-1)%LINE_LENGTH;
      uintnative_t full_Line_Rear_Span_Length
        =LINE_LENGTH-1-full_Line_Front_Span_Length;

      // Determine the chunk_Size we should use and the number of
      // chunk_Characters_Left_To_Process. If there are no
      // chunk_Characters_Left_To_Process, then exit the thread. Also
      // update sequence_Characters_Left_To_Process so that the next
      // thread looking for a chunk to work on knows the number of
      // sequence_Characters_Left_To_Process.
      uintnative_t chunk_Size
        =sequence_Characters_Left_To_Process>LINES_PER_CHUNK*LINE_LENGTH
        ? LINES_PER_CHUNK*LINE_LENGTH
        : sequence_Characters_Left_To_Process;
      uintnative_t chunk_Characters_Left_To_Process=chunk_Size;
      if(!chunk_Characters_Left_To_Process){
        pthread_mutex_unlock(&shared_Variables_Mutex);
        return NULL;
      }
      sequence_Characters_Left_To_Process-=chunk_Size;

      // Get a copy of the front_Character_Of_Last_Assigned_Chunk that we
      // can use to keep track of the last_Processed_Chunk_Character. Also
      // decrement front_Character_Of_Last_Assigned_Chunk by our
      // chunk_Size so that the next thread looking for a chunk to work on
      // will know to continue working from the front of our chunk.
      uint8_t * last_Processed_Chunk_Character
        =front_Character_Of_Last_Assigned_Chunk;
      front_Character_Of_Last_Assigned_Chunk-=chunk_Size;

      // Get a copy of semaphore_For_Signaling_Last_Assigned_Chunk_Written
      // so that we know what semaphore_To_Wait_On_Before_Writing_Chunk.
      // Also set semaphore_For_Signaling_Last_Assigned_Chunk_Written to
      // our semaphore_For_Signaling_Chunk_Written so that the next thread
      // looking for a chunk to work on knows what semaphore it should
      // wait on before writing another chunk.
      sem_t * semaphore_To_Wait_On_Before_Writing_Chunk
        =semaphore_For_Signaling_Last_Assigned_Chunk_Written;
      semaphore_For_Signaling_Last_Assigned_Chunk_Written
        =semaphore_For_Signaling_Chunk_Written;

    pthread_mutex_unlock(&shared_Variables_Mutex);

    uint8_t * chunk_Pos=chunk_To_Write;


    // We now have all information we need to know and can start reverse
    // complementing our chunk.

    // First we check to see if we have an optimal size sequence that
    // entirely consists of full lines (which will be the case when
    // full_Line_Rear_Span_Length is zero). In this case we can just make a
    // single call to reverse_Complement_And_Move_Span() and have it reverse
    // complement the entire chunk. This does require the
    // reverse_Complement_And_Move_Span() function to leave newlines
    // unchanged when they are complemented though.
    if(!full_Line_Rear_Span_Length){
      reverse_Complement_And_Move_Span(chunk_Pos
        , last_Processed_Chunk_Character
        , chunk_Characters_Left_To_Process);
      chunk_Characters_Left_To_Process=0;
    }


    // This loop reverse complements and moves full lines and also knows how
    // to skip over newlines as needed and then reinsert them at the
    // appropriate positions. This loop does most of the reverse
    // complementing work.
    for(; chunk_Characters_Left_To_Process>=LINE_LENGTH
      ; chunk_Characters_Left_To_Process-=LINE_LENGTH){

      // Reverse complement and move a full_Line_Front_Span_Length of
      // nucleobases ending in front of the last_Processed_Chunk_Character
      // to chunk_Pos (which will now be pointing at the postion for the
      // first nucleobase of a line). Then chunk_Pos and
      // last_Processed_Chunk_Character are incremented/decremented
      // respectively by full_Line_Front_Span_Length and
      // last_Processed_Chunk_Character is decremented by one more to skip
      // over the newline in the preceding line.
      reverse_Complement_And_Move_Span(chunk_Pos
        , last_Processed_Chunk_Character
        , full_Line_Front_Span_Length);
      chunk_Pos+=full_Line_Front_Span_Length;
      last_Processed_Chunk_Character-=full_Line_Front_Span_Length+1;

      // Reverse complement and move a full_Line_Rear_Span_Length of
      // nucleobases ending in front of the last_Processed_Chunk_Character
      // (which will now be pointing at the newline after the last
      // nucleobase of a line) to chunk_Pos. Then chunk_Pos and
      // last_Processed_Chunk_Character are incremented/decremented
      // respectively by full_Line_Rear_Span_Length.
      reverse_Complement_And_Move_Span(chunk_Pos
        , last_Processed_Chunk_Character
        , full_Line_Rear_Span_Length);
      chunk_Pos+=full_Line_Rear_Span_Length;
      last_Processed_Chunk_Character-=full_Line_Rear_Span_Length;

      // Finally insert a newline at chunk_Pos and increment it because of
      // the newline.
      *chunk_Pos++='\n';
    }


    // If chunk_Size isn't evenly divisible by LINE_LENGTH, then there will
    // be one last partial line of chunk_Characters_Left_To_Process and the
    // line will contain a full_Line_Front_Span_Length of nucelobases plus a
    // preceding newline. Reverse complement and move that partial line here
    // if necessary.
    if(chunk_Characters_Left_To_Process)
      reverse_Complement_And_Move_Span(chunk_Pos
        , last_Processed_Chunk_Character
        , full_Line_Front_Span_Length+1);


    // Before we can write the chunk_To_Write that we just finished reverse
    // complementing, we need to wait for a signal from the
    // semaphore_To_Wait_On_Before_Writing_Chunk so that we know the
    // previous chunk (and all prior chunks) have been written first. Once
    // that happens we can then write the chunk_To_Write. We then signal the
    // semaphore_For_Signaling_Chunk_Written so that the thread processing
    // the next chunk (if any) knows that it is OK for it to start writing.
    // Finally we need to leave the semaphore_For_Signaling_Chunk_Written
    // alone so that it can potentially be seen by another thread, we'll
    // change our semaphore_For_Signaling_Chunk_Written (for the next
    // potential chunk that this thread will process) to the now unused
    // semaphore_To_Wait_On_Before_Writing_Chunk.
    sem_wait(semaphore_To_Wait_On_Before_Writing_Chunk);
    (void)!write(STDOUT_FILENO, chunk_To_Write, chunk_Size);
    sem_post(semaphore_For_Signaling_Chunk_Written);
    semaphore_For_Signaling_Chunk_Written
      =semaphore_To_Wait_On_Before_Writing_Chunk;
  }
}


void write_Sequence_Reverse_Complement(uint8_t * sequence
  , uintnative_t sequence_Size){
  // sequence will point at the '>' in the header and sequence_Size is the
  // amount of characters including the '>' in the header and the last newline
  // of the sequence.

  uint8_t * header_Newline=memchr(sequence, '\n', sequence_Size);


  // Write the header line including the header_Newline.
  (void)!write(STDOUT_FILENO, sequence, header_Newline-sequence+1);


  // front_Character_Of_Last_Assigned_Chunk is initially set to point to the
  // last newline of the sequence (if the sequence was one chunk larger, this
  // is where the front of that chunk would have been).
  front_Character_Of_Last_Assigned_Chunk=sequence+sequence_Size-1;

  sequence_Characters_Left_To_Process
    =front_Character_Of_Last_Assigned_Chunk-header_Newline;


  // Figure out the number_Of_Threads_To_Use based on how many CPU cores are
  // available. Note that using sysconf(_SC_NPROCESSORS_ONLN) will return the
  // number of processors online on the system but not necessarily
  // available to the process (if something like taskset is used). Using
  // something like sched_getaffinity() with CPU_COUNT() would be more
  // accurate on systems like Linux but is less portable.
  uintnative_t number_Of_Threads_To_Use
    =(uintnative_t)labs(sysconf(_SC_NPROCESSORS_ONLN));

  pthread_t chunks_Processing_Threads[number_Of_Threads_To_Use];
  sem_t chunk_Written_Semaphores[number_Of_Threads_To_Use+1];

  // Initialize all the chunk_Written_Semaphores. Although no chunks have been
  // written yet, the thread processing the first chunk (if any) will expect
  // to see a chunk_Written_Semaphore signaling that all prior chunks have
  // been written. To meet its expectations we pretend that a prior chunk has
  // already been written by assigning the last chunk_Written_Semaphores to
  // semaphore_For_Signaling_Last_Assigned_Chunk_Written and initializing it
  // as already being signaled.
  for(uintnative_t i=number_Of_Threads_To_Use+1; i-->0;)
    sem_init(&chunk_Written_Semaphores[i], 0, i/number_Of_Threads_To_Use);
  semaphore_For_Signaling_Last_Assigned_Chunk_Written
    =&chunk_Written_Semaphores[number_Of_Threads_To_Use];

  // Create number_Of_Threads_To_Use chunks_Processing_Threads and have them
  // all write_Reverse_Complements_Of_Chunks.
  for(uintnative_t i=number_Of_Threads_To_Use; i-->0;)
    pthread_create(&chunks_Processing_Threads[i], NULL
      , write_Reverse_Complements_Of_Chunks, &chunk_Written_Semaphores[i]);

  // Wait for all the chunks_Processing_Threads to finish writing the reverse
  // complement of the sequence.
  for(uintnative_t i=number_Of_Threads_To_Use; i-->0;)
    pthread_join(chunks_Processing_Threads[i], NULL);

  // Destroy all the chunk_Written_Semaphores.
  for(uintnative_t i=number_Of_Threads_To_Use+1; i-->0;)
    sem_destroy(&chunk_Written_Semaphores[i]);
}


int main(void){

  // We initialize the REVERSE_COMPLEMENT_LOOKUP table here but only fill in
  // elements for characters that will be in the range of ASCII characters
  // that we can expect to see in inputted data.
  for(uintnative_t i='\n'; i<sizeof(COMPLEMENT_LOOKUP)-1; i++)
    for(uintnative_t j='\n'; j<sizeof(COMPLEMENT_LOOKUP)-1; j++)
      REVERSE_COMPLEMENT_LOOKUP[i<<8 | j]
        =(uint16_t)COMPLEMENT_LOOKUP[j]<<8
        | (uint16_t)COMPLEMENT_LOOKUP[i];


  // Allocate memory for the initial sequence (assuming there is one).
  uintnative_t sequence_Capacity=READ_SIZE, sequence_Size=0;
  uint8_t * sequence=malloc(sequence_Capacity);

  // Read in sequence data until we reach the end of the file or encounter an
  // error.
  for(uintnative_t bytes_Read
    ; (bytes_Read=read(STDIN_FILENO, &sequence[sequence_Size], READ_SIZE));){

    // Search the read in chunk of data for a '>' to see if any sequences
    // are being started.
    for(uint8_t * sequence_Start
      ; (sequence_Start=memchr(&sequence[sequence_Size], '>', bytes_Read))
      ;){

      // Update the sequence_Size to reflect any data before the '>' that
      // was read in.
      uintnative_t number_Of_Preceding_Bytes
        =sequence_Start-&sequence[sequence_Size];
      sequence_Size+=number_Of_Preceding_Bytes;


      // If there is any data for the current sequence, then process it
      // and update things for processing the next sequence.
      if(sequence_Size){

        // Process the current sequence.
        write_Sequence_Reverse_Complement(sequence, sequence_Size);

        // Copy the read-in '>' and any data following it to the front
        // of sequence.
        memmove(sequence, sequence_Start
          , bytes_Read-number_Of_Preceding_Bytes);

        // Reset sequence_Size to 0 as we start processing the next
        // sequence.
        sequence_Size=0;
      }


      // Update sequence_Size and bytes_Read to reflect the read in '>'
      // and any data that preceded it.
      sequence_Size++;
      bytes_Read-=number_Of_Preceding_Bytes+1;
    }


    // Update sequence_Size to reflect the bytes that were read in.
    sequence_Size+=bytes_Read;

    // If there potentially isn't enough free space for all the data from
    // the next read, then double the capacity of the sequence.
    if(sequence_Size>sequence_Capacity-READ_SIZE)
      sequence=realloc(sequence, sequence_Capacity*=2);
  }


  // If there is any data for a last sequence, process it.
  if(sequence_Size)
    write_Sequence_Reverse_Complement(sequence, sequence_Size);

  free(sequence);
}