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

## Matrix Class

This project provides a C++ implementation of a `Matrix` class that supports basic and advanced matrix operations, including linear algebra functionalities like Gaussian elimination, inversion, and the Moore-Penrose pseudoinverse.

### Features

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

### Dependencies

- Requires `Vector` class defined in `vector.h`
- Uses standard C++ libraries: `<iostream>`, `<string>`, `<stdexcept>`

## Matrix Class

This project provides a C++ implementation of a `LinearSystem` class that supports solving linear system, including over-determined and under-determined linear system; and its subclass `PosSymLinSystem` to find solution of positive definite symmetric linear systems.

### Features

- Solve the linear system Ax = B
- Integration with the `Vector` and `Matrix` class

### Dependencies

- Requires `Vector` class defined in `vector.h`, `Matrix` class defined in `Matrix.h`
- Uses standard C++ libraries: `<iostream>`, `<string>`, `<stdexcept>`

### Usage

Include both header files in your project:

```cpp
#include "matrix.h"
#include "vector.h"
#include "linearsystem.h"
```

## Linear Regression Module

This module implements a linear regression model using the Ordinary Least Squares (OLS) method to predict the target PRP value from 6 input features extracted from the `machine.data` dataset.

### Files and Structure

- `mainB.cpp`: Main program file – handles data reading, normalization, training, prediction, and evaluation.
- `MatrixB.h / MatrixB.cpp`:  
  Custom matrix class supporting:
  - Matrix initialization, deep copy
  - Transposition
  - Matrix multiplication
  - Matrix inversion using Gaussian elimination
- `LinearRegression.h / LinearRegression.cpp`:  
  Implementation of a linear regression model that supports:
  - Training with closed-form solution:  
    $$
    w = (X^T X)^{-1} X^T y
    $$
  - Prediction on new data
  - RMSE evaluation
- `machine.data`: Dataset used. Only 6 input features (from columns 3 to 8) and the target PRP (column 9) are used.

---

### Functional Description

#### 1. Data Processing

- Input: `machine.data`  
- Skips first 2 columns (`vendor name`, `model name`)  
- Extracts 6 numerical features and target PRP  
- Applies **standardization** using training set mean and standard deviation:  
  $$
  x' = \frac{x - \mu}{\sigma}
  $$
- Adds **bias term** as the first feature (value 1)

#### 2. Train-Test Split

- Total: 209 samples  
- 80% training set  
- 20% testing set  
- Random shuffle using Fisher-Yates algorithm

#### 3. Model Training

- Uses the closed-form solution of OLS:  
  $$
  w = (X^T X)^{-1} X^T y
  $$
- Matrix operations (`transpose`, `multiply`, `inverse`) are supported through `MatrixB.cpp`.

#### 4. Prediction and Evaluation

- Predicts PRP using:  
  $$
  \hat{y} = X_{\text{test}} \cdot w
  $$
- Evaluates accuracy using RMSE (Root Mean Squared Error):  
  $$
  \text{RMSE} = \sqrt{ \frac{1}{n} \sum_{i=1}^{n} (y_i - \hat{y}_i)^2 }
  $$

---

### How to Compile and Run

```bash
g++ mainB.cpp MatrixB.cpp LinearRegression.cpp -o linearRegressionProgram
./linearRegressionProgram