# New Findings

## Overview
After measuring the performance of algorithms from micro benchmarks, we observe that in some cases, even with disabling all run-time checks, the Rust implementation is still much slower than the C implementation. We discovered several new factors that influence Rust run-time performance

## Finding 1
Rust uses saturating floating-point to integer conversions for type casting, which is conservative but incurs extra run-time overheads.
- Please see [HERE](https://github.com/yzhang71/Rust_C_Benchmarks/tree/main/New_Findings/Finding_1)

## Finding 2
The Unicode encoding design guarantees the safety of strings in Rust, but it introduces extra overheads for modifying string data type.
- Please see [HERE](https://github.com/yzhang71/Rust_C_Benchmarks/tree/main/New_Findings/Finding_2)