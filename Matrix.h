#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include<string>
#include <stdexcept>
#include "vector.h"
using namespace std;

class Matrix {
private:
    //number of rows and columns
    int mNumRows_, mNumCols_;

    //original number of columns, for gaussian elimination
    int orig_cols_;

    //number of row swap
    int mNumSwap_;
    
    //Create a double pointer to store the matrix elements
    double ** mData;

    void allocate();
	void deallocate();


public:
    //Constructor and Destructor
        //Contstructor

        //Create a Matrix with the specified number of rows and columns
        Matrix(int rows, int cols);

        //Default constructor
        Matrix();

        //Create a copy
        Matrix(const Matrix &mat);

        //Destructor. For simplicity, i don't use virtual here since we don't have any inheritance like Sparse matrix etc.  
        ~Matrix();
    
    // Member functions
        // Get the number of rows and columns
        int getRows() const;
        int getCols() const;

        //rank of matrix
        int rank() const;

        void setEntry(int rows, int cols, const double value);
        double getEntry(int rows, int cols) const;

        //zeros
        void zeros();

        void print() const;
    
    //Overloading operator
        //Operator =
        Matrix& operator=(const Matrix &mat);

        //Operator +. Create a new Matrix
        Matrix operator+(const Matrix &mat);
    
        //Operator -. Create a new Matrix
        Matrix operator-(const Matrix &mat);
      
        //Operator * (scalar). Create a new Matrix
        Matrix operator*(const double scalar);

        //Operator * (vector). Create a new Vector 
        Vector operator*(const Vector &vec);

        //Operator * (Matrix). Create a new Matrix
        Matrix operator*(const Matrix &mat);

        //Operator ==
        bool operator==(const Matrix &mat) const;


        //overloaded round bracket operator
        // one‑based, mutable
        double& operator()(int rows, int cols);

        // one‑based, const
        const double& operator()(int rows, int cols) const;

        //Create identity matrix
        Matrix identity(int size) const;

        //Augmented matrix
        Matrix augment(const Matrix &A, const Matrix &B) const;

        //Gaussian elimination
        Matrix gaussianElimination() const;

        //tranpose matrix
        Matrix transpose() const;

        // is Symmetric?
        bool isSymmetric() const;

        //is Invertible?
        bool isInvertible() const;

        // is the matrix square?
        bool isSquare() const;

        //is the matrix full rank?
        bool isFullRank() const;

        //swap rows
        void swapRows(int i, int j);

        //determinant for square matrix
        double determinant() const;

        //inverse for square matrix
        Matrix inverse() const;

        //Row echelon form
        Matrix rowReduceFromGaussian() const;

        //pseudo-inverse
        Matrix pseudoInverse() const;

        // Moore-Penrose: regularlized pseudo inverse
        Matrix Moore_Penrose(double lambda = 0.01) const;

};

// Free function for scalar * matrix (allows scalar on left side)
Matrix operator*(double scalar, const Matrix& mat);

#endif //MATRIX_H

//Change the this