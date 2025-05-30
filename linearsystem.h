#ifndef LINEARSYSTEM_H
#define LINEARSYSTEM_H
#include "vector.h"
#include "matrix.h"
#include <iostream>
#include <stdexcept>
#include <cmath>

class LinearSystem {
protected:
    int mSize;
    Matrix* mpA;
    Vector* mpb;
    LinearSystem(const LinearSystem& other);    // Prevent user to use copy constructor
public:
// Constructor (no default) and destructor
    LinearSystem(const Matrix& mx, const Vector& vec);
    virtual ~LinearSystem();
// Member function
    virtual void display() const;
    virtual Vector solve() const;
};


class PosSymLinSystem: public LinearSystem {
public:
    PosSymLinSystem(const Matrix& mx, const Vector& vec); // add :LinearSystem(mx, vec) in definition
    Vector solve() const override;
};



#endif