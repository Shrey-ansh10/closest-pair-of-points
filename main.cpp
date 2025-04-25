#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <unordered_set>
#include <sstream>
#include <memory>
#include "Point.h"
#include "ClosestPair.h"

// Function to generate n unique random points
std::unique_ptr<std::vector<Point>> generateRandomPoints(int n, int seed = 42) {
    std::mt19937 gen(seed);
    std::uniform_real_distribution<> dist(0.0, 1000.0); // Range for x,y coordinates
    
    auto points = std::make_unique<std::vector<Point>>();
    points->reserve(n); // Pre-allocate memory
    
    std::unordered_set<std::string> pointSet; // To track unique points
    
    for (int i = 0; i < n; i++) {
        double x, y;
        std::string pointStr;
        
        // Generate unique point
        do {
            x = dist(gen);
            y = dist(gen);
            
            // Create a string representation of the point for uniqueness check
            std::ostringstream oss;
            oss << std::fixed << std::setprecision(6) << x << "," << y;
            pointStr = oss.str();
            
        } while (pointSet.find(pointStr) != pointSet.end());
        
        pointSet.insert(pointStr);
        points->push_back(Point(i, x, y));
    }
    
    return points;
}

// Function to measure execution time of an algorithm
template<typename Func>
double measureExecutionTime(Func algorithm, const std::vector<Point>& points) {
    auto start = std::chrono::high_resolution_clock::now();
    auto result = algorithm(points);
    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double, std::milli> duration = end - start;
    
    std::cout << "Closest pair: Points " << result.idx1 << " and " << result.idx2 
              << " with distance " << result.distance << std::endl;
    
    return duration.count();
}

int main() {
    // Set up output file for results
    std::ofstream outFile("results.csv");
    outFile << "n,ALG1_Time_ms,ALG2_Time_ms" << std::endl;
    
    // Number of iterations for each input size
    const int iterations = 10;
    
    // Input sizes to test
    std::vector<int> inputSizes = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
    
    // Maximum input size for brute force algorithm - set to 100000 to ensure it runs for all input sizes
    const int maxBruteForceSize = 100000;
    
    // For each input size
    for (int n : inputSizes) {
        double totalTimeALG1 = 0.0;
        double totalTimeALG2 = 0.0;
        bool skipBruteForce = (n > maxBruteForceSize);
        
        std::cout << "\nTesting with n = " << n << std::endl;
        std::cout << "--------------------------------------" << std::endl;
        
        // Run multiple iterations
        for (int iter = 0; iter < iterations; iter++) {
            std::cout << "Iteration " << (iter + 1) << ":" << std::endl;
            
            // Generate random points (use different seed for each iteration)
            auto pointsPtr = generateRandomPoints(n, 42 + iter);
            
            if (!skipBruteForce) {
                // Measure execution time for brute force algorithm
                std::cout << "Running ALG1 (Brute Force)..." << std::endl;
                double timeALG1 = measureExecutionTime([](const std::vector<Point>& p) { 
                    return ClosestPair::bruteForce(p); 
                }, *pointsPtr);
                
                std::cout << "ALG1 Time: " << timeALG1 << " ms" << std::endl;
                totalTimeALG1 += timeALG1;
            } else {
                std::cout << "Skipping ALG1 (Brute Force) for large input size (n > " 
                          << maxBruteForceSize << ")..." << std::endl;
            }
            
            // Measure execution time for divide-and-conquer algorithm
            std::cout << "Running ALG2 (Divide and Conquer)..." << std::endl;
            double timeALG2 = measureExecutionTime([](const std::vector<Point>& p) { 
                return ClosestPair::divideAndConquer(p); 
            }, *pointsPtr);
            
            std::cout << "ALG2 Time: " << timeALG2 << " ms" << std::endl;
            totalTimeALG2 += timeALG2;
            
            // Force cleanup of points to free memory before next iteration
            pointsPtr.reset();
        }
        
        // Calculate averages
        double avgTimeALG1 = skipBruteForce ? -1.0 : (totalTimeALG1 / iterations);
        double avgTimeALG2 = totalTimeALG2 / iterations;
        
        std::cout << "\nResults for n = " << n << ":" << std::endl;
        if (!skipBruteForce) {
            std::cout << "Average ALG1 (Brute Force) Time: " << avgTimeALG1 << " ms" << std::endl;
        } else {
            std::cout << "Average ALG1 (Brute Force) Time: Skipped (too large)" << std::endl;
        }
        std::cout << "Average ALG2 (Divide and Conquer) Time: " << avgTimeALG2 << " ms" << std::endl;
        
        // Write to output file
        outFile << n << "," << (skipBruteForce ? "" : std::to_string(avgTimeALG1)) << "," << avgTimeALG2 << std::endl;
    }
    
    outFile.close();
    std::cout << "\nResults have been written to results.csv" << std::endl;
    
    return 0;
} 