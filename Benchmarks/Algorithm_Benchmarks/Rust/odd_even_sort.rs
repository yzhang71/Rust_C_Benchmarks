pub fn odd_even_sort(arr: &mut Vec<i32>, len : usize) {
    let mut sorted = false;

    let mut i;
    let mut j;

    while !sorted {
        sorted = true;

        i = 1;
        j = 0;

        while i <= (len - 2) {
            if arr[i] > arr[i + 1] {
                arr.swap(i, i + 1);
                sorted = false;
            }
            i += 2;
        }
        while j <= (len - 2) {
            if arr[j] > arr[j + 1] {
                arr.swap(j, j + 1);
                sorted = false;
            }
            j += 2;
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
    let len = arr.len();
    for i in 0..2000000 {
        odd_even_sort(&mut arr, 1372);
    }
}

