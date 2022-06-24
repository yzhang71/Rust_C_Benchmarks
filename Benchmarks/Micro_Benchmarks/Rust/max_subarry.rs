pub fn maximum_subarray(array: &[i32]) -> i32 {
    let mut dp = vec![0; 97];
    dp[0] = array[0];
    let mut result = dp[0];

    for i in 1..97 {
        if dp[i - 1] > 0 {
            dp[i] = dp[i - 1] + array[i];
        } else {
            dp[i] = array[i];
        }
        result = result.max(dp[i]);
    }

    result
}

use std::io::{self, BufRead};

fn main() {
    let reader = io::stdin();
    let arr: Vec<i32> = 
        reader.lock()
              .lines().next().unwrap().unwrap()
              .trim().split(' ')
              .map(|s| s.parse().unwrap())
              .collect();
    let mut c = 0;
    for i in 0..30000000 {
        c = maximum_subarray(&arr);
    }
    println!("{:?}", c);
}
