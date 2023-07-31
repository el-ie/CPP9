#!/bin/bash
shuf -i 1-2147483647 -n$1 | xargs ./PmergeMe
