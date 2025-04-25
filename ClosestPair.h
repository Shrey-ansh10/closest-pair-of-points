#ifndef CLOSEST_PAIR_H
#define CLOSEST_PAIR_H

#include <vector>
#include <algorithm>
#include <limits>
#include <chrono>
#include "Point.h"

class ClosestPair {
public:
    // Result structure to hold the pair of closest points and their distance
    struct Result {
        int idx1;           // Index of first point
        int idx2;           // Index of second point
        double distance;    // Distance between points
        
        Result() : idx1(-1), idx2(-1), distance(std::numeric_limits<double>::max()) {}
        Result(int i, int j, double d) : idx1(i), idx2(j), distance(d) {}
    };
    
    // Brute force algorithm (ALG1)
    static Result bruteForce(const std::vector<Point>& points);
    
    // Divide and conquer algorithm (ALG2)
    static Result divideAndConquer(const std::vector<Point>& points);
    
private:
    // Helper functions for divide and conquer algorithm
    static Result closestPairRec(const std::vector<Point>& Px, 
                                const std::vector<Point>& Py);
                                             
    static Result stripClosest(const std::vector<Point>& strip, double d);
    
    // Comparator functions for sorting points
    static bool compareX(const Point& a, const Point& b) {
        return a.x < b.x;
    }
    
    static bool compareY(const Point& a, const Point& b) {
        return a.y < b.y;
    }
};

#endif // CLOSEST_PAIR_H 