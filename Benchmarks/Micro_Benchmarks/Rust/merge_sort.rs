fn merge(ori: &mut [i32], copy: &mut [i32], low: usize, mid: usize, high: usize) {
    let mut x = low;
    let mut y = low;
    let mut z = mid + 1;
 
    while y <= mid && z <= high {
        if ori[y] < ori[z] {
            copy[x] = ori[y];
            x+=1;
            y+=1;
        } else {
            copy[x] = ori[z];
            x+=1;
            z+=1;
        }
    }
 
    while y <= mid {
        copy[x] = ori[y];
        x+=1;
        y+=1;
    }
 
    y = low;
    while y <= high {
        ori[y] = copy[y];
        y+=1;
    }
}

fn merge_sort(ori: &mut [i32], copy: &mut [i32], low: usize, high: usize) {
    if high == low {
        return;
    }
 
    let mut mid: usize = (low + (( high - low ) >> 1));
 
    merge_sort(ori, copy, low, mid);
    merge_sort(ori, copy, mid + 1, high);
    merge(ori, copy, low, mid, high);
 
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
    let mut copy: Vec<i32> = vec![0; 98];
    copy.clone_from_slice(&arr);

    for i in 0..1000000 {
        merge_sort(&mut arr,&mut copy,0,97);
    }
}

