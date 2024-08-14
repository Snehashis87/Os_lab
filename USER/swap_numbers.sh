#!/bin/bash

# Check if two arguments are provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <number1> <number2>"
    exit 1
fi

# Read the numbers from the command line arguments
num1=$1
num2=$2

# Display the original numbers
echo "Original numbers:"
echo "num1 = $num1"
echo "num2 = $num2"

# Swap the numbers using a temporary variable
temp=$num1
num1=$num2
num2=$temp

# Display the swapped numbers
echo "Swapped numbers:"
echo "num1 = $num1"
echo "num2 = $num2"

