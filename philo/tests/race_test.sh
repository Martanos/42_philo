#!/bin/bash
\
NAME=$1
\
OUTPUT_DIR=$2
\

\
# Rapid death test
\
./$NAME 4 200 210 200 > $OUTPUT_DIR/race1.txt
\
# Simultaneous meals test
\
./$NAME 4 410 200 200 5 > $OUTPUT_DIR/race2.txt
\
# Quick succession test
\
./$NAME 4 200 100 100 > $OUTPUT_DIR/race3.txt
