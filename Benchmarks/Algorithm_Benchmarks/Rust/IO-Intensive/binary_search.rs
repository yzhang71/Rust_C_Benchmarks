pub fn binary_search(k: i32, items: &mut Vec<i32>) -> i32 {

    if items.len() == 0 {
        return 0;
    }

    let len_n: usize = items.len();
    let mut lo: isize = 0;
    let mut hi: isize = len_n as isize - 1;
    while lo <= hi {
        let mid = lo + (hi - lo) / 2;
        if items[mid as usize] == k {
            return mid as i32;
        }
        if items[mid as usize] > k {
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    -1
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
    let mut cnt = 0;
    let start = Instant::now();
    for i in 0..300000000 {
        cnt = binary_search(284, &mut arr);
    }
    let duration = start.elapsed();

    println!("Time elapsed is: {:?} {:?}", duration, cnt);
}

