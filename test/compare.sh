#!/bin/bash

# aditional data processing commands here.

gnuplot << EOP


datafile = "worst_st"
set terminal jpeg font arial 10 size 750,550
set output "worst.jpg"
set xlabel "Calls" font "Arial,15"
set ylabel "Fragmentation (%)" font "Arial,15"
set key top left

plot datafile using 7 title "Fragmentation" with lines lw 4
#     datafile using 2 title "Free space" with lines lw 4, \
#     datafile using 6 title "Max free block" with lines lw 4

EOP
