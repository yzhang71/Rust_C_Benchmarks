use std::cmp::min;

pub fn fibonacci_search(len: usize, item: i32, arr: Vec<i32>) -> usize {

    let mut start = -1;

    let mut f0 = 0;
    let mut f1 = 1;
    let mut f2 = 1;
    while f2 < len {
        f0 = f1;
        f1 = f2;
        f2 = f0 + f1;
    }
    while f2 > 1 {
        let index = min((f0 as isize + start) as usize, len - 1);
        if arr[index] < item {
            f2 = f0;
            f1 -= f0;
            f0 = f2 - f1;

        }
        else if arr[index] > item {
            f2 = f1;
            f1 = f0;
            f0 = f2 - f1;
            start = index as isize;
        }

        else {
            return index;
        }
    }
    if (f1 != 0) && (arr[len - 1] == item) {
        return len - 1;
    }
    return 0;
}

fn main() {
    for i in 0..200000000 {
        let index = fibonacci_search(97, 245, vec![371, 323, 241, 181, 90, 102, 11, 198, 20, 121, 441, 57, 225, 218, 284, 425, 223, 213, 158, 366, 637, 180, 520, 386, 641, 128, 77, 492, 71, 86, 279, 401, 476, 414, 444, 317, 39, 238, 375, 499, 236, 163, 546, 242, 402, 603, 614, 83, 541, 25, 72, 234, 140, 639, 248, 544, 96, 27, 66, 581, 273, 133, 190, 320, 721, 221, 361, 391, 145, 752, 472, 3, 447, 219, 161, 237, 718, 157, 184, 147, 247, 604, 587, 583, 405, 58, 346, 433, 172, 460, 62, 265, 92, 351, 122, 120, 114, 245]);
    }
}

