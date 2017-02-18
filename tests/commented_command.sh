#!/bin/sh

echo "Testing commented command: A pure comment"
echo #ls -a; echo hello; git status; exit; asdfjkl

echo "Testing commented command: Two arguments and a comment"
echo ls -a; echo hello; #git status; exit; asdjfkl

echo "Testing commented command: Comment after exit"
echo ls -a; echo hello; git status; exit #asdjfkl