#!/bin/bash

echo "Testing hello && mkdir test"
echo hello && mkdir test
echo "Testing world || git status"
echo world || git status
echo "Testing ls -a ; echo hello"
echo ls -a ; echo hello
echo "Testing ls -a; echo hello && mkdir test || echo world; git status"
echo ls -a; echo hello && mkdir test || echo world; git status
echo exit