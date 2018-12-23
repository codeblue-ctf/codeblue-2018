#!/bin/bash
ulimit -s unlimited
./smth_revenge < `dirname $0`/payload | hexdump -C | grep -B 1 -A 1 FTCBC
