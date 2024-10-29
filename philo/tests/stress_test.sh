#!/bin/bash
\
NAME=$1
\
OUTPUT_DIR=$2
\

\
# High load test
\
./$NAME 20 800 200 200 10 > $OUTPUT_DIR/stress1.txt
\
# Maximum values test
\
./$NAME 200 60000 60000 60000 1 > $OUTPUT_DIR/stress2.txt
\
# Minimum values test
\
./$NAME 2 60 60 60 1 > $OUTPUT_DIR/stress3.txt
