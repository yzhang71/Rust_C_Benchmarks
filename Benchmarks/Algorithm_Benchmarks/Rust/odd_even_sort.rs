pub fn odd_even_sort(arr: &mut Vec<i32>) {
    let len = arr.len();
    if len == 0 {
        return;
    }

    let mut sorted = false;
    while !sorted {
        sorted = true;

        for i in (1..len - 1).step_by(2) {
            if arr[i] > arr[i + 1] {
                arr.swap(i, i + 1);
                sorted = false;
            }
        }

        for i in (0..len - 1).step_by(2) {
            if arr[i] > arr[i + 1] {
                arr.swap(i, i + 1);
                sorted = false;
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
    for i in 0..2000000 {
        odd_even_sort(&mut arr);
    }
    let duration = start.elapsed();

    println!("Time elapsed is: {:?}", duration);
}

