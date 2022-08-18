
pub fn selection_sort<T: Ord>(arr: &mut [T]) {
    let len = arr.len();
    for left in 0..len {
        let mut smallest = left;
        for right in (left + 1)..len {
            if arr[right] < arr[smallest] {
                smallest = right;
            }
        }
        arr.swap(smallest, left);
    }
}           

use std::io::{self, BufRead}; 
use std::time::{Duration, Instant};  
fn main() {
    let reader = io::stdin();
    let mut arr: Vec<i32> = 
        reader.lock()
              .lines().next().unwrap().unwrap()
              .trim().split(' ')
              .map(|s| s.parse().unwrap())
              .collect();
    let start = Instant::now();
    for i in 0..1000000 {
        selection_sort(&mut arr);
    }
    let duration = start.elapsed();

    println!("Time elapsed is: {:?}", duration);
}



