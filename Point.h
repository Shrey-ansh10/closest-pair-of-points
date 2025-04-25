#ifndef POINT_H
#define POINT_H

#include <cmath>
#include <iostream>

struct Point {
    int id;     // Point index/identifier
    double x;   // x-coordinate
    double y;   // y-coordinate
    
    // Default constructor
    Point() : id(-1), x(0), y(0) {}
    
    // Constructor with coordinates
    Point(int _id, double _x, double _y) : id(_id), x(_x), y(_y) {}
    
    // Calculate Euclidean distance between two points
    static double distance(const Point& p1, const Point& p2) {
        return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + 
                         (p1.y - p2.y) * (p1.y - p2.y));
    }
    
    // Operator overloading for output
    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "Point " << p.id << " (" << p.x << ", " << p.y << ")";
        return os;
    }
};

#endif // POINT_H 