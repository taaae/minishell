#!/bin/zsh

# The directory to start searching from, replace '/path/to/your/directory' with your actual directory path
root_dir="$HOME/Desktop/minishell/src"

# Iterate over each file found by find
find "$root_dir" -type f | while read file; do
  # Use a temporary file to store the formatted content
  
  # Format the file and write the output to the temporary file
  python3 -m c_formatter_42 < "$file" > "$file"
  
  # Replace the original file with the formatted file
  
  echo "Processed $file"
done
