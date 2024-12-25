#!/bin/bash

data="./func_tests/data"
pos_case="./func_tests/scripts/pos_case.sh"
neg_case="./func_tests/scripts/neg_case.sh"

for test_name in "$data"/*_args.txt; do
    num=$(basename "$test_name" | cut -c -6)

    if [[ "$test_name" =~ "pos" ]]; then
        "$pos_case" "$test_name" "${data}/${num}_out.txt" 
        result=$?
    elif [[ "$test_name" =~ "neg" ]]; then
        "$neg_case" "$test_name" "${data}/${num}_out.txt" 
        result=$?
    else
        continue
    fi

    echo -n "Test ${num}: "

    if [ "$result" != "0" ]; then
        echo "failed"
    else
        echo "passed"
    fi
done

exit 0
