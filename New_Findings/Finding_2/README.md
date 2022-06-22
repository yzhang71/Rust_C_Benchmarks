# Finding 2

## Overview
The Unicode encoding design guarantees the safety of strings in Rust, but it introduces extra overheads for modifying string data type.

## Build and run benchmarks from source code
Take "reverse" as an example, you can follow the instructions to compile other algorithms.

### Rust version
```
$ rustc -C opt-level=3 -C overflow_checks=no reverse.rs -o reverse-Rust
$ time ./reverse-Rust < input
```

