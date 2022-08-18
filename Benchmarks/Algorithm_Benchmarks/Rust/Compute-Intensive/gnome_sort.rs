pub fn gnome_sort<T: PartialOrd>(s: &mut [T]) {
    let mut i = 0;
    while i < s.len() {
        if i == 0 || s[i - 1] < s[i] {
            i += 1;
        } else {
            s.swap(i - 1, i);
            i -= 1;
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
    for i in 0..30000000 {
        gnome_sort(&mut arr);
    }
    let duration = start.elapsed();

    println!("Time elapsed is: {:?}", duration);
}

