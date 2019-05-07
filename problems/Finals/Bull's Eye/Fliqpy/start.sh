#!/bin/sh
LD_PRELOAD=./libc-2.23.so stdbuf -i0 -o0 -e0 ./fliqpy
