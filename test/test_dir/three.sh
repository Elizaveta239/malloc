#!/bin/bash

# aditional data processing commands here.

gnuplot << EOP

datafile = "st2"
set terminal jpeg font arial 10 size 750,550
set output "triple.jpg"
set xlabel "Calls" font "Arial,15"
set ylabel "Size (bytes)" font "Arial,15"
set key top left

plot datafile using 1 title "Size of Heap" with lines lw 4, \
     datafile using 2 title "Free space" with lines lw 4, \
     datafile using 6 title "Max free block" with lines lw 4

EOP
