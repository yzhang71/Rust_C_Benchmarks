pub fn reverse(chars: &mut Vec<_>, len: usize) {
    let mut i = 0;
    let mut j = len - 1;

    while i < j {
        chars.swap(i, j);
        i += 1;
        j -= 1;
    }
}

use std::io::stdin;
use std::time::Instant;

fn main() {
    let mut input_string = String::new();
    stdin().read_line(&mut input_string)
        .ok()
        .expect("");

    let len = input_string.len();
    let mut input_string: Vec<_> = input_string.chars().collect();

    let start = Instant::now();
    for _i in 0..100000000 {
        reverse(&mut input_string, len);
    }
    let duration = start.elapsed();

    println!("Time elapsed is: {:?}", duration);
}
