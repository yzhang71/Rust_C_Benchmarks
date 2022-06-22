# Finding 1

## Overview
Rust uses saturating floating-point to integer conversions for type casting, which is conservative but incurs extra run-time overheads.

## Build and run benchmarks from source code
Take "comb sort" as an example.

### Rust version
```
$ rustc -C opt-level=3 -C overflow_checks=no comb_sort.rs -o comb_sort-Rust
$ time ./comb_sort-Rust < input
```

