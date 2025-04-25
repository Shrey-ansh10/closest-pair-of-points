#include "ClosestPair.h"
#include <float.h>
#include <memory>
#include <algorithm>

// ALG1: Brute Force O(n²) algorithm
ClosestPair::Result ClosestPair::bruteForce(const std::vector<Point>& points) {
    int n = points.size();
    if (n < 2) {
        return Result(); // Not enough points
    }
    
    Result result;
    result.distance = std::numeric_limits<double>::max(); // setting min distance to max(infinity)
    
    // Compare all pairs of points
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            double dist = Point::distance(points[i], points[j]); // calculating distance using point.h
            if (dist < result.distance) {
                result.distance = dist;
                result.idx1 = points[i].id;
                result.idx2 = points[j].id;
            }
        }
    }
    
    return result;
}

// ALG2: Divide and Conquer O(n log n) algorithm
ClosestPair::Result ClosestPair::divideAndConquer(const std::vector<Point>& points) {
    int n = points.size();
    if (n < 2) {
        return Result(); // Not enough points
    }
    
    // Construct Px and Py - exactly as in pseudocode
    std::vector<Point> Px = points;
    std::vector<Point> Py = points;
    
    // Sort points by x-coordinate and y-coordinate
    std::sort(Px.begin(), Px.end(), compareX);
    std::sort(Py.begin(), Py.end(), compareY);
    
    // Call recursive function (p0*, p1*) = Closest-Pair-Rec(Px, Py)
    return closestPairRec(Px, Py);
}

// Recursive function following the pseudocode: Closest-Pair-Rec(Px, Py)
ClosestPair::Result ClosestPair::closestPairRec(
    const std::vector<Point>& Px, 
    const std::vector<Point>& Py) {
    
    int n = Px.size();
    
    // Base case: if |P| ≤ 3, find the closest pair by measuring all pairwise distances
    if (n <= 3) {
        return bruteForce(Px);
    }
    
    // Divide points into left half (Q) and right half (R)
    int mid = n / 2;
    double midX = Px[mid-1].x;  // Use the x-coordinate of the last point in Q
    
    // Construct Qx, Qy, Rx, Ry in O(n) time
    std::vector<Point> Qx, Qy, Rx, Ry;
    Qx.reserve(mid);
    Rx.reserve(n - mid);
    
    // Qx = first half of Px
    for (int i = 0; i < mid; i++) {
        Qx.push_back(Px[i]);
    }
    
    // Rx = second half of Px
    for (int i = mid; i < n; i++) {
        Rx.push_back(Px[i]);
    }
    
    // Partition Py into Qy and Ry based on x-coordinate
    for (const auto& point : Py) {
        if (point.x <= midX && Qy.size() < mid) {
            Qy.push_back(point);
        } else {
            Ry.push_back(point);
        }
    }
    
    // (q0*, q1*) = Closest-Pair-Rec(Qx, Qy)
    Result qResult = closestPairRec(Qx, Qy);
    
    // (r0*, r1*) = Closest-Pair-Rec(Rx, Ry)
    Result rResult = closestPairRec(Rx, Ry);
    
    // δ = min(d(q0*, q1*), d(r0*, r1*))
    double delta = std::min(qResult.distance, rResult.distance);
    Result result = (qResult.distance <= rResult.distance) ? qResult : rResult;
    
    // L = {(x, y): x = x*} - midpoint line
    double x_star = midX;
    
    // S = points in P within distance δ of L
    std::vector<Point> S;
    for (const auto& point : Py) {
        if (std::abs(point.x - x_star) < delta) {
            S.push_back(point);
        }
    }
    
    // Construct Sy (it's already sorted by y)
    std::vector<Point> Sy = S;
    
    // Check pairs in the strip
    int m = Sy.size();
    for (int i = 0; i < m; i++) {
        // Check at most 15 points ahead as per pseudocode
        for (int j = i + 1; j < m && j <= i + 15 && (Sy[j].y - Sy[i].y) < delta; j++) {
            double dist = Point::distance(Sy[i], Sy[j]);
            if (dist < delta) {
                delta = dist;
                result.distance = dist;
                result.idx1 = Sy[i].id;
                result.idx2 = Sy[j].id;
            }
        }
    }
    
    // Return the closest pair found
    return result;
}

// Function to find the closest pair in the strip - note: this is now unused as strip processing is done in closestPairRec
ClosestPair::Result ClosestPair::stripClosest(const std::vector<Point>& strip, double d) {
    Result result;
    result.distance = d;
    
    // Strip is already sorted by y-coordinate
    int size = strip.size();
    
    // Compare distances of points in the strip
    for (int i = 0; i < size; i++) {
        // Check at most 15 points ahead as per pseudocode (originally 7 in our optimized version)
        for (int j = i + 1; j < size && j <= i + 15 && (strip[j].y - strip[i].y) < d; j++) {
            double dist = Point::distance(strip[i], strip[j]);
            if (dist < result.distance) {
                result.distance = dist;
                result.idx1 = strip[i].id;
                result.idx2 = strip[j].id;
            }
        }
    }
    
    return result;
} 