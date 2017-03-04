#!/bin/sh

echo "Testing single commands: "
echo (echo hello)
echo (ls -a)

echo "Testing muliple commands: "
echo (echo A && echo B) || (echo C && echo D)
echo (test -e /cs100 && echo A) && echo hello || echo goodbye
echo (test -e ../README.md && echo A && test -f /hw3) || (echo hello && ls -a)

echo "Testing unpaired parentheses: "
echo (echo A
echo (echo A && echo B) && echo C)
echo ls -a && () && echo hello