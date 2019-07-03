---
layout: page
title: Setup
---

## Prerequisites

  * Compiler that supports C++11 or newer
  * CMake v3.8 or newer
  * POSIX threading library (pthread)

## Setup

### Directory Structure
This repo is designed for an out-of-tree build. This makes it easier to switch
between compilers should this be required.

A typical directory tree is:
```
cxx-concurrency/
├── build/
└── cxx-concurrency/
```

Create this using:
```bash
$ mkdir cxx-concurrency
$ cd cxx-concurrency
$ mkdir build
$ git clone git@github.com:KevinWMatthews/cxx-concurrency.git
```

### Configure

At its simplest, simply run CMake:
```bash
$ cd build
$ cmake ../cxx-concurrency
$ make
```

The project has several build options:

  * `USE_CXX_STANDARD`
    - Set the C++ standard. Allowed values are: `98`,`11`, `14`, `17`, `20`
  * `ENABLE_TSAN`
    - Enable the thread sanitizer. Allowed values are: `ON`, `OFF`

To set configuration options, use:
```bash
$ ccmake ../cxx-concurrency
# or
$ cmake-gui ../cxx-concurrency
```

or set them from the command line:
```bash
$ cmake ../cxx-concurrency -DUSE_CXX_STANDARD=11 -DENABLE_TSAN=ON
```


### Build

Once a project is configured, simply run:
```bash
$ cd build
$ make
```

That's it!


### Run

Executables are located in the `bin` directory of the build tree:

```bash
.
├── build
│   ├── bin
```

Run them using:

```bash
$ cd build/bin
$ ./<executable_name>
```
