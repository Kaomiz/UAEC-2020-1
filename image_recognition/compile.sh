#!/bin/bash
cd src
gcc -Wall -O3 -o preprocess preprocess.c \
	`pkg-config --cflags --libs MagickWand`
gcc -Wall -O3 -o train train.c -lfann
mv preprocess ../
mv train ../
