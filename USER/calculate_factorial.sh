#!/bin/bash

# Function to calculate the factorial
factorial() {
    local num=$1
    local result=1

    # Loop to calculate factorial
    for (( i=1; i<=num; i++ )); do
        result=$(( result * i ))
    done

    echo $result
}

# Check if the user has provided an input
if [ $# -eq 0 ]; then
    echo "Usage: $0 <number>"
    exit 1
fi

# Read the number from the command line argument
number=$1

# Check if the input is a valid non-negative integer
if ! [[ $number =~ ^[0-9]+$ ]]; then
    echo "Error: Please enter a valid non-negative integer."
    exit 1
fi

# Calculate and display the factorial
factorial_result=$(factorial $number)
echo "The factorial of $number is $factorial_result."

