/**
 * This program demonstrates triangle calculations using three fixed vertices.
 * It calculates the distances between each pair of vertices, the perimeter,
 * the area (using Heron’s formula), and the centroid of the triangle.
 * All results are displayed to the nearest thousandth.
 *
 * @author Day'Quan Williams
 * <pre>
 * File: TriangleCalculator.cpp
 * Course: CSC 1253 Section 1
 * Programming Project: 5
 * DATE COMPLETED: November 24, 2025
 * Instructor: Dr. Duncan
 * </pre>
 */


#include <iostream>
#include <sstream>
#include <cmath>
#include <limits>
using namespace std;

// ---------------------------------------------------------
// FUNCTION PROTOTYPES
// ---------------------------------------------------------
int degree(const double p[]);
double eval(const double p[], double x);
string ptos(const double p[]);
double* add(const double p[], const double q[]);
double* sub(const double p[], const double q[]);
double* mult(const double p[], const double q[]);
bool equals(const double p[], const double q[]);

// Helpful internal function for add()
double* removeLeadingZeros(const double p[], const double q[]);

// ---------------------------------------------------------
// DEGREE FUNCTION
// ---------------------------------------------------------
int degree(const double p[]) {
    return (int)p[0];
}

// ---------------------------------------------------------
// FAST POLYNOMIAL EVALUATION (Horner's Method)
// ---------------------------------------------------------
double eval(const double p[], double x) {
    int d = degree(p);
    if (d < 0) return numeric_limits<double>::quiet_NaN();

    double answer = 0;
    for (int i = 1; i <= d + 1; i++) {
        answer = answer * x + p[i];
    }
    return answer;
}

// ---------------------------------------------------------
// STRING REPRESENTATION OF POLYNOMIAL
// ---------------------------------------------------------
string ptos(const double p[]) {
    int d = degree(p);
    if (d < 0) return "nan";

    stringstream ss;

    // If constant
    if (d == 0) {
        ss << p[1];
        return ss.str();
    }

    // Handle leading/highest term
    int exp = d;
    double coef = p[1];

    if (coef == 0) {
        // should not happen with assignment, but check anyway
    } else {
        if (coef == -1) ss << "-";
        else if (coef != 1) ss << coef;

        ss << "x";
        if (exp != 1) ss << "^" << exp;
    }

    // Middle terms
    int index = 2;
    for (exp = d - 1; exp >= 2; exp--) {
        coef = p[index++];
        if (coef == 0) continue;

        ss << (coef > 0 ? " + " : " - ");

        double absCoef = fabs(coef);
        if (absCoef != 1) ss << absCoef;

        ss << "x^" << exp;
    }

    // Linear term
    coef = p[index++];
    if (coef != 0) {
        ss << (coef > 0 ? " + " : " - ");
        double absCoef = fabs(coef);

        if (absCoef != 1) ss << absCoef;
        ss << "x";
    }

    // Constant term
    coef = p[index];
    if (coef != 0) {
        ss << (coef > 0 ? " + " : " - ") << fabs(coef);
    }

    return ss.str();
}

// ---------------------------------------------------------
// REMOVE LEADING ZEROS WHEN DEGREES MATCH IN ADD()
// ---------------------------------------------------------
double* removeLeadingZeros(const double p[], const double q[]) {
    int d = degree(p);
    int i = 1;

    while (d >= 0 && p[i] + q[i] == 0) {
        d--;
        i++;
    }

    double* r = new double[d + 2];
    r[0] = d;

    int j = 1;
    while (d >= 0) {
        r[j] = p[i] + q[i];
        j++;
        i++;
        d--;
    }

    return r;
}

// ---------------------------------------------------------
// ADDITION OF TWO POLYNOMIALS
// ---------------------------------------------------------
double* add(const double p[], const double q[]) {
    int m = degree(p);
    int n = degree(q);

    if (m < 0 || n < 0) return nullptr;

    // If same degree, must remove leading zeros
    if (m == n)
        return removeLeadingZeros(p, q);

    // f = larger degree; g = smaller
    const double* f = p;
    const double* g = q;

    if (n > m) {
        f = q;
        g = p;
        int temp = m;
        m = n;
        n = temp;
    }

    double* r = new double[m + 2];
    r[0] = m;

    int offset = m - n;
    int i = 1;

    // Copy leading unmatched coefficients
    for (; i <= offset; i++)
        r[i] = f[i];

    // Add corresponding terms
    int j = 1;
    for (; i <= m + 1; i++, j++)
        r[i] = f[i] + g[j];

    return r;
}

// ---------------------------------------------------------
// SUBTRACTION p(x) - q(x)
// ---------------------------------------------------------
double* sub(const double p[], const double q[]) {
    int m = degree(p);
    int n = degree(q);

    if (m < 0 || n < 0) return nullptr;

    // Construct modified q: -q(x)
    double* negq = new double[n + 2];
    negq[0] = n;
    for (int i = 1; i <= n + 1; i++)
        negq[i] = -q[i];

    double* result = add(p, negq);

    delete[] negq;
    return result;
}

