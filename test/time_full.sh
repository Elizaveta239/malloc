#!/bin/bash

# aditional data processing commands here.

gnuplot << EOP

set terminal jpeg font arial 14 size 800, 600
set output "time_full.jpg"

set xlabel "Fullness (%)"
set ylabel "Time (ns)"

plot "list_first" using 8:9 title "First fit", \
     "list_best" using 8:9 title "Best fit", \
     "list_worst" using 8:9 title "Worst fit", \
     "list_glibc" using 12:11 title "Glibc"
EOP
