#!/bin/bash

# Assuming your program is named "your_program"
PROGRAM=".././a.out"

# Input file with 100 lines (replace "input.txt" with your actual file name)
INPUT_FILE="suites/ALL_TESTS.txt"

# Loop through each line in the file and run the program
while IFS= read -r line; do
    # Run your program with the current line as an argument
    $PROGRAM "$line"
done < "$INPUT_FILE"

