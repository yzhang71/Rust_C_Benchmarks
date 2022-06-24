pub fn comb_sort(arr: &mut Vec<i32>) {
    let mut gap = arr.len();
    let shrink = 2.0;
    let mut sorted = false;

    while !sorted {
        gap = (gap as f32 / shrink).floor() as usize;
        if gap <= 1 {
            gap = 1;
            sorted = true;
        }
        for i in 0..arr.len() - gap {
            let j = i + gap;
            if arr[i] > arr[j] {
                arr.swap(i, j);
                sorted = false;
            }
        }
    }
}

use std::io::{self, BufRead};  
fn main() {
    let reader = io::stdin();
    let mut arr: Vec<i32> = 
        reader.lock()
              .lines().next().unwrap().unwrap()
              .trim().split(' ')
              .map(|s| s.parse().unwrap())
              .collect();
    for i in 0..10000000 {
        comb_sort(&mut arr);
    }
}

