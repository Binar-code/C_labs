#!/bin/bash

file_args="$1"
file_etalon="$2"
temp_out="./func_tests/data/temp_out.txt"

app="./app.exe"
comparator="./func_tests/scripts/comparator.sh"

touch "./func_tests/data/temp_out.txt"

args=""

file_content=$(<"$file_args")

for word in $file_content; do
    args="$args $word"
done

args=$(echo "$args" | sed 's/[[:space:]]*$//')

app=$app" $args"
$app
result=$?

if [ "$result" != "0" ]; then
    exit 0
fi

exit 1
