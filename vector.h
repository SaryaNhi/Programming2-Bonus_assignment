#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include<string>
#include <stdexcept>
using namespace std;

class Vector {
private:
    //array size
    unsigned int mSize;
    
    //pointer to array
    double* mData;

    void allocate();
	void deallocate();
    //friend double dot(const Vector& a, const Vector& b);

public:
    //Constructor and Destructor
        //Create a vector with size 
        Vector(const int& size);

        //Creates a Vector of size x with all elements set to value.
        Vector(const int& size, const double& value);

        //Deep copy from another vector
        Vector(const Vector& theOther);

        //Destructor
        ~Vector();
    
    // Member functions
        void clear();

        //get the size
        unsigned int getSize() const;

        //get the entry at index
        double getEntry(const int& index) const;

        //set the value at index
        void setEntry(const int& index, const double& value);

        void print(string name) const;

        void ones() const;

        void zeros() const;

        void random() const;
    
    //Overloading operator
        //Operator =
        Vector& operator=(const Vector& theOther);

        //Operator +
        Vector operator+(const Vector& theOther);

        //Operator -
        Vector operator-(const Vector& theOther);

        //Operator * (scalar)
        Vector operator*(const double& scalar);

        //Zero-based access []
        double& operator[](const int& index);
        const double& operator [](const int& index)const;

        //One-based access ()
        double& operator()(const int& index);
        const double& operator()(const int& index)const;

        // Friend function for output stream
        friend ostream& operator<<(ostream& os, const Vector& v);
};
//Dot product
double dot(const Vector& a, const Vector& b);
#endif //VECTOR_H

//Change the this