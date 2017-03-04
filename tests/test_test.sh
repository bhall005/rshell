#!/bin/sh

echo "Testing single arguments: "
echo test -f ../README.md
echo [-f ../README.md]

echo "Testing multile arguments: "
echo test ../Makefile && echo hello
echo ls -a && [../Makefile]

echo "Testing incorrect flags: "
echo test -k /test
echo [-q /test]

echo "Testing incorrect paths: "
echo test -e /test/file/path
echo [-f /asdfjkl]
echo test -e /qwerty || echo hello
echo test -d /cs100; test -f /asn3; [-e /test]; echo goodbye


