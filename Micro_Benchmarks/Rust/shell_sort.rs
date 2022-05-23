pub fn shell_sort(arr: &mut Vec<i32>) {
    let len = arr.len();
    let mut gap = len as i32 / 2;

    while gap > 0 {
        for i in gap..len as i32 {
            let temp = arr[i as usize];
            let mut j = i;

            while j >= gap && arr[j as usize - gap as usize] > temp {
                arr.swap(j as usize, j as usize - gap as usize);
                j -= gap;
            }

            arr[j as usize] = temp;
        }
        gap /= 2;
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
    for i in 0..3000000 {
        shell_sort(&mut arr);
    }
}

