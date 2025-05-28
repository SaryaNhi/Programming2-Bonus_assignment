#include <iostream>
#include <cassert>
#include <cmath>
#include "vector.h"
#include "matrix.h"
#define EPS 1e-10

void Matrix::allocate() {
    //allocate memory for double values
    mData = new double*[mNumRows_];
    for (int i = 0; i < mNumRows_; i++) {
        mData[i] = new double[mNumCols_]; // Fixed: should use mNumCols_ not mNumRows_
    }
}

void Matrix::deallocate() {
    if (mData != nullptr){
        for (int i = 0; i < mNumRows_; i++) {
            delete[] mData[i];
        }
        delete[] mData;
        mData = nullptr;
    }
}

//Constructor and Destructor
//Create a matrix with size 
Matrix::Matrix(int rows, int cols) {
    //steps to create a matrix
    //1. size of row
    //2. size of column
    //3. allocate
    //4. initialize
    mNumRows_ = rows;
    mNumCols_ = cols;
    allocate();
    //initialize matrix with 0.0
    for (int i = 1; i < mNumRows_; i++) {
        for (int j = 1; j < mNumCols_; j++) { 
            (*this)(i, j) = 0.0;
        }
    }
}

//Create default matrix with size 1x1
Matrix::Matrix() : mNumRows_(1), mNumCols_(1) 
{
    // Allocate memory for the matrix
    allocate();
    
    // Initialize the single element to 0
   (*this)(1, 1) = 0.0;
}

Matrix::Matrix(const Matrix& mat) {
    //obtain the matrix size
    this->mNumRows_ = mat.getRows();
    this->mNumCols_ = mat.getCols();
    allocate();
    //deep copy
    for (int i = 0; i < mNumRows_; i++) {
        for (int j = 0; j < mNumCols_; j++) {
            this->mData[i][j] = mat.mData[i][j];
        }
    }
}

//Destructor
Matrix::~Matrix() {
    //deallocate memory
    deallocate();
}

//Member functions
//Get the number of rows
int Matrix::getRows() const {
    return mNumRows_;
}

//Get the number of cols
int Matrix::getCols() const {
    return mNumCols_;
}

//Calculate rank of matrix
int Matrix::rank() const {
    Matrix A = rowReduceFromGaussian();
    int rank = 0;
    bool zero_row = false;
    for (int i=1; i <= mNumRows_; i++) {
        for (int j=i; j <= mNumCols_; j++) {
            if (A(i,j) != 0) {
                rank++;
                break;
            }
            if (j == mNumCols_ && A(i,j) == 0) 
                zero_row = true;
        }
        if(zero_row)
            break;
    }
    return rank;
}

//Set entry
void Matrix::setEntry(int rows, int cols, const double value)  {
    assert(rows >= 1 && rows <= mNumRows_);
    assert(cols >= 1 && cols <= mNumCols_);
    (*this)(rows,cols) =  value;
}

//Get entry
double Matrix::getEntry(int rows, int cols) const {
    assert(rows >= 1 && rows <= mNumRows_);
    assert(cols >= 1 && cols <= mNumCols_);
    return (*this)(rows,cols);
}

