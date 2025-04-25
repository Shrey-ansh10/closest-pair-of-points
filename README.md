# Closest Pair of Points Analysis

This project implements and compares two algorithms for solving the Closest Pair of Points problem:
1. Brute Force approach (ALG1) - O(n²) time complexity
2. Divide and Conquer approach (ALG2) - O(n log n) time complexity

## Problem Statement
Given n points P1, P2, …, Pn in a plane, the objective is to find the pair of points that are closest to each other. The algorithm returns the indices i and j of the two closest points, Pi and Pj.

## Project Structure

```
.
├── CMakeLists.txt          # CMake build configuration
├── ClosestPair.cpp         # Implementation of both algorithms
├── ClosestPair.h           # Header file for the algorithms
├── Point.h                 # Definition of the Point class
├── README.md               # This file
├── install_dependencies.sh # Script to install Python dependencies
├── main.cpp                # Main testing framework
├── requirements.txt        # Python dependencies for visualization
├── run_tests.sh            # Script to build and run tests
└── visualize_results.py    # Python script for visualizing results
```

## Implementation Details

- The project is implemented in C++
- Runtime performance is measured for input sizes from 10,000 to 100,000 points (with increments of 10,000)
- Each input size is tested 10 times with different random point sets to get average performance
- Results are saved in CSV format for further analysis

## Building the Project

### Prerequisites
- C++ compiler with C++17 support
- CMake (version 3.10 or higher)
- Python 3 with pandas, matplotlib, and numpy (for visualization)

### Build Instructions

```bash
# Create a build directory
mkdir build
cd build

# Generate build files
cmake ..

# Build
cmake --build .
```

### Running the Program

#### Option 1: Manual Build and Run
```bash
# From the build directory
./ClosestPairOfPoints
```

#### Option 2: Using the Provided Script
```bash
# From the project root directory
./run_tests.sh
```

## Visualization

After running the tests, you can visualize the results using the provided Python script:

```bash
# Install required Python packages
pip install -r requirements.txt
# Or use the provided script
./install_dependencies.sh

# Run the visualization script
./visualize_results.py
```

The script will generate:
1. A comparison of running times between the two algorithms
2. The speedup ratio of divide and conquer over brute force
3. A comparison with theoretical complexity curves
4. A log-log scale plot that clearly shows the O(n²) vs O(n log n) complexity difference

The script automatically handles missing values for the brute force algorithm on large inputs by estimating them based on O(n²) complexity, showing these as dashed lines in the charts.

The visualizations will be saved as PNG files in the current directory.

## Output

The program will output the execution times to the console and generate a `results.csv` file with the following format:
```
n,ALG1_Time_ms,ALG2_Time_ms
10000,time1,time2
20000,time1,time2
...
```

## Analysis

The expected results should show:
- ALG1 (Brute Force) has O(n²) time complexity, so runtime increases quadratically with input size
- ALG2 (Divide and Conquer) has O(n log n) time complexity, so runtime increases more slowly

For large inputs, the divide-and-conquer approach should significantly outperform the brute force method.