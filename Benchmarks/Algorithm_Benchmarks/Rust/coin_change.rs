/// Coin change via Dynamic Programming

/// coin_change(coins, amount) returns the fewest number of coins that need to make up that amount.
/// If that amount of money cannot be made up by any combination of the coins, return `None`.
///
/// Arguments:
///     * `coins` - coins of different denominations
///     * `amount` - a total amount of money be made up.
/// Complexity
///     - time complexity: O(amount * coins.length),
///     - space complexity: O(amount),
pub fn coin_change(coins: &mut Vec<usize>, amount: usize) -> Option<usize> {
    let mut dp = vec![std::usize::MAX; amount + 1];
    dp[0] = 0;

    // Assume dp[i] is the fewest number of coins making up amount i,
    // then for every coin in coins, dp[i] = min(dp[i - coin] + 1).
    for i in 0..=amount {
        for j in 0..coins.len() {
            if i >= coins[j] && dp[i - coins[j]] != std::usize::MAX {
                dp[i] = dp[i].min(dp[i - coins[j]] + 1);
            }
        }
    }

    match dp[amount] {
        std::usize::MAX => None,
        _ => Some(dp[amount]),
    }
}

use std::io::{self, BufRead};  
use std::time::{Duration, Instant}; 
fn main() {
    let reader = io::stdin();
    let mut arr: Vec<usize> = 
        reader.lock()
              .lines().next().unwrap().unwrap()
              .trim().split(' ')
              .map(|s| s.parse().unwrap())
              .collect();
    let start = Instant::now();
    for i in 0..500 {
        coin_change(&mut arr, 98564);
    }
    let duration = start.elapsed();

    println!("Time elapsed is: {:?}", duration);
}
