#!/bin/bash

echo "Testing exit: "
echo test -f ../README.md; (echo hello && echo goodbye) && exit