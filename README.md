# Rust and C Benchmarks

## Overview
Rust is a statically-typed programming language developed for efficiency and safety, particularly in concurrency and memory safety. The popularity of Rust programming has increased over the last couple years because it was claimed to provide comparable speed to C/C++. This repository collect 22 macro benchmarks and 10 performance benchmarks that are both implemented in Rust and C from open-sourced third-parties to compare the run-time performance objectively.

## Building Environment
Rustc and llvm arre supported by different Ubuntu versions. For reproductive experiments, we recommend you to build them on Ubuntu 18.04 LTS 64bit.

#### Build Vanilla rust-1.61.0 from source code
```
$ git clone https://github.com/rust-lang/rust.git
$ cd rust
$ cp config.toml.example config.toml
$ ./x.py build && ./x.py install
```
To build and install Cargo, you may run ```./x.py install cargo``` or set the ```build.extended``` key in ```config.toml``` to true to build and install all tools.

#### Build Modified rust-1.61.0 from source code (in this repository)
```
$ cd rust-1.61.0-modified
$ cp config.toml.example config.toml
$ ./x.py build && ./x.py install
```

#### Download Vanilla LLVM-14.0.0 

It can be downloaded and installed from [[here]](https://github.com/llvm/llvm-project/releases/download/llvmorg-14.0.0/clang+llvm-14.0.0-x86_64-linux-gnu-ubuntu-18.04.tar.xz).

## Test Cases 
For more details, please refer to Section III "Performance Comparison: Rust v.s. C" in our paper.

Please refer to the relevant README under the [Benchmarks](./Benchmarks/README.md) path.

- [Micro_Benchmarks](./Benchmarks/Micro_Benchmarks/README.md)
- [Performance_Benchmarks](./Benchmarks//Performance_Benchmarks/README.md)

## New Findings

We discovered several new factors that influence Rust run-time performance. [Click here](./New_Findings/README.md) to view.