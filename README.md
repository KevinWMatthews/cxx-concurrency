# Concurrency in C++

Introduction to C++ standard library features for multi-threading.

## Background

Explore concurrency concepts and semantics using the C++ standard library and
show how the Thread Sanitizer can be used to debug race conditions at runtime.

## Prerequesites

  * C++ compiler (C++11 or newer)
  * CMake (TODO or newer)
  * POSIX threading library

## Getting Started

The project can be compiled using CMake and a C++ compiler:
```bash
$ cmake .
$ make
```

Executables are located in the `bin/` directory.
```bash
$ ./bin/<executable>
```

An out-of-tree build is typically preferable to compiling in the source directory.
See the [documentation](https://kevinwmatthews.github.io/cxx-concurrency/setup.html)
for details.
