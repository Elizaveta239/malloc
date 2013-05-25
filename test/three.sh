#!/bin/bash

# aditional data processing commands here.

gnuplot << EOP

set terminal jpeg font arial 10 size 750,550
set output "size_zip_worst.jpg"

set xlabel "Calls" font "Arial,15"
set ylabel "Size (bytes)" font "Arial,15"
set key top left

plot "zip_worst_c" using 1 title "Size of Heap" with lines lw 2, \
     "zip_worst_c" using 2 title "Free space" with lines lw 2, \
     "zip_worst_c" using 6 title "Max free block" with lines lw 2

EOP
