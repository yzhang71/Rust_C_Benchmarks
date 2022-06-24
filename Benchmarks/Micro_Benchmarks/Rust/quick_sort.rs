fn quick_sort(param_int_array: &mut [i32], start: usize, end: usize) {
    if start >= end {
        return;
    }
    let pivot = partition(param_int_array, start, end);

    quick_sort(param_int_array, start, (pivot - 1) as usize);
    quick_sort(param_int_array, (pivot + 1) as usize, end);
}

fn partition(param_int_array: &mut [i32], start: usize, end: usize ) -> i32 {
    let mut pivot = param_int_array[end];

    let mut index = start;

    let mut i = start;
    while i < end {

        if param_int_array[i] < pivot {
            swap(param_int_array, i, index);
            index+=1;
        }

        i+=1;
    }
    swap(param_int_array, index, end);
    return index as i32;
}

fn swap(param_int_array: &mut [i32], i: usize, j: usize ) {
    let temp = param_int_array[i];
    param_int_array[i] = param_int_array[j];
    param_int_array[j] = temp;
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
    for i in 0..1000000 {
        quick_sort(&mut arr, 0, 97);
    }
}
