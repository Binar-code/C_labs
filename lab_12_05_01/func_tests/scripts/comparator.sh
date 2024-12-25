#!/bin/bash

file1=$1
file2=$2

numbers1=$(grep -oE '[0-9]+' "$file1")
numbers2=$(grep -oE '[0-9]+' "$file2")

if [ "$numbers1" == "$numbers2" ]; then
    exit 0
else
    exit 1
fi
