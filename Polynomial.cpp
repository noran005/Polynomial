#include "Polynomial.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <iomanip>

using namespace std;

// Default constructor
Polynomial::Polynomial() : coeffs(1, 0.0) {}

// Constructor with coefficients
Polynomial::Polynomial(const vector<double>& coefficients) : coeffs(coefficients) {}

// Copy constructor
Polynomial::Polynomial(const Polynomial& other) : coeffs(other.coeffs) {}

// Destructor
Polynomial::~Polynomial() {}

// Assignment operator
Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        coeffs = other.coeffs;
    }
    return *this;
}

// Arithmetic operators
Polynomial Polynomial::operator+(const Polynomial& other) const {
    vector<double> resultCoeffs(max(coeffs.size(), other.coeffs.size()), 0.0);
    for (size_t i = 0; i < resultCoeffs.size(); ++i) {
        if (i < coeffs.size()) resultCoeffs[i] += coeffs[i];
        if (i < other.coeffs.size()) resultCoeffs[i] += other.coeffs[i];
    }
    return Polynomial(resultCoeffs);
}

Polynomial Polynomial::operator-(const Polynomial& other) const {
    vector<double> resultCoeffs(max(coeffs.size(), other.coeffs.size()), 0.0);
    for (size_t i = 0; i < resultCoeffs.size(); ++i) {
        if (i < coeffs.size()) resultCoeffs[i] += coeffs[i];
        if (i < other.coeffs.size()) resultCoeffs[i] -= other.coeffs[i];
    }
    return Polynomial(resultCoeffs);
}

Polynomial Polynomial::operator*(const Polynomial& other) const {
    vector<double> resultCoeffs(coeffs.size() + other.coeffs.size() - 1, 0.0);
    for (size_t i = 0; i < coeffs.size(); ++i) {
        for (size_t j = 0; j < other.coeffs.size(); ++j) {
            resultCoeffs[i + j] += coeffs[i] * other.coeffs[j];
        }
    }
    return Polynomial(resultCoeffs);
}

// Equality operator
bool Polynomial::operator==(const Polynomial& other) const {
    return coeffs == other.coeffs;
}

// Output operator
ostream& operator<<(ostream& out, const Polynomial& poly) {
    for (size_t i = 0; i < poly.coeffs.size(); ++i) {
        if (i > 0) {
            out << (poly.coeffs[i] >= 0 ? " + " : " ");
        }
        out << poly.coeffs[i] << "x^" << i;
    }
    return out;
}

// Utility functions
int Polynomial::degree() const {
    return coeffs.size() - 1; // Degree is the size of coeffs - 1
}

double Polynomial::evaluate(double x) const {
    double result = 0.0;
    for (int i = 0; i < coeffs.size(); ++i) {
        result += coeffs[i] * pow(x, i);
    }
    return result;
}

Polynomial Polynomial::derivative() const {
    if (coeffs.size() <= 1) return Polynomial({0}); // Derivative of constant is zero
    vector<double> derivCoeffs(coeffs.size() - 1);
    for (int i = 1; i < coeffs.size(); ++i) {
        derivCoeffs[i - 1] = i * coeffs[i];
    }
    return Polynomial(derivCoeffs);
}

Polynomial Polynomial::integral() const {
    vector<double> intCoeffs(coeffs.size() + 1);
    intCoeffs[0] = 0; // constant of integration
    for (int i = 0; i < coeffs.size(); ++i) {
        intCoeffs[i + 1] = coeffs[i] / (i + 1);
    }
    return Polynomial(intCoeffs);
}

double Polynomial::integral(double x1, double x2) const {
    Polynomial integralPoly = this->integral();
    return integralPoly.evaluate(x2) - integralPoly.evaluate(x1);
}

double Polynomial::getRoot(double guess, double tolerance, int maxIter) {
    double x = guess;
    for (int i = 0; i < maxIter; ++i) {
        double fx = evaluate(x);
        double dfx = derivative().evaluate(x);
        if (fabs(fx) < tolerance) return x; // Found root
        if (fabs(dfx) < 1e-10) break; // Avoid division by zero
        x -= fx / dfx; // Newton's method
    }
    return x; // Return last guess
}

void Polynomial::setCoefficients(const vector<double>& coefficients) {
    coeffs = coefficients;
}

double Polynomial::getCoefficient(int degree) const {
    if (degree < 0 || degree >= coeffs.size()) {
        throw out_of_range("Degree out of range");
    }
    return coeffs[degree];
}

Polynomial Polynomial::compose(const Polynomial& q) const {
    Polynomial result({0});  // Initialize result as the zero polynomial

    // Iterate through the coefficients of the current polynomial (this->coeffs)
    for (int i = coeffs.size() - 1; i >= 0; --i) {
        result = result * q + Polynomial({coeffs[i]});
    }

    return result;
}
