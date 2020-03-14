#!/bin/bash
# Big script

NAME="test"
FILENAME="data"
FILES="*.cpp"
FLAGS="-std=c++11 -Wall -pthread -o $NAME"


g++ $FILES $FLAGS
./$NAME > $FILENAME
# gnuplot # plot "$FILENAME" w lp
