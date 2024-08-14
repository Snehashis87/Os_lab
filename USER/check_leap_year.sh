#!/bin/bash

# Check if the user has provided an input
if [ $# -eq 0 ]; then
    echo "Usage: $0 <year>"
    exit 1
fi

# Read the year from the command line argument
year=$1

# Check if the input is a valid number
if ! [[ $year =~ ^[0-9]{4}$ ]]; then
    echo "Error: Please enter a valid 4-digit year."
    exit 1
fi

# Check if the year is a leap year
if [ $((year % 4)) -eq 0 ]; then
    if [ $((year % 100)) -eq 0 ]; then
        if [ $((year % 400)) -eq 0 ]; then
            echo "$year is a leap year."
        else
            echo "$year is not a leap year."
        fi
    else
        echo "$year is a leap year."
    fi
else
    echo "$year is not a leap year."
fi

