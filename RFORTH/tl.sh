#!/bin/bash

echo "Enter file extensions (separated by spaces, e.g., \".c .py .txt\") or press Enter for all files:"
read -r extensions

if [ -z "$extensions" ]; then
    extensions="*"
fi

# Check if the user entered a space followed by a period
all_files=0
if [[ "$extensions" == *". " ]]; then
    all_files=1
    extensions="*"
fi

# Redirect the output to a temporary file
{
    echo "Listing all files with extensions: $extensions"
    echo

    # The for loop iterates over directories, excluding the build directory
    for d in $(find . -type d -not -path "./build*"); do
        # Output all files if the user entered ". "
        if [ "$all_files" -eq 1 ]; then
            for e in "$d"/*; do
                echo "Filename: $e"
                cat "$e" 2>/dev/null
                echo
            done
        else
            # Output files based on extensions
            for e in $extensions; do
                for f in "$d"/*"$e"; do
                    echo "Filename: $f"
                    cat "$f" 2>/dev/null
                    echo
                done
            done
        fi
    done
} > output.txt

# Display the contents of the temporary file
cat output.txt

# Delete the temporary file
rm output.txt

echo "Listing complete."
