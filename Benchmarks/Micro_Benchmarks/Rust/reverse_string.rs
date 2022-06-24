pub fn reverse(text: &mut str) {
    let mut i = 0;
    let mut j = text.len() - 1;
    let mut chars: Vec<_> = text.chars().collect();

    while i < j {
        chars.swap(i, j);
        i = i + 1;
        j = j - 1;
    }
}

use std::io::stdin;

fn main() {
    //Declare a mutable input string
    let mut input_string = String::new();
    stdin().read_line(&mut input_string)
        .ok()
        .expect("");
    for i in 0..100000000 {
        reverse(&mut input_string);
    }
}

