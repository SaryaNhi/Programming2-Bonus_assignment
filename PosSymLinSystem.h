#ifndef POSSYMLINSYSTEM_H
#define POSSYMLINSYSTEM_H

#include "LinearSystem.h"

class PosSymLinSystem : public LinearSystem {
public:
    PosSymLinSystem(const Matrix& A, const Vector& b);
    
    virtual Vector Solve() const override;
    
private:
    bool IsSymmetric(const Matrix& A) const;
};

#endif