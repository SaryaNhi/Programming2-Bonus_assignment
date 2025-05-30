#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H

#include "MatrixB.h"

/*
 * Linear Regression model using Ordinary Least Squares (OLS)
 * Solves: weights = (X^T * X)^-1 * X^T * y
 */

class LinearRegression {
private:
    Matrix weights; // Model coefficients (including bias)
    bool trained;   // Training status flag


public:
    LinearRegression(); // Fixed: Initializes weights to 0x0 matrix
   
    // Trains model using input features X and target values y
    void train(const Matrix& X, const Matrix& y);
   
    // Predicts target values for input features X
    Matrix predict(const Matrix& X) const;
   
    // Computes Root Mean Squared Error
    double rmse(const Matrix& predictions, const Matrix& targets) const;


    // Outputs model coefficients
    void printWeights() const;
};

#endif
