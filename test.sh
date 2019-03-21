#!/bin/bash

DIR=$2
PROG=$1
VAL="valgrind --error-exitcode=15 --leak-check=full \
	--show-leak-kinds=all --errors-for-leak-kinds=all -q"
TOTAL=0
PASSED=0
FAILED=0

for f in $DIR/*.in ; do
	echo "">temp.out
    echo "">temp.err
	((TOTAL++))
	printf "Test [$TOTAL] ${f#*$DIR/} "
	if [ "${3}" == "-v" ]; then
		$VAL ./$PROG <$f 1>temp.out 2>temp.err
	else
		./$PROG <$f 1>temp.out 2>temp.err
	fi

	if [ "$(diff -q temp.out ${f%.in}.out)" != "" ] \
 	|| [ "$(diff -q temp.err ${f%.in}.err)" != "" ]; then
 		((FAILED++))
		printf "Failed\n"
	else
		((PASSED++))
		printf "Passed\n"
	fi
done

printf "$PASSED/$TOTAL Passed "
printf "$FAILED/$TOTAL Failed\n"

rm -f temp.out temp.err
