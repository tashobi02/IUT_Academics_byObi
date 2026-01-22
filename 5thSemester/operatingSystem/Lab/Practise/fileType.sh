#!/bin/bash

# Check if filename argument is provided
if [ $# -eq 0 ]; then
    echo "Usage: $0 <filename>"
    exit 1
fi

filename="$1"

# Extract extension
extension="${filename##*.}"

# Determine file type using case
case "$extension" in
    txt)
        echo "Text file"
        ;;
    c)
        echo "C source file"
        ;;
    cpp)
        echo "C++ source file"
        ;;
    py)
        echo "Python script"
        ;;
    sh)
        echo "Bash script"
        ;;
    java)
        echo "Java source file"
        ;;
    html|htm)
        echo "HTML file"
        ;;
    jpg|jpeg|png)
        echo "Image file"
        ;;
    pdf)
        echo "PDF document"
        ;;
    *)
        echo "Unknown or unsupported file type"
        ;;
esac
