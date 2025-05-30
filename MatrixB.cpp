#include "MatrixB.h"
#include <iostream>
#include <cmath>
using namespace std;


// Constructor: Allocates memory and initializes to zero
Matrix::Matrix(int r, int c) : rows(r), cols(c) {
    data = new double*[rows];
    for (int i = 0; i < rows; ++i)
        data[i] = new double[cols](); // Zero-initialize
}


// Copy constructor: Performs deep copy
Matrix::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
    data = new double*[rows];
    for (int i = 0; i < rows; ++i) {
        data[i] = new double[cols];
        for (int j = 0; j < cols; ++j)
            data[i][j] = other.data[i][j];
    }
}


// Destructor: Frees dynamically allocated memory
Matrix::~Matrix() {
    for (int i = 0; i < rows; ++i)
        delete[] data[i];
    delete[] data;
}


// Assignment operator: Handles self-assignment and deep copy
Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) return *this; // Self-assignment check


    // Free existing memory
    for (int i = 0; i < rows; ++i)
        delete[] data[i];
    delete[] data;


    // Copy data from other
    rows = other.rows;
    cols = other.cols;
    data = new double*[rows];
    for (int i = 0; i < rows; ++i) {
        data[i] = new double[cols];
        for (int j = 0; j < cols; ++j)
            data[i][j] = other.data[i][j];
    }
    return *this;
}


// Accessors
int Matrix::getRows() const { return rows; }
int Matrix::getCols() const { return cols; }
double Matrix::get(int r, int c) const { return data[r][c]; }
void Matrix::set(int r, int c, double value) { data[r][c] = value; }


// Transpose operation: Rows become columns and vice versa
Matrix Matrix::transpose() const {
    Matrix result(cols, rows);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            result.set(j, i, data[i][j]);
    return result;
}


// Matrix multiplication: Classic O(n^3) algorithm
Matrix Matrix::multiply(const Matrix& other) const {
    // Check if dimensions are compatible
    if (cols != other.rows) {
        cerr << "Matrix dimension mismatch for multiplication.\n";
        return Matrix(0, 0);
    }
   
    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < other.cols; ++j)
            for (int k = 0; k < cols; ++k)
                result.data[i][j] += data[i][k] * other.data[k][j];
    return result;
}


// Matrix inverse: Uses Gaussian elimination (for square matrices)
Matrix Matrix::inverse() const {
    if (rows != cols) {
        cerr << "Matrix must be square to invert.\n";
        return Matrix(0, 0);
    }


    int n = rows;
    Matrix augmented(n, 2 * n); // Augmented matrix [A | I]


    // Build augmented matrix: left half is original, right half is identity
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            augmented.set(i, j, data[i][j]);
        augmented.set(i, i + n, 1.0); // Identity part
    }


    // Gaussian elimination with partial pivoting
    for (int i = 0; i < n; ++i) {
        // Find pivot row (partial pivoting for stability)
        int pivotRow = i;
        for (int k = i + 1; k < n; ++k)
            if (abs(augmented.data[k][i]) > abs(augmented.data[pivotRow][i]))
                pivotRow = k;


        // Swap current row with pivot row
        if (pivotRow != i)
            for (int j = 0; j < 2 * n; ++j)
                swap(augmented.data[i][j], augmented.data[pivotRow][j]);


        // Check for singularity
        if (augmented.data[i][i] == 0.0) {
            cerr << "Matrix is singular (no inverse).\n";
            return Matrix(0, 0);
        }


        // Normalize pivot row
        double pivot = augmented.data[i][i];
        for (int j = 0; j < 2 * n; ++j)
            augmented.data[i][j] /= pivot;


        // Eliminate other rows
        for (int k = 0; k < n; ++k) {
            if (k == i) continue;
            double factor = augmented.data[k][i];
            for (int j = 0; j < 2 * n; ++j)
                augmented.data[k][j] -= factor * augmented.data[i][j];
        }
    }


    // Extract inverse matrix from right half of augmented matrix
    Matrix inv(n, n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            inv.set(i, j, augmented.get(i, j + n));


    return inv;
}


// Utility: Prints matrix to console
void Matrix::print() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j)
            cout << data[i][j] << " ";
        cout << "\n";
    }
}
