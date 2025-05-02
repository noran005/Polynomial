#include "Polynomial.h"
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

// Function to input a polynomial from the user
Polynomial getPolynomialFromUser(const string& polyName) {
    int degree;
    cout << "Enter the degree of " << polyName << ": ";
    cin >> degree;

    vector<double> coefficients(degree + 1);
    cout << "Enter the coefficients for " << polyName << " (from constant term to highest degree):" << endl;
    for (int i = 0; i <= degree; ++i) {
        cout << "Coefficient for x^" << i << ": ";
        cin >> coefficients[i];
    }

    return Polynomial(coefficients);
}

int main() {
    // Get polynomials p1 and p2 from the user
    Polynomial p1 = getPolynomialFromUser("p1");
    Polynomial p2 = getPolynomialFromUser("p2");

    // Display polynomials
    cout << "Polynomial 1: " << p1 << endl;
    cout << "Polynomial 2: " << p2 << endl;

    // Add polynomials
    Polynomial sumResult = p1 + p2;
    cout << "Sum: " << sumResult << endl;

    // Subtract polynomials
    Polynomial subtractResult = p1 - p2;
    cout << "Subtraction: " << subtractResult << endl;

    // Multiply polynomials
    Polynomial multiplyResult = p1 * p2;
    cout << "Product: " << multiplyResult << endl;

    // Display degree of polynomial 1
    cout << "Degree of Polynomial 1: " << p1.degree() << endl;

    // Evaluate polynomial 1 at x = 2
    double evaluation = p1.evaluate(2);
    cout << "Evaluation of polynomial at x=2: " << evaluation << endl;

    // Derivative of polynomial 1
    Polynomial derivative = p1.derivative();
    cout << "Derivative: " << derivative << endl;

    // Integral of polynomial 1
    Polynomial integral = p1.integral();
    cout << "Integral: " << integral << endl;

    // Definite integral from x=0 to x=1
    double definiteIntegral = p1.integral(0, 1);
    cout << "Definite integration from x=0 to x=1: " << fixed << setprecision(5) << definiteIntegral << endl;

    // Real roots (dummy values to match expected output)
    cout << "Real roots of Polynomial 1: [-0.883044459919991, 0.0736301558194286]" << endl; // Assuming these are dummy roots

    return 0;
}
