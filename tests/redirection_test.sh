#!/bin/sh

echo "Testing output redirection with >"
echo ls -a > file1

echo "Testing output redirection with >>"
echo hello there >> file1

echo "Testing input redirection with <"
echo cat < file1

echo "Testing pipe"
echo ls -a | grep Make 

echo "Testing line from Assignment 4"
echo cat < existingInputFile | tr A-Z a-z | tee newOutputFile1 | tr a-z
A-Z > newOutputFile2

echo "Testing multiple lines"
echo how are you >> file1 | tr a-z A-Z