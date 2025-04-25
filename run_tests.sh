#!/bin/bash

# Create build directory if it doesn't exist
mkdir -p build
cd build

# Configure with CMake
echo "Configuring with CMake..."
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build
echo "Building..."
cmake --build . --config Release

# Check if build was successful
if [ $? -eq 0 ]; then
    echo "Build successful! Running tests..."
    # Run the executable
    ./ClosestPairOfPoints
    
    # Check if results.csv was created
    if [ -f "results.csv" ]; then
        echo "Results have been saved to build/results.csv"
        
        # Optional: Visualize results
        echo "To visualize results, you can import the CSV file into a spreadsheet application"
    else
        echo "Error: results.csv file was not created."
    fi
else
    echo "Build failed. Please check the error messages above."
fi 