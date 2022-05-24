/// Longest common subsequence via Dynamic Programming

/// longest_common_subsequence(a, b) returns the longest common subsequence
pub fn longest_common_subsequence(a: &Vec<char>, b: &Vec<char>) {
    let (na, nb) = (1327, 1569);
    // solutions[i][j] is the length of the longest common subsequence
    // between a[0..i-1] and b[0..j-1]
    let mut solutions = vec![vec![0; nb + 1]; na + 1];

    for i in 0..na {
        for j in 0..nb {
            // if ci == cj, there is a new common character;
            // otherwise, take the best of the two solutions
            // at (i-1,j) and (i,j-1)
            solutions[i + 1][j + 1] = if a[i] == b[j] {
                solutions[i][j] + 1
            } else {
                solutions[i][j + 1].max(solutions[i + 1][j])
            }
        }
    }
    // reconstitute the solution string from the lengths
    let mut result: Vec<char> = Vec::new();
    let (mut i, mut j) = (na, nb);
    while i > 0 && j > 0 {
        if a[i - 1] == b[j - 1] {
            result.push(a[i - 1]);
            i -= 1;
            j -= 1;
        } else if solutions[i - 1][j] > solutions[i][j - 1] {
            i -= 1;
        } else {
            j -= 1;
        }
    }
}


fn main() {
    let a: Vec<_> = "dymhjvxkgqekugratdpdmyjeafehaclzogbzhnyosemfhxitehlisprghkdymhjvxkgqekugratdpdmyjeafehaclzogbzhnyosemfhxitehlisprghkdymhjvxkgqekugratdpdmyjeafehaclzogbzhnyosemfhxitehlisprghkdymhjvxkgqekugratdpdmyjeafehaclzogbzhnyosemfhxitehlisprghkdymhjvxkgqekugratdpdmyjeafehaclzogbzhnyosemfhxitehlisprghkdymhjvxkgqekugratdpdmyjeafehaclzogbzhnyosemfhxitehlisprghkdymhjvxkgqekugratdpdmyjeafehaclzogbzhnyosemfhxitehlisprghkdymhjvxkgqekugratdpdmyjeafehaclzogbzhnyosemfhxitehlisprghkdymhjvxkgqekugratdpdmyjeafehaclzogbzhnyosemfhxitehlisprghkdymhjvxkgqekugratdpdmyjeafehaclzogbzhnyosemfhxitehlisprghkdymhjvxkgqekugratdpdmyjeafehaclzogbzhnyosemfhxitehlisprghkdymhjvxkgqekugratdpdmyjeafehaclzogbzhnyosemfhxitehlisprghkdymhjvxkgqekugratdpdmyjeafehaclzogbzhnyosemfhxitehlisprghkdymhjvxkgqekugratdpdmyjeafehaclzogbzhnyosemfhxitehlisprghkdymhjvxkgqekugratdpdmyjeafehaclzogbzhnyosemfhxitehlisprghkdymhjvxkgqekugratdpdmyjeafehaclzogbzhnyosemfhxitehlisprghkdymhjvxkgqekugratdpdmyjeafehaclzogbzhnyosemfhxitehlisprghkdymhjvxkgqekugratdpdmyjeafehaclzogbzhnyosemfhxitehlisprghkdymhjvxkgqekugratdpdmyjeafehaclzogbzhnyosemfhxitehlisprghkdymhjvxkgqekugratdpdmyjeafehaclzogbzhnyosemfhxitehlisprghkdymhjvxkgqekugratdpdmyjeafehaclzogbzhnyosemfhxitehlisprghkdymhjvxkgqekugratdpdmyjeafehaclzogbzhnyosemfhxitehlisprghkdymhjvxkgqekugratdpdmyjeafehaclzogbzhnyosemfhxitehl".chars().collect();
    let b: Vec<_> = "rxywvzmgjisgfazeguickjelmgtlnmjstceivppxlybbqopxohjyonjntqgnahczyspsgrxywvzmgjisgfazeguickjelmgtlnmjstceivppxlybbqopxohjyonjntqgnahczyspsgrxywvzmgjisgfazeguickjelmgtlnmjstceivppxlybbqopxohjyonjntqgnahczyspsgrxywvzmgjisgfazeguickjelmgtlnmjstceivppxlybbqopxohjyonjntqgnahczyspsgrxywvzmgjisgfazeguickjelmgtlnmjstceivppxlybbqopxohjyonjntqgnahczyspsgrxywvzmgjisgfazeguickjelmgtlnmjstceivppxlybbqopxohjyonjntqgnahczyspsgrxywvzmgjisgfazeguickjelmgtlnmjstceivppxlybbqopxohjyonjntqgnahczyspsgrxywvzmgjisgfazeguickjelmgtlnmjstceivppxlybbqopxohjyonjntqgnahczyspsgrxywvzmgjisgfazeguickjelmgtlnmjstceivppxlybbqopxohjyonjntqgnahczyspsgrxywvzmgjisgfazeguickjelmgtlnmjstceivppxlybbqopxohjyonjntqgnahczyspsgrxywvzmgjisgfazeguickjelmgtlnmjstceivppxlybbqopxohjyonjntqgnahczyspsgrxywvzmgjisgfazeguickjelmgtlnmjstceivppxlybbqopxohjyonjntqgnahczyspsgrxywvzmgjisgfazeguickjelmgtlnmjstceivppxlybbqopxohjyonjntqgnahczyspsgrxywvzmgjisgfazeguickjelmgtlnmjstceivppxlybbqopxohjyonjntqgnahczyspsgrxywvzmgjisgfazeguickjelmgtlnmjstceivppxlybbqopxohjyonjntqgnahczyspsgrxywvzmgjisgfazeguickjelmgtlnmjstceivppxlybbqopxohjyonjntqgnahczyspsgrxywvzmgjisgfazeguickjelmgtlnmjstceivppxlybbqopxohjyonjntqgnahczyspsgrxywvzmgjisgfazeguickjelmgtlnmjstceivppxlybbqopxohjyonjntqgnahczyspsgrxywvzmgjisgfazeguickjelmgtlnmjstceivppxlybbqopxohjyonjntqgnahczyspsgrxywvzmgjisgfazeguickjelmgtlnmjstceivppxlybbqopxohjyonjntqgnahczyspsgrxywvzmgjisgfazeguickjelmgtlnmjstceivppxlybbqopxohjyonjntqgnahczyspsgrxywvzmgjisgfazeguickjelmgtlnmjstceivppxlybbqopxohjyonjntqgnahczyspsgrxywvzmgjisgfazeguickjelmgtlnmjstceivppxlybbqopxohj".chars().collect();
    for i in 0..500 {
        longest_common_subsequence(&a, &b);
    }
}

