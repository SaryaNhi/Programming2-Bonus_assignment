#include "linearsystem.h"
#include "vector.h"
#include "matrix.h"
#include <iostream>
#include <stdexcept>
#include <cmath>
using namespace std;
#define EPS 1e-10

// LINEAR SYSTEM CLASS

    // Public member
        // Constructot (no default constructor) and destructor
LinearSystem::LinearSystem(const Matrix& mx, const Vector& vec) {
    // Linear system: Ax = B    (mxn)(nx1) = (mx1)
    if(mx.getRows() == vec.getSize())
        throw std::invalid_argument("Rows of matrix not compatible with size of vector!");
    mpA = new Matrix(mx);
    mpb = new Vector(vec);
    mSize = mx.getRows() * mx.getCols();
}

LinearSystem::~LinearSystem() {
    delete[] mpA;
    delete[] mpb;
}

        // Member functions
void LinearSystem::display() const{
    cout << "Size: " << mSize << endl << "Matrix A: " << endl;
    mpA->print();
    mpb->print("B");
    solve().print("x");
}

Vector LinearSystem::solve() const{
    // 2 case: invertible matrix and not invertible matrix
    return mpA->inverse() * *mpb;
}




// POSSYM LINEAR SYSTEM CLASS
    // Public member
PosSymLinSystem::PosSymLinSystem(const Matrix& mx, const Vector& vec): LinearSystem(mx, vec) {
    if(!mpA->isPositiveDefinite())
        throw std::invalid_argument("Matrix is not positive definite!");
}

Vector PosSymLinSystem::solve() const{
    // (nxn)*(nx1) = (nx1)
    // 1. Initial guess solution x0
    Vector x(mpb->getSize());
    x.random();
    // 2. Initial residual r0 = b - Ax0 ; initial search direction p0 = r0
    Vector r = (*mpb) - (*mpA) * x;
    Vector p = r;
    // 3. Solving loop
    while(abs(r.norm()) > EPS) {
        // The denominator is a vector size = 1
        double alpha = dot(r, r) / (p.transpose() * (*mpA) * p).getEntry(0);
        x = x + alpha*p;
        Vector r_update = (*mpb) - (*mpA)*x;
        double beta = dot(r_update, r_update) / dot(r, r);
        // Update new direction p and r_k
        p = r_update + beta*p;
        r = r_update;
    }
    return x;
}