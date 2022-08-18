pub fn bubble_sort<T: Ord>(arr: &mut [T]) {
    for i in 0..arr.len() {
        for j in 0..arr.len() - 1 - i {
            if arr[j] > arr[j + 1] {
                arr.swap(j, j + 1);
            }
        }
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
        bubble_sort(&mut arr);
    }
    let duration = start.elapsed();

    println!("Time elapsed is: {:?}", duration);
}