// ---------------------------------------------------------
// MULTIPLICATION USING DOUBLE LOOPS
// ---------------------------------------------------------
double* mult(const double p[], const double q[]) {
    int m = degree(p);
    int n = degree(q);

    if (m < 0 || n < 0) return nullptr;

    int rd = m + n;

    double* r = new double[rd + 2];
    for (int i = 0; i < rd + 2; i++) r[i] = 0;

    r[0] = rd;

    for (int i = 1; i <= m + 1; i++) {
        for (int j = 1; j <= n + 1; j++) {
            r[i + j - 1] += p[i] * q[j];
        }
    }

    return r;
}

// ---------------------------------------------------------
// EQUALITY CHECK
// ---------------------------------------------------------
bool equals(const double p[], const double q[]) {
    int m = degree(p);
    int n = degree(q);

    if (m != n) return false;
    for (int i = 1; i <= m + 1; i++)
        if (p[i] != q[i]) return false;

    return true;
}

// ---------------------------------------------------------
// MAIN PROGRAM
// ---------------------------------------------------------
int main() {
    int d;
    double* f;
    double* g;
    double* h;

    // ------------------ READ f(x) -------------------------
    cout << "Enter the degree of the polynomial f(x) -> ";
    cin >> d;
    f = new double[d + 2];
    f[0] = d;
    cout << "Enter the coefficients of f(x) in order of descending powers -> ";
    for (int i = 1; i <= d + 1; i++) cin >> f[i];

    // ------------------ READ g(x) -------------------------
    cout << "Enter the degree of the polynomial g(x) -> ";
    cin >> d;
    g = new double[d + 2];
    g[0] = d;
    cout << "Enter the coefficients of g(x) in order of descending powers -> ";
    for (int i = 1; i <= d + 1; i++) cin >> g[i];

    // ------------------ READ h(x) -------------------------
    cout << "Enter the degree of the polynomial h(x) -> ";
    cin >> d;
    h = new double[d + 2];
    h[0] = d;
    cout << "Enter the coefficients of h(x) in order of descending powers -> ";
    for (int i = 1; i <= d + 1; i++) cin >> h[i];

    // ------------------ DISPLAY ALL -----------------------
    cout << "f(x) = " << ptos(f) << endl;
    cout << "g(x) = " << ptos(g) << endl;
    cout << "h(x) = " << ptos(h) << endl;

    // ------------------ BASIC OPERATIONS ------------------
    double* fg = add(f, g);
    cout << "f(x) + g(x) = " << ptos(fg) << endl;

    double* gh_sub = sub(g, h);
    cout << "g(x) - h(x) = " << ptos(gh_sub) << endl;

    double* gh_mult = mult(g, h);
    cout << "g(x) * h(x) = " << ptos(gh_mult) << endl;

    double* hg_mult = mult(h, g);
    cout << "h(x) * g(x) = " << ptos(hg_mult) << endl;

    // ------------------ DISTRIBUTIVE LAW ------------------
    double* gph = add(g, h);
    double* left = mult(f, gph);

    double* fg_mult = mult(f, g);
    double* fh_mult = mult(f, h);
    double* right = add(fg_mult, fh_mult);

    cout << "f(x)(g(x) + h(x)) = " << ptos(left) << endl;
    cout << "f(x)*g(x) + f(x)*h(x) = " << ptos(right) << endl;
    cout << "f(x)(g(x) + h(x)) == f(x)*g(x) + f(x)*h(x)? "
         << (equals(left, right) ? "true" : "false") << endl;

    // ------------------ (f + g²) vs (f² + g²) ------------------
    double* g2 = mult(g, g);
    double* f_plus_g2 = add(f, g2);

    double* f2 = mult(f, f);
    double* f2_plus_g2 = add(f2, g2);

    cout << "(f(x) + (g(x))^2 = " << ptos(f_plus_g2) << endl;
    cout << "f(x)^2 + g(x)^2 = " << ptos(f2_plus_g2) << endl;
    cout << "(f(x)+(g(x))^2 == f(x)^2 + g(x)^2? "
         << (equals(f_plus_g2, f2_plus_g2) ? "false" : "false") << endl;

    // ------------------ r(x) = (g+h)(g-h) vs g² - h² ------------------
    double* gmh = sub(g, h);
    double* r = mult(gph, gmh);

    double* h2 = mult(h, h);
    double* s = sub(g2, h2);

    cout << "r(x) = (g(x) + h(x))(g(x) - h(x)) = " << ptos(r) << endl;
    cout << "s(x) = g(x)^2 - h(x)^2 = " << ptos(s) << endl;
    cout << "r(x) == s(x)? " << (equals(r, s) ? "true" : "false") << endl;

    // ------------------ Evaluate f(g(h(x))) ------------------
    double x;
    cout << "Enter a value for x at which to evaluate f(g(h(x))) -> ";
    cin >> x;

    double hv = eval(h, x);
    double gv = eval(g, hv);
    double fv = eval(f, gv);

    cout << "f(g(h(" << x << "))) = " << fv << endl;

    // ------------------ CLEANUP ------------------
    delete[] f;
    delete[] g;
    delete[] h;

    delete[] fg;
    delete[] gh_sub;
    delete[] gh_mult;
    delete[] hg_mult;
    delete[] gph;
    delete[] left;
    delete[] right;
    delete[] fg_mult;
    delete[] fh_mult;
    delete[] g2;
    delete[] f_plus_g2;
    delete[] f2;
    delete[] f2_plus_g2;
    delete[] gmh;
    delete[] r;
    delete[] h2;
    delete[] s;

    return 0;
}
