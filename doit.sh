#!/bin/bash

set -e
rm -f a.out
gcc mat.c mymat.c handlemymat.c
echo "blah" | ./a.out
