# tyler-matrix Library
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/license/mit)
![C++](https://img.shields.io/badge/C%2B%2B-23-blue.svg?style=flat&logo=c%2B%2B)

A high performance, header-only C++ math matrix library.

## Features
* **Easy Implementation:** Just need to include the header file to implement the library.
* **Efficient Storage:** Uses a 1D vector to lower memory use.
* **Modern Features:** Compiled with C++23 standards.
* **Cross-Platform:** Verified to work with Windows, MacOS, and Linux operating systems.

## Installation
This is a **header-only** library. Simply copy `include/matrix.hpp` and `include/matrix.tpp` into your project's include directory.

## Requirements
* Must compile with at least the C++23 standard.

## Quick Start
```cpp
#include "matrix.hpp"

int main()
{
  Matrix<int> m (3, 3, 1);
  m (1, 1) = 5;
  return 0;
}
```

## Testing
* Download the additional files in tests/ and Makefile.
* Run **make**
* Run **./test_library***
* In addition, you can use the included gof.cpp for a working demo:
* Run **make gof_demo**
* Run **./gof_demo <size> <layout>**

**Artifical Intelligence was used in the following ways for this repository:**
* Assisted in creation of Makefile, test.yml, docs.yml
* Created some test cases

## Attributions and Licenses
**This library is distributed with the MIT license:**
**[License Information](https://opensource.org/license/mit)**

* **[Catch2](https://github.com/catchorg/Catch2):** Modern C++ testing framework.
