//
// Created by dev on 11/7/17.
//

#include <iostream>      // standard input/output
#include <vector>        // standard vector
#include <cppad/cppad.hpp> // the CppAD package http://www.coin-or.org/CppAD/

namespace {
    // define y(x) = Poly(a, x) in the empty namespace
    template <class Type>
    Type Poly(const std::vector<double> &a, const Type &x)
    {     size_t k  = a.size();
        Type y   = 0.;  // initialize summation
        Type x_i = 1.;  // initialize x^i
        size_t i;
        for(i = 0; i < k; i++)
        {     y   += a[i] * x_i;  // y   = y + a_i * x^i
            x_i *= x;           // x_i = x_i * x
        }
        return y;
    }
}

using CppAD::AD;           // use AD as abbreviation for CppAD::AD
using std::vector;         // use vector as abbreviation for std::vector

void exercise3() {
//    Compute and print the derivative of f ( x ) = exp ( x ) - 1 - x - x 2 / 2 at the point x = .5 .
    int k = 3;
    vector<double> a = {1.0, 1.0, 0.5};

    int n = 1;
    vector<AD<double>> X(n);
    X[0] = 0.5;
    CppAD::Independent(X);
    int m = 1;
    vector<AD<double>> Y(m);
    Y[0] = exp(X[0]) - Poly(a, X[0]);
//    Y[0] = exp(X[0]);
//    Y[0] = Poly(a, X[0]);
    CppAD::ADFun<double> f(X, Y);
    vector<double> jac(m*n);
    vector<double> x(n);
    x[0] = 0.5;
    jac = f.Jacobian(x);
    std::cout << "f'(0.5) computed by CppAD = " << jac[0] << std::endl;
}

// main program
int main(void)
{     using CppAD::AD;           // use AD as abbreviation for CppAD::AD
    using std::vector;         // use vector as abbreviation for std::vector
    size_t i;                  // a temporary index

    exercise3();

    // vector of polynomial coefficients
    size_t k = 5;              // number of polynomial coefficients
    vector<double> a(k);       // vector of polynomial coefficients
    for(i = 0; i < k; i++)
        a[i] = 1.;           // value of polynomial coefficients

    // domain space vector
    size_t n = 1;              // number of domain space variables
    vector< AD<double> > X(n); // vector of domain space variables
    X[0] = 3.;                 // value corresponding to operation sequence
//    X[0] = 100.;                 // value corresponding to operation sequence
//    X[0] = -100.;                 // value corresponding to operation sequence
//    X[0] = -0.;                 // value corresponding to operation sequence

    // declare independent variables and start recording operation sequence
    CppAD::Independent(X);

    // range space vector
    size_t m = 1;              // number of ranges space variables
    vector< AD<double> > Y(m); // vector of ranges space variables
    Y[0] = Poly(a, X[0]);      // value during recording of operations

    // store operation sequence in f: X -> Y and stop recording
    CppAD::ADFun<double> f(X, Y);

    // compute derivative using operation sequence stored in f
    vector<double> jac(m * n); // Jacobian of f (m by n matrix)
    vector<double> x(n);       // domain space vector
    x[0] = 3.;                 // argument value for derivative
//    x[0] = 1.;                 // argument value for derivative
    jac  = f.Jacobian(x);      // Jacobian for operation sequence

    // print the results
    std::cout << "f'(3) computed by CppAD = " << jac[0] << std::endl;

    // check if the derivative is correct
    int error_code;
    if( jac[0] == 142. )
        error_code = 0;      // return code for correct case
    else  error_code = 1;      // return code for incorrect case

    return error_code;
}
