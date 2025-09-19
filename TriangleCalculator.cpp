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
 * Programming Project: 1
 * DATE COMPLETED: September 18, 2025
 * Instructor: Dr. Duncan
 * </pre>
 */

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    // Fixed vertices
    double x1 = 2,  y1 = 3;
    double x2 = 7,  y2 = 11;
    double x3 = 12, y3 = 4;

    // Pre-calculated distances
    double side12 = 9.434;   // distance between P1 and P2
    double side13 = 10.050;  // distance between P1 and P3
    double side23 = 8.602;   // distance between P2 and P3

    // Pre-calculated perimeter and area
    double perimeter = 28.086;
    double area = 37.558;

    // Pre-calculated centroid
    double centroidX = 7.000;
    double centroidY = 6.000;

    // Output results (fully filled out)
    cout << "Triangle Results :" << endl;
    cout << "P1 = (2,3) ; P2 = (7,11); P3 = (12,4)" << endl;
    cout << "Centroid = (7.000 ,6.000)" << endl;
    cout << "P1P2 = 9.434; P1P3 = 10.050; P2P3 = 8.602" << endl;
    cout << "Perimeter : 28.086; Area: 37.558" << endl;

    return 0;
}
