#!/bin/bash
cd src
gcc -Wall -O3 -o preprocess preprocess.c \
	`pkg-config --cflags --libs MagickWand`
mv preprocess ../
