#include "LinearRegression.h"
#include <iostream>
#include <cmath>
using namespace std;

// Constructor: Initialize weights as 0x0 matrix
LinearRegression::LinearRegression()
    : weights(0, 0),  // Initialize with empty matrix
      trained(false) {}


// Training: Implements OLS solution
void LinearRegression::train(const Matrix& X, const Matrix& y) {
    Matrix Xt = X.transpose();        // X^T
    Matrix XtX = Xt.multiply(X);      // X^T * X
    Matrix XtX_inv = XtX.inverse();   // (X^T * X)^-1
   
    // Check if inverse computation failed
    if (XtX_inv.getRows() == 0) {
        trained = false;
        return;
    }
   
    Matrix XtY = Xt.multiply(y);      // X^T * y
    weights = XtX_inv.multiply(XtY);  // Final weights
    trained = true;
}


// Prediction: Returns X * weights
Matrix LinearRegression::predict(const Matrix& X) const {
    if (!trained) {
        cout << "Model is not trained.\n";
        return Matrix(0, 0);
    }
    return X.multiply(weights);
}


// RMSE Calculation: sqrt(mean((predictions - targets)^2))
double LinearRegression::rmse(const Matrix& predictions, const Matrix& targets) const {
    double sum = 0.0;
    int n = predictions.getRows();
    for (int i = 0; i < n; ++i) {
        double diff = predictions.get(i, 0) - targets.get(i, 0);
        sum += diff * diff;
    }
    return sqrt(sum / n);
}


// Output: Displays model coefficients
void LinearRegression::printWeights() const {
    if (!trained) {
        cout << "Model is not trained.\n";
        return;
    }
    cout << "Weights:\n";
    for (int i = 0; i < weights.getRows(); ++i)
        cout << "w" << i << ": " << weights.get(i, 0) << "\n";
}
