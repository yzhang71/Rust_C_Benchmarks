pub fn binary_search(k: i32, items: &mut Vec<i32>) -> usize {
    let mut low = 0;
    let mut high = items.len() - 1;

    while low <= high {
        let middle = ((high + low) / 2) as usize;
        if let current = items[middle] {
            if current == k {
                return middle;
            }
            if current > k {
                high = middle - 1
            }
            if current < k {
                low = middle + 1
            }
        }
    }
    1
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
    let mut cnt = 0;
    for i in 0..300000000 {
        cnt = binary_search(284, &mut arr);
    }
}

