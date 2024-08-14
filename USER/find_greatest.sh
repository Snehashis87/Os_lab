#!/bin/bash

# Check if three arguments are provided
if [ $# -ne 3 ]; then
    echo "Usage: $0 <number1> <number2> <number3>"
    exit 1
fi

# Read the numbers from the command line arguments
num1=$1
num2=$2
num3=$3

# Check if the input values are valid numbers
if ! [[ $num1 =~ ^-?[0-9]+$ ]] || ! [[ $num2 =~ ^-?[0-9]+$ ]] || ! [[ $num3 =~ ^-?[0-9]+$ ]]; then
    echo "Error: Please enter valid integers."
    exit 1
fi

# Find the greatest number
if [ $num1 -ge $num2 ] && [ $num1 -ge $num3 ]; then
    greatest=$num1
elif [ $num2 -ge $num1 ] && [ $num2 -ge $num3 ]; then
    greatest=$num2
else
    greatest=$num3
fi

# Display the result
echo "The greatest number among $num1, $num2, and $num3 is $greatest."

