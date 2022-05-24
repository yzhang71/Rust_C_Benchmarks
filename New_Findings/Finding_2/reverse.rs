pub fn reverse(text: &mut Vec<char>) {
    let mut i = 0;
    let mut j = text.len() - 1;

    while i < j {
        text.swap(i, j);
        i = i + 1;
        j = j - 1;
    }
}

use std::io::{self, BufRead};

fn main() {
    let reader = io::stdin();
    let mut arr: Vec<char> = 
        reader.lock()
              .lines().next().unwrap().unwrap()
              .trim().split(' ')
              .map(|s| s.parse().unwrap())
              .collect();
    for i in 0..100000000 {
        reverse(&mut arr);
    }
}
