#!/bin/bash

# aditional data processing commands here.

gnuplot << EOP

set terminal jpeg font arial 14 size 800, 600
set output "fragment.jpg"

set xlabel "Calls"
set ylabel "Fragmentation (%)"

plot "zip_first" using 7 title "First fit" with lines lw 2, \
     "zip_best" using 7 title "Best fit" with lines lw 2, \
     "zip_worst" using 7 title "Worst fit" with lines lw 2

EOP
