# Micro Benchmarks

## Overview
Intending to provide an as comprehensively as possible performance comparison between Rust and C, we collect 22 real-world, publicly available and famous algorithms implementation in both Rust version and C version for micro benchmarks.

## Build and run benchmarks from source code
Take "selection sort" as an example, you can follow the instructions to compile other algorithms.
### Rust version
```
$ rustc -C opt-level=3 -C overflow_checks=yes selection_sort.rs -o selection_sort-Rust
$ time ./selection_sort-Rust < input
```
### C version
```
$ clang -O3 selection_sort.c -o selection_sort-C
$ time ./selection_sort-C < input
```

