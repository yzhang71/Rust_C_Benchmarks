//! Solves the knapsack problem
use std::cmp::max;

/// knapsack_table(w, weights, values) returns the knapsack table (`n`, `m`) with maximum values, where `n` is number of items
///
/// Arguments:
///     * `w` - knapsack capacity
///     * `weights` - set of weights for each item
///     * `values` - set of values for each item
fn knapsack_table(w: &usize, weights: &[usize], values: &[usize]) -> Vec<Vec<usize>> {
    // Initialize `n` - number of items
    let n: usize = 15;
    // Initialize `m`
    // m[i, w] - the maximum value that can be attained with weight less that or equal to `w` using items up to `i`
    let mut m: Vec<Vec<usize>> = vec![vec![0; w + 1]; n + 1];

    for i in 0..n {
        for j in 0..*w {
            // m[i, j] compiled according to the following rule:
            if i == 0 || j == 0 {
                m[i][j] = 0;
            } else if weights[i - 1] <= j {
                // If `i` is in the knapsack
                // Then m[i, j] is equal to the maximum value of the knapsack,
                // where the weight `j` is reduced by the weight of the `i-th` item and the set of admissible items plus the value `k`
                m[i][j] = max(values[i - 1] + m[i - 1][j - weights[i - 1]], m[i - 1][j]);
            } else {
                // If the item `i` did not get into the knapsack
                // Then m[i, j] is equal to the maximum cost of a knapsack with the same capacity and a set of admissible items
                m[i][j] = m[i - 1][j]
            }
        }
    }
    m
}

/// knapsack(w, weights, values) returns the tuple where first value is `optimal profit`,
/// second value is `knapsack optimal weight` and the last value is `indices of items`, that we got (from 1 to `n`)
///
/// Arguments:
///     * `w` - knapsack capacity
///     * `weights` - set of weights for each item
///     * `values` - set of values for each item
///
/// Complexity
///     - time complexity: O(nw),
///     - space complexity: O(nw),
///
/// where `n` and `w` are `number of items` and `knapsack capacity`
pub fn knapsack(w: usize, weights: Vec<usize>, values: Vec<usize>) -> usize {
    let n: usize = 15;
    // Find the knapsack table
    let m: Vec<Vec<usize>> = knapsack_table(&w, &weights, &values);

    // Return result
    m[n][w]
}

fn main() {
    for i in 0..100000 {
        knapsack(
            750,
            vec![70, 73, 77, 80, 82, 87, 90, 94, 98, 106, 110, 113, 115, 118, 120],
            vec![135, 139, 149, 150, 156, 163, 173, 184, 192, 201, 210, 214, 221, 229, 240]
        );
    }
}
