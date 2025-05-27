#include "Vector.hpp"
#include <iostream>
#include <cassert>
using namespace std;

// PRIVATE FUNCTION
void Vector::allocate() {
    mData = new double[mSize + 1];
    mData[0] = 0; // Dummy header, always = 0
}

void Vector::deallocate() {
    delete[] mData;
}

int Vector::getsize() const{
    return mSize;
}



// PUBLIC FUNCTION
Vector::Vector(const int& size, const double& val, bool user_input) {
    mSize = size;
    allocate();
    if (user_input) {
        for (int i=1; i<=this->mSize; i++) {
            cout << "Enter value for entry " << i <<": ";
            cin >> this->mData[i];
        }
    }
    else {
        for (int i=1; i<=this->mSize; i++) {
            mData[i] = val;
        }
    }

}
Vector::Vector(const Vector& vec) {
    this->mSize = vec.getsize();
    allocate();
    for(int i = 1; i<=this->mSize; i++) {
        this->mData[i] = vec(i);
    }
}

Vector::~Vector() {
    deallocate();
}

void Vector::display() {
    cout << "[ ";
    for (int i=1; i<=mSize; i++) {
        cout << mData[i] << " ";
    }
    cout << "]";
}

double Vector::operator() (const int& index) const{    // return value of the entry, do not allow modifying
    (*this)[index]; //check if index valid
    return mData[index];
}
double& Vector::operator() (const int& index) {    // return reference of entry, can modify
    (*this)[index]; //check if index valid
    return mData[index];
}

void Vector::operator[] (const int& index) const{    // Valid index is in range [1,mSize]; 0 is dummy header
    assert(index > 0 && index <= mSize);
}


Vector& Vector::operator= (const Vector& vec) {     // Return a referenced of this vector after copy
    if (this == &vec) return *this;  // Check for self-assignment
    assert(this->mSize == vec.getsize());
    for(int i=1; i<=this->mSize; i++) {
        this->mData[i] = vec(i);
    }
    return *this;
}


Vector& Vector::operator++ () {
    for(int i=1; i<=this->mSize; i++) {
        ++(this->mData[i]);
    }
    return *this;
}
const Vector Vector::operator++ (int) {  // Postfix: return copy of current this before increment
    Vector ans = *this;
    for(int i=1; i<=this->mSize; i++) {
        (this->mData[i])++;
    }
    return ans;
}

Vector& Vector::operator-- () {
    for(int i=1; i<=this->mSize; i++) {
        --(this->mData[i]);
    }
    return *this;
}
const Vector Vector::operator-- (int) {  // Postfix: return copy of current this before decrement
    Vector ans = *this;
    for(int i=1; i<=this->mSize; i++) {
        (this->mData[i])--;
    }
    return ans;
}

Vector& Vector::operator+=(const Vector& vec) {
    assert(this->mSize == vec.getsize());
    for(int i=1; i<=this->mSize; i++) {
        this->mData[i] += vec(i);
    }
    return *this;
}
Vector& Vector::operator-=(const Vector& vec) {
    assert(this->mSize == vec.getsize());
    for(int i=1; i<=this->mSize; i++) {
        this->mData[i] -= vec(i);
    }
    return *this;
}
Vector& Vector::operator*=(const Vector& vec) {
    assert(this->mSize == vec.getsize());
    for(int i=1; i<=this->mSize; i++) {
        this->mData[i] *= vec(i);
    }
    return *this;
}
Vector& Vector::operator*=(const double& c) {
    for(int i=1; i<=this->mSize; i++) {
        this->mData[i] *= c;
    }
    return *this;
}

Vector Vector::operator+(const Vector& vec) {
    assert(this->mSize == vec.getsize());
    int ansSize = this->mSize;
    Vector ans(ansSize, 0, false);
    for(int i=1; i<=ansSize; i++) {
        ans(i) = this->mData[i] + vec(i);
    }
    return ans;
}
Vector Vector::operator-(const Vector& vec) {
    assert(this->mSize == vec.getsize());
    int ansSize = this->mSize;
    Vector ans(ansSize, 0, false);
    for(int i=1; i<=ansSize; i++) {
        ans(i) = this->mData[i] - vec(i);
    }
    return ans;
}
Vector Vector::operator*(const Vector& vec) {
    assert(this->mSize == vec.getsize());
    int ansSize = this->mSize;
    Vector ans(ansSize, 0, false);
    for(int i=1; i<=ansSize; i++) {
        ans(i) = this->mData[i] * vec(i);
    }
    return ans;
}
Vector Vector::operator*(const double& c) {
    int ansSize = this->mSize;
    Vector ans(ansSize, 0, false);
    for(int i=1; i<=ansSize; i++) {
        ans(i) = this->mData[i] * c;
    }
    return ans;
}


int main() {
    Vector a(6, 1, false);
    a.display();
    Vector b(6, 0, false);
    Vector c = a++ + b;
    a.display();
    b.display();
    c.display();
    return 0;
}
