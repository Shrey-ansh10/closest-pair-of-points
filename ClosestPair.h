#ifndef CLOSEST_PAIR_H
#define CLOSEST_PAIR_H

#include <vector>
#include <algorithm>
#include <limits>
#include <chrono>
#include "Point.h"

class ClosestPair { // creating class
public:
    // Result structure to hold the pair of closest points and their distance 
    struct Result {
        int idx1;           // Index of first point
        int idx2;           // Index of second point
        double distance;    // Distance between points
        
        Result() : idx1(-1), idx2(-1), distance(std::numeric_limits<double>::max()) {} // default constructor, sets the initial distance to max value of double data-type
        Result(int i, int j, double d) : idx1(i), idx2(j), distance(d) {} //custom constructor
    };
    
    // Brute force algorithm (ALG1) - function decleration, defination in ClosestPair.cpp file
    static Result bruteForce(const std::vector<Point>& points); 
    
    // Divide and conquer algorithm (ALG2)
    static Result divideAndConquer(const std::vector<Point>& points);
    
private:
    // Helper functions for divide and conquer algorithm. This recursive function takes sorted list of points
    static Result closestPairRec(const std::vector<Point>& Px, // takes points sorted by x-axis
                                const std::vector<Point>& Py); // takes points sorted by y-axis
                                             
    static Result stripClosest(const std::vector<Point>& strip, double d); // helper function to solve strip part
    
    // Comparator functions for sorting points
    static bool compareX(const Point& a, const Point& b) { //Sort points based on x-coordinates.
        return a.x < b.x;
    }
    
    static bool compareY(const Point& a, const Point& b) { //Sort points based on y-coordinates.
        return a.y < b.y;
    }
};

#endif // CLOSEST_PAIR_H 