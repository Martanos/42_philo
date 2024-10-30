#!/bin/bash

NAME=$1
OUTPUT_DIR=$2

if [ -z "$NAME" ] || [ -z "$OUTPUT_DIR" ]; then
    echo "Usage: $0 <program_name> <output_directory>"
    exit 1
fi

# Create output directory if it doesn't exist
mkdir -p "$OUTPUT_DIR"

# Function to run test and check exit status
run_test() {
    local test_name=$1
    local args=$2
    echo "Running $test_name..."
    
    # Run with thread sanitizer
    TSAN_OPTIONS="second_deadlock_stack=1" ./$NAME $args > "$OUTPUT_DIR/${test_name}.txt" 2>&1
    
    if [ $? -eq 0 ]; then
        echo "✓ $test_name completed successfully"
    else
        echo "✗ $test_name failed"
    fi
    echo
}

# Run tests
run_test "death_test" "4 200 210 200"
run_test "meal_count_test" "4 410 200 200 5"
run_test "rapid_cycle_test" "4 200 100 100"
