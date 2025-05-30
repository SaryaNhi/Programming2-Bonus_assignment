#ifndef MATRIXB_H
#define MATRIXB_H

/*
 * Matrix class for linear algebra operations.
 * Supports basic matrix operations: transpose, multiplication, and inverse.
 */

class Matrix {
private:
    int rows;     // Number of rows
    int cols;     // Number of columns
    double** data; // 2D array to store matrix data


public:
    // Constructor: creates a zero-initialized matrix of size r x c
    Matrix(int r, int c);
   
    // Copy constructor: deep copy of another matrix
    Matrix(const Matrix& other);
   
    // Destructor: frees allocated memory
    ~Matrix();


    // Assignment operator: deep copy assignment
    Matrix& operator=(const Matrix& other);


    // Accessors
    int getRows() const;
    int getCols() const;
    double get(int r, int c) const;
    void set(int r, int c, double value);


    // Matrix operations
    Matrix transpose() const;    // Returns transpose of the matrix
    Matrix multiply(const Matrix& other) const; // Matrix multiplication
    Matrix inverse() const;      // Returns inverse (for square matrices)


    // Utility
    void print() const; // Prints matrix contents
};

#endif
