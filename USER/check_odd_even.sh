#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Usage: $0 <number>"
    exit 1
fi

number=$1

if ! [[ $number =~ ^-?[0-9]+$ ]]; then
    echo "Error: Please enter a valid integer."
    exit 1
fi

if [ $((number % 2)) -eq 0 ]; then
    echo "$number is even."
else
    echo "$number is odd."
fi

