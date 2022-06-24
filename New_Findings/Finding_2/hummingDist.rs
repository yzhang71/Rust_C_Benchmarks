pub fn hamming_distance(string1: &Vec<char>, string2: &Vec<char>) -> usize {
    let mut distance = 0;
    let mut i = 0;

    while i < string1.len() {
        if string1[i] != string2[i] {
            distance += 1;
        }
        i += 1;
    }
    return distance;
}

use std::time::{Duration, Instant}; 
fn main() {
    let start = Instant::now();
    let a: Vec<_> = "geekspracticehguisdhgiiuweyriuwehiiuweyriuwehfwebfuwebguyuheruihgvuyebghuiiuweyriuwehfwebfuwebguyuheruihgvuyebghuyveuyrghfiuhwueyveuyrghfiuhwuefwebfuwebguyuheruiiuweyriuwehfwebfuwebguyuheruihgvuyebghuyveuyrghfiuhwueihgvuyebghuyveuyrghfiuhwueihfiiuweyriuwehfwebfuwebguyuheruihgvuyebghuyveuyrghfiuhwueiwuehuyfgbwuybfviyuwehbiufh".chars().collect();
    let b: Vec<_> = "nerdspractiseeruhfiuerhgbgtreughiuewriiuweyriuwehfwebfuwebguyiiuweyriuwehfwebfuwebguyuheruihgvuyebghuyveuyrghfiuhwueuheruihgvuyebghuyveuyrghfiuhwuehfiuwiiuweyriuwehfwebfuwebguyuheruihgvuyebghuyveuyrghfiuhwueehfuibuyweiiuweyriuwehfwebfuwebguyuheruihgvuyebghuyveuyrghfiuhwuebiughneruijhfoweifjwoeijguibhniurteboehjoirwhjeoifhoou".chars().collect();

    let mut result = 0;
    for i in 0..10000000 {
        result = hamming_distance(&a, &b);

    }
    println!("{:?}", result);
    let duration = start.elapsed();

    println!("Time elapsed is: {:?}", duration);
}

