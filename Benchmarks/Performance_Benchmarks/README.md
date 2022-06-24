# Performance Benchmarks

## Overview
Aiming to quantitatively analyze the performance of both languages in real world programming, we selected the Benchmarks Game to compare 10 different programs that are implemented separately in Rust and C versions, but simultaneously achieve the same functionality.

## Build and run benchmarks from source code
Take "fannkuch-redux" as an example, you can follow the instructions to compile other benchmarks.
### Rust version
```
$ RUSTFLAGS="-C opt-level=3 -C overflow_checks=yes -C codegen-units=1 -C target-cpu=ivybridge" cargo build
$ time ./fannkuchredux 12
```
### C version
```
$ clang -pipe -Wall -O3 -fomit-frame-pointer -march=ivybridge -pthread fannkuch-reduc.c -o fannkuchredux-C
$ time ./fannkuchredux-C 12
```
