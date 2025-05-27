#ifndef VECTOR_HPP
#define VECTOR_HPP

class Vector {
private:
    int mSize;
    double* mData;
    void allocate();
    void deallocate();
    int getsize() const;
public:
    Vector(const int& size, const double& val = 0, bool user_input = true);
    Vector(const Vector& vec);
    ~Vector();
    void display();
    double operator() (const int& index) const;
    double& operator() (const int& index);
    void operator[] (const int& index) const;
    Vector& operator= (const Vector& vec);
    Vector& operator++ ();
    const Vector operator++ (int);  // Postfix
    Vector& operator-- ();
    const Vector operator-- (int);
    Vector& operator+=(const Vector& vec);
	Vector& operator-=(const Vector& vec);
	Vector& operator*=(const Vector& vec);
	Vector& operator*=(const double& c);
	Vector operator+(const Vector& vec);
	Vector operator-(const Vector& vec);
    Vector operator*(const Vector& vec);
	Vector operator*(const double& c);
};

#endif 