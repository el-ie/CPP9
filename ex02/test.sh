#!/bin/bash

for i in {1..100}
do
output=$(shuf -i 1-1000 -n$i | xargs ./PmergeMe > error_log && tail -n 1 error_log)

if [ "$output" != "sorted" ]; then
	echo "ERROR, see error_log for more informations"
	exit
else
	rm error_log
	echo -n "."
fi
done
echo SUCESS
