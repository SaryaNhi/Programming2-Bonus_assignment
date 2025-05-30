#include"vector.h"
#include<iostream>
#include<string>
#include<cassert>
#include<cmath>
#include<random>

void Vector::allocate() {
    //allocate memory for double values
    mData = new double[mSize];
}
void Vector::deallocate() {
	delete[] mData;
}

//Constructor and Destructor
//Create a vector with size 
Vector::Vector(const int& size){
    mSize = size;
    allocate();
    for (int i = 0; i < mSize; i++) {
        mData[i] = 0;
    }
}

//Creates a Vector of size x with all elements set to value.
Vector::Vector(const int& size, const double& value) {
	mSize = size;
	allocate();
	for (int i = 0; i < mSize; i++) {
		mData[i] = value;
	}
}

//Deep copy from another vector
Vector::Vector(const Vector& theOther) {
    this->mSize = theOther.getSize();
    allocate();
    for (int i = 0; i < this->mSize; i++){
        this ->mData[i] = theOther.mData[i];
    }
}

Vector::~Vector() {
	deallocate();
}

//Member functions
void Vector::clear()
{
    //clear the vector
    mSize = 0;
    delete[]mData;
    mData = nullptr;
}

unsigned int Vector::getSize() const{
    return mSize;
}

double Vector::getEntry(const int& index) const{
    assert(index >= 0 && index < mSize);
    return mData[index];
}

void Vector::setEntry(const int& index, const double& value){
    assert(index >= 0 && index < mSize);
    mData[index] = value;
}

void Vector::ones() const {
    for (int i = 0; i < mSize; i++) {
        mData[i] = 1.0;
    }
}

void Vector::zeros() const {
    for (int i = 0; i < mSize; i++) {
        mData[i] = 0.0;
    }
}

void Vector::random() const {
    // Thread-safe since C++11 (initialization)
    static thread_local std::mt19937_64 engine(std::random_device{}());
    static std::uniform_real_distribution<double> dist(0.0, 1.0);

    for (int i = 0; i < mSize; i++){
        mData[i] = dist(engine);
    }
}

double Vector::norm() const {
    double sum = 0;
    for(int i = 0; i < mSize; i++) {
        sum += (getEntry(i) * getEntry(i));
    }
    return std::sqrt(sum);
}

void Vector::print(string name) const {
    cout << "Vector" << name << ":" << endl << "[";
    for (int i = 0; i < mSize; i++){
        cout << mData[i] << " ";
    }
    cout << "]" << endl;
}

//Overloading operator
Vector& Vector::operator=(const Vector& theOther) {
    assert(this->mSize == theOther.getSize());
    for (int i = 0; i < this->mSize; i++){
       this->mData[i] = theOther.mData[i];
    }
    return *this;
}

Vector Vector::operator+(const Vector& theOther){
    assert(this->mSize == theOther.getSize());
    Vector result(this->mSize);
    for (int i = 0; i < this->mSize; i++){
        result.mData[i] = this->mData[i] + theOther.mData[i];
    }
    return result;
}

Vector Vector::operator-(const Vector& theOther){
    assert(this->mSize == theOther.getSize());
    Vector result(this->mSize);
    for (int i = 0; i < this->mSize; i++){
        result.mData[i] = this->mData[i] - theOther.mData[i];
    }
    return result;
}

Vector Vector::operator*(const double& scalar){
    Vector result(this->mSize);
    for (int i = 0; i < this->mSize; i++){
        result.mData[i] = this->mData[i] * scalar;
    }
    return result;
}

double dot(const Vector& a, const Vector& b) {
    double result = 0;
    for (int i = 0; i < a.getSize(); i++){
        result += a.getEntry(i) * b.getEntry(i);
    }
    return result;
}

// zero‑based, mutable
double& Vector::operator[](const int& index) {
    if (index >= mSize) 
        throw std::out_of_range("Vector[] index out of range");
    return mData[index];
}

// zero‑based, const
const double& Vector::operator[](const int& index) const {
    if (index >= mSize) 
        throw std::out_of_range("Vector[] index out of range");
    return mData[index];
}

// one‑based, mutable
double& Vector::operator()(const int& index) {
    if (index < 1 || index > mSize) 
        throw std::out_of_range("Vector() index out of range");
    return mData[index - 1];
}

// one‑based, const
const double& Vector::operator()(const int& index) const {
    if (index < 1 || index > mSize) 
        throw std::out_of_range("Vector() index out of range");
    return mData[index - 1];
}
