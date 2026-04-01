#!/usr/bin/bash

g++ -g ./src/main.cpp ./src/sorting/counting_sort.cpp ./src/sorting/radix_sort.cpp ./src/io/read.cpp ./src/io/write.cpp ./src/classes/Encoder.cpp ./src/classes/RadixEncoder.cpp -I./include -o ./build/main