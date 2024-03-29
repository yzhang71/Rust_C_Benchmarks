pub fn knuth_morris_pratt(st: String, pat: String) -> Vec<usize> {
    let string = st.as_bytes().to_vec();
    let pattern = pat.as_bytes().to_vec();

    // build the partial match table
    let mut partial = vec![0];
    for i in 1..pattern.len() {
        let mut j = partial[i - 1];
        while j > 0 && pattern[j] != pattern[i] {
            j = partial[j - 1];
        }
        partial.push(if pattern[j] == pattern[i] { j + 1 } else { j });
    }

    // and read 'string' to find 'pattern'
    let mut ret = vec![];
    let mut j = 0;
    let mut i = 0;

    for c in string {
        while j > 0 && c != pattern[j] {
            j = partial[j - 1];
        }
        if c == pattern[j] {
            j += 1;
        }
        if j == pattern.len() {
            ret.push(i + 1 - j);
            j = partial[j - 1];
        }
        i += 1;
    }

    ret
}
use std::time::{Duration, Instant}; 
fn main() {
    let start = Instant::now();

    for i in 0..10000000 {
        knuth_morris_pratt("dcpaabtaadaaciaaacdaadrtvaavhaauaalziaastaanfqaaagaaavaaypaalnmaaovaauaaawlaalcaaczaadvaaheaaoaapmaaspaaabaabaaaaa".to_string(), "aa".to_string());

    }
    let duration = start.elapsed();

    println!("Time elapsed is: {:?}", duration);
}

