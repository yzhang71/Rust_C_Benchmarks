pub fn hamming_distance(string1: &str, string2: &str) -> usize {
    let mut distance = 0;
    let mut i = 0;
    let string1: Vec<_> = string1.chars().collect();
    let string2: Vec<_> = string2.chars().collect();

    while i < string1.len() {
        if string1[i] != string2[i] {
            distance += 1;
        }
        i += 1;
    }
    return distance;
}

fn main() {
    for i in 0..10000000 {
        hamming_distance("geekspracticehguisdhgiiuweyriuwehiiuweyriuwehfwebfuwebguyuheruihgvuyebghuiiuweyriuwehfwebfuwebguyuheruihgvuyebghuyveuyrghfiuhwueyveuyrghfiuhwuefwebfuwebguyuheruiiuweyriuwehfwebfuwebguyuheruihgvuyebghuyveuyrghfiuhwueihgvuyebghuyveuyrghfiuhwueihfiiuweyriuwehfwebfuwebguyuheruihgvuyebghuyveuyrghfiuhwueiwuehuyfgbwuybfviyuwehbiufh", "nerdspractiseeruhfiuerhgbgtreughiuewriiuweyriuwehfwebfuwebguyiiuweyriuwehfwebfuwebguyuheruihgvuyebghuyveuyrghfiuhwueuheruihgvuyebghuyveuyrghfiuhwuehfiuwiiuweyriuwehfwebfuwebguyuheruihgvuyebghuyveuyrghfiuhwueehfuibuyweiiuweyriuwehfwebfuwebguyuheruihgvuyebghuyveuyrghfiuhwuebiughneruijhfoweifjwoeijguibhniurteboehjoirwhjeoifhoou");

    }
}

