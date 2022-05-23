//! Solves the rod-cutting problem
use std::cmp::max;

/// `rod_cut(p)` returns the maximum possible profit if a rod of length `n` = `p.len()`
/// is cut into up to `n` pieces, where the profit gained from each piece of length
/// `l` is determined by `p[l - 1]` and the total profit is the sum of the profit
/// gained from each piece.
///
/// # Arguments
///    - `p` - profit for rods of length 1 to n inclusive
///
/// # Complexity
///    - time complexity: O(n^2),
///    - space complexity: O(n^2),
///
/// where n is the length of `p`.
pub fn rod_cut(p: &mut Vec<i32>, n : usize) -> i32 {
    // f is the dynamic programming table
    let mut f = vec![0; n];

    for i in 0..n {
        let mut max_price = p[i];
        for j in 1..i {
            max_price = max(max_price, p[j - 1] + f[i - j]);
        }
        f[i] = max_price;
    }

    f[n - 1]

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
    let n = arr.len();
    for i in 0..3000000 {
        rod_cut(&mut arr, n);
    }
}

