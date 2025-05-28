#include "Vector.h"
#include<iostream>
#include<string>
#include<cassert>
#include<cmath>
#include<random>

#include <iomanip>

int main() {
    Vector a(3);
    Vector b(3);

    a.setEntry(0, 1);
    a.setEntry(1, 2);
    a.setEntry(2, 3);

    b.setEntry(0, 4);
    b.setEntry(1, 5);
    b.setEntry(2, 6);

    double result = dot(a, b);
    cout << "Dot product: " << result << endl;  // Should print 32
    return 0;
}