# Programming2-Bonus_assignment

## Vector Class

This project defines a basic `Vector` class in C++ to represent and manipulate 1D mathematical vectors. 

### Features

- Dynamic memory allocation for vector storage
- Support for common vector operations:
  - Addition
  - Subtraction
  - Scalar multiplication
  - Dot product
- Element access via both `[]` (zero-based) and `()` (one-based)
- Initialization utilities:
  - Fill with ones
  - Fill with zeros
  - Fill with random values
- Deep copy and assignment operator
- Output printing via `<<` stream operator

## Usage
This is a small part of a project along with matrix class.

# Matrix Class

This project provides a C++ implementation of a `Matrix` class that supports basic and advanced matrix operations, including linear algebra functionalities like Gaussian elimination, inversion, and the Moore-Penrose pseudoinverse.

## Features

- Dynamic 2D array allocation for matrix storage
- Support for core operations:
  - Matrix addition, subtraction, multiplication (by scalar, vector, or another matrix)
  - Element-wise access and modification
  - Identity matrix creation
  - Matrix transposition
  - Gaussian elimination and row reduction
  - Determinant and inverse computation (for square matrices)
  - Symmetry, invertibility and positive definited checks
  - Pseudoinverse calculation (Moore-Penrose)
    - Pseudo inverse: (A^T x A)^(-1) x A^T
    - Moore-Penrose: [(A^T x A) + (lambda x I)]^(-1) x A^T
- Operator overloading:
  - `+`, `-`, `*`, `==`, `()` (one-based indexing)
- Integration with the `Vector` class

## Dependencies

- Requires `Vector` class defined in `vector.h`
- Uses standard C++ libraries: `<iostream>`, `<string>`, `<stdexcept>`

# Matrix Class

This project provides a C++ implementation of a `LinearSystem` class that supports solving linear system, including over-determined and under-determined linear system; and its subclass `PosSymLinSystem` to find solution of positive definite symmetric linear systems.

## Features

- Solve the linear system Ax = B
- Integration with the `Vector` and `Matrix` class

## Dependencies

- Requires `Vector` class defined in `vector.h`, `Matrix` class defined in `Matrix.h`
- Uses standard C++ libraries: `<iostream>`, `<string>`, `<stdexcept>`

## Usage

Include both header files in your project:

```cpp
#include "matrix.h"
#include "vector.h"
#include "linearsystem.h"
```
