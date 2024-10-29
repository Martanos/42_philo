#!/bin/bash
\
NAME=$1
\
OUTPUT_DIR=$2
\

\
# Single philosopher test
\
./$NAME 1 800 200 200 > $OUTPUT_DIR/single.txt
\
# Even philosophers test
\
./$NAME 4 410 200 200 > $OUTPUT_DIR/even.txt
\
# Odd philosophers test
\
./$NAME 5 410 200 200 > $OUTPUT_DIR/odd.txt