//Print
void Matrix::print() const {
    for (int i = 1; i <= mNumRows_; i++) {
        for (int j = 1; j <= mNumCols_; j++) { 
            std::cout <<(*this)(i,j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

double& Matrix::operator() (int rows, int cols){
    if (rows < 1 || rows > mNumRows_) 
        throw std::out_of_range("Matrix() index out of row range");
    if (cols < 1 || cols > mNumCols_) 
        throw std::out_of_range("Matrix() index out of col range");
    return mData[rows-1][cols-1];
}

const double& Matrix::operator()(int rows, int cols) const {
    if (rows < 1 || rows > mNumRows_) 
        throw std::out_of_range("Matrix() index out of row range");
    if (cols < 1 || cols > mNumCols_) 
        throw std::out_of_range("Matrix() index out of col range");
    return mData[rows-1][cols-1];
}

void Matrix::zeros() {
    for (int i = 1; i <= mNumRows_; i++) {
        for (int j = 1; j <= mNumCols_; j++) {
            (*this)(i,j) = 0.0;
        }
    }
}

Matrix& Matrix::operator= (const Matrix& mat) {
    assert(this->mNumRows_ == mat.getRows());
    assert(this->mNumCols_ == mat.getCols());    
    for (int i = 0; i < this->mNumRows_; i++) {
        for (int j = 0; j < this->mNumCols_; j++) { 
            this->mData[i][j] = mat(i+1, j+1); 
        }
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix& mat) {
    assert(this->mNumRows_ == mat.getRows());
    assert(this->mNumCols_ == mat.getCols());
    int outputRows = this->mNumRows_;
    int outputCols = this->mNumCols_;
    Matrix output(outputRows, outputCols);
    output.zeros();
    for (int i = 0; i < this->mNumRows_; i++) {
        for (int j = 0; j < this->mNumCols_; j++) {
            output(i+1, j+1) = this->mData[i][j] + mat(i+1, j+1);
        }
    }
    return output;
}

Matrix Matrix::operator-(const Matrix& mat) {
    assert(this->mNumRows_ == mat.getRows());
    assert(this->mNumCols_ == mat.getCols());
    int outputRows = this->mNumRows_;
    int outputCols = this->mNumCols_;
    Matrix output(outputRows, outputCols);
    output.zeros();
    for (int i = 0; i < this->mNumRows_; i++) {
        for (int j = 0; j < this->mNumCols_; j++) {
            output(i+1, j+1) = this->mData[i][j] - mat(i+1, j+1); 
        }
    }
    return output;
}

bool Matrix::operator==(const Matrix& mat) const {
    assert(this->mNumRows_ == mat.getRows());
    assert(this->mNumCols_ == mat.getCols());
    for (int i = 0; i < this->mNumRows_; i++) {
        for (int j = 0; j < this->mNumCols_; j++) {
            if (this->mData[i][j] - mat(i+1, j+1) > EPS) {
                return false;
            }
        }
    }
    return true;
}



//is Square?
bool Matrix::isSquare() const {
    if (this->mNumRows_ == this->mNumCols_) {
        return true;
    }
    return false; 
}

//Is symmetric?
bool Matrix::isSymmetric() const {
    if (mNumRows_ != mNumCols_) return false; // Must be square
    return *this == this->transpose();
}

//Is invertible?
bool Matrix::isInvertible() const {
    //If it is square
    if (!isSquare()) return false;
    //If it does have determinant
    return fabs(determinant()) > EPS;
    //Then True
}

//Is full rank?
bool Matrix::isFullRank() const {
    int temp = mNumCols_;
    if (mNumRows_ < mNumCols_) 
        temp = mNumRows_;
    if (rank() == temp)
        return true;
    return false;
}

//A=B*C
//A=B.operator*(C)
//Matrix operator*(const Matrix& C) A: output, B: carrier, C: input
//     B (2x3)                 C (3x2)                   A (2x2)
//[ b11 b12 b13 ]     x    [ c11 c12 ]        =    [ a11 a12 ]
//[ b21 b22 b23 ]          [ c21 c22 ]             [ a21 a22 ]
//                         [ c31 c32 ]
// Number of elements regards in the sum is the cols (3) in B which explains the "for (int k = 0; k < this->mNumCols_; ++k);""
//a11 = b11*c11 + b12*c21 + b13*c31
//a12 = b11*c12 + b12*c22 + b13*c32
//a21 = b21*c11 + b22*c21 + b23*c31
//a22 = b21*c12 + b22*c22 + b23*c32

Matrix Matrix::operator*(const Matrix& mat) {
    assert(this->mNumCols_==mat.getRows());
    int outputRows = this->mNumRows_;
    int outputCols = mat.getCols();
    Matrix output(outputRows, outputCols);
    output.zeros();
    for (int i = 0; i < outputRows; ++i) {
        for (int j = 0; j < outputCols; ++j) { 
            for (int k = 0; k < this->mNumCols_; ++k) {
                output(i+1, j+1) += this->mData[i][k] * mat(k+1, j+1); 
            }
        }
    }
    return output;
}

//A=B*a
//A=B.operator*(a)
//Matrix operator*(const double scalar);
Matrix Matrix::operator* (const double scalar) {
    int outputRows = this->mNumRows_;
    int outputCols = this->mNumCols_;
    Matrix output(outputRows, outputCols);
    output.zeros();
    for (int i = 0; i < mNumRows_; ++i) {
        for (int j = 0; j < mNumCols_; ++j) {
            output(i+1, j+1) = this->mData[i][j] * scalar; 
        }
    }
    return output;
}


//Transpose matrix
Matrix Matrix::transpose() const {
    Matrix output(mNumCols_, mNumRows_ ); // Create a new matrix with swapped dimensions 
    for (int i = 1; i <= mNumCols_; ++i) {
        for (int j = 1; j <= mNumRows_; ++j) {
            output(i, j) = (*this)(j, i); 
        }
    }
    return output;
}

//

//t=E*v
//t=E.operator*(v)
// Matrix * Vector = Vector 
Vector Matrix::operator*(const Vector& vec) { 
    assert(this->mNumCols_ == vec.getSize());
    int outputSize = this->mNumRows_; 
    Vector output(outputSize); 
    output.zeros();
    for (int i = 0; i < this->mNumRows_; ++i) { 
        for (int j = 0; j < this->mNumCols_; ++j) {
            output(i+1) += this->mData[i][j] * vec(j+1); 
        }
    }
    return output;
}

//create identity matrix
Matrix Matrix::identity(int size) const{
    Matrix I(size, size);
    I.zeros();
    for (int i = 1; i <= size; ++i) {
        I(i, i) = 1.0;
    }
    return I;
}

//swap rows
void Matrix::swapRows(int i, int j) {
    assert(i >= 1 && i <= mNumRows_ && i != j);
    assert(j >= 1 && j <= mNumRows_ && j != i);
    for (int k = 1; k <= mNumCols_; ++k) {
        double temp = (*this)(i, k);
        (*this)(i, k) = (*this)(j, k);
        (*this)(j, k) = temp;
    }
}

//augment matrix
Matrix Matrix::augment(const Matrix &A, const Matrix &B) const{
    assert(A.getRows() == B.getRows());
    Matrix AB(A.mNumRows_, A.mNumCols_ + B.mNumCols_); 
    AB.orig_cols_ = A.mNumCols_;
    for (int i = 1; i <= A.mNumRows_; ++i) {
        for (int j = 1; j <= AB.mNumCols_; ++j) {
             //  A
            if (j <= A.mNumCols_) {
                AB(i, j) = A(i, j);
            }
            //  B
            else {
                AB(i, j) = B(i, j);
            }
        }
    }
    return AB;
}

//Gaussian elimination - Forward Phase
Matrix Matrix::gaussianElimination() const {
    Matrix Ab(*this);
    int rows = Ab.getRows();
    int cols = Ab.getCols();
    int Acol = Ab.orig_cols_;

    //swap count
    int swapCount = 0;
    
    //row tracker
    int i = 1;
    //col tracker
    int j = 1;

    //iterate through rows
    while (i <= rows && j <= Acol ){
        // Finding the partial pivot: finding the greatest absolute value and put the row having it to the top
        int best = i;
        double bestValue = fabs(Ab(i,j));
        for (int k = i + 1; k <= rows; k++){
            double tempValue = fabs(Ab(k, j));
            if (bestValue < tempValue){
                best = k;
                bestValue = tempValue;
            }
        }
        // if pivot too small then skip to the next col
        if (bestValue < EPS) {
            ++j;
            continue;
        }

        //swap if needed
        if (best != i) {
            //swap rows
            swapCount ++;
            Ab.swapRows(i, best);
            }

        // eliminate below by minus the cofactor
        for (int t = i+1; t <= rows; ++t) {
            double factor = Ab(t,j) / Ab(i,j);
            for (int s = j; s <= cols; ++s) {
                //Do the minus thingy
                Ab(t,s) -= factor * Ab(i,s);
                // If too small then make it 0.0
                if (fabs(Ab(t,s)) < EPS) Ab(t,s) = 0.0;
            }
        }

     ++i; ++j;
    }

    Ab.mNumSwap_ = swapCount;

    return Ab;
}

//rowReduceFromGaussian - Backward Phase: reduced row echelon
Matrix Matrix::rowReduceFromGaussian() const {
    Matrix R(*this);
    int rows = R.getRows();
    int cols = R.getCols();

    int i = rows;           //row tracker
    int j = R.orig_cols_;   //col tracker - start from the rightmost columnin the original matrix (left part)

    //Iterate through rows from bottom to top
    while (i >=0 ){
        //find the pivot farthest to the left of the row, stop when zero encountered
        int k = j - 1;
        while (k >= 0){
            if(R(i, k) != 0.0){
                j = k;
            }
        k--;
        }
        
        
        if(R(i,j) != 0.0){
            // divide row by pivot
            for (int k = j + 1; k < cols; ++k) {
                R(i, k) = R(i, k) / R(i, j);
                // If too small then make it 0.0
                if (R(i, k) < EPS && R(i, k) > -1*EPS)
                    R(i, k) = 0.0;
            }
            R(i, j) = 1; //Make the pivot 1

           // zero out elements above pivots if pivot not 0
            for (int t = i - 1; t >=0; --t){
                for(int s = 0; s < cols; s++){
                    if (s!=j){
                        R(t, s) = R(t, s) - R(i, s) * (R(t, j) / R(i, j));
                        //If too small then make it 0.0
                        if (R(t, s) < EPS && R(t, s) > -1*EPS){
                            R(t,s ) = 0.0;
                        }
                    }   
                }
            }

        }
        i--;
        j--; // This assumes each row's pivot is exactly one column left of the previous row's pivot, which should be true for a proper row echelon form
    }


    return R;
}

//determinant
double Matrix::determinant() const{
    assert(mNumRows_ == mNumCols_); //only square matrices have a determinant
    Matrix upper = this->gaussianElimination();

    // Calculate determinant as product of diagonal elements
    double determinant = 1.0;
    for (int i = 1; i <= mNumRows_; i++) {  // Using your 1-based indexing
        determinant *= upper(i, i);
    }

    // if the number of swap is odd then make it change its sign
    if (mNumSwap_%2==1){
        determinant *= -1.0;
    }

    return determinant;
}

Matrix Matrix::inverse() const {
    // Augment original matrix with identity matrix of same size, reduce the left part to identity matrix
    // Then the right part of augment matrix is the inverse matrix
    if(!isInvertible)
        return Moore_Penrose();     // If not invertible, return Moore-Penrose (pseudo-inverse may error if not full rank)
    Matrix I = identity(mNumRows_);
    Matrix Aug = augment(*this, I);
    Matrix A = Aug.gaussianElimination();
    Matrix B = A.rowReduceFromGaussian();
    Matrix inverse_mx(mNumRows_, mNumCols_);
    for(int i = 1; i <= mNumRows_; i++) {
        for(int j = 1; j <= mNumCols_; j++) {
            inverse_mx(i, j) = B(i, j + mNumCols_);
        }
    }
    return inverse_mx;
}

Matrix Matrix::pseudoInverse() const {
    Matrix AT = transpose();
    return (AT * *this).inverse() * AT; 
}

Matrix Matrix::Moore_Penrose(double lambda = 0.01) const {
    int m = getRows();
    int n = getCols();
    Matrix I = identity(n);
    Matrix AT = transpose();
    return(AT * *this + I * lambda).inverse() * AT;
}