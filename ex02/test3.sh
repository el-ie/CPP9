#!/bin/bash
shuf -i 1-$1 -n$1 | xargs ./PmergeMe
