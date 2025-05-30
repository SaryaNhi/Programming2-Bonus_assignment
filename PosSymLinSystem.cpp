#include "PosSymLinSystem.h"
#include <cassert>
#include <cmath>

PosSymLinSystem::PosSymLinSystem(const Matrix& A, const Vector& b)
    : LinearSystem(A, b) {
    assert(IsSymmetric(A));
}

// Check if matrix is symmetric
bool PosSymLinSystem::IsSymmetric(const Matrix& A) const {
    assert(A.GetNumRows() == A.GetNumCols());
    
    int n = A.GetNumRows();
    for (int i = 1; i <= n; i++) {
        for (int j = i+1; j <= n; j++) {
            if (fabs(A(i, j) - A(j, i)) > 1e-10) {
                return false;
            }
        }
    }
    
    return true;
}

// Solve method using conjugate gradient
Vector PosSymLinSystem::Solve() const {
    // Get reference to matrix A and vector b
    const Matrix& A = *mpA;
    const Vector& b = *mpb;
    
    int n = A.GetNumRows();
    assert(A.GetNumCols() == n); // Check if A is square
    
    // Initial guess
    Vector x(n);
    for (int i = 1; i <= n; i++) {
        x(i) = 0.0;
    }
    
    // Initialize residual r = b - Ax
    Vector r = b - A * x;
    
    // Initialize direction vector p = r
    Vector p = r;
    
    // Initialize variables
    double rsold = r * r;
    double rsnew, alpha, beta;
    
    // Tolerance for convergence
    const double tol = 1e-10;
    
    // Maximum iterations
    const int maxIter = 1000;
    
    // Conjugate gradient iterations
    for (int iter = 0; iter < maxIter; iter++) {
        // Exit if residual is small enough
        if (sqrt(rsold) < tol) {
            break;
        }
        
        // Calculate A*p
        Vector Ap = A * p;
        
        // Calculate step size
        alpha = rsold / (p * Ap);
        
        // Update solution
        x = x + (alpha * p);
        
        // Update residual
        r = r - (alpha * Ap);
        
        // Calculate new residual norm
        rsnew = r * r;
        
        // Calculate new direction
        beta = rsnew / rsold;
        p = r + (beta * p);
        
        // Update residual norm
        rsold = rsnew;
    }
    
    return x;
}