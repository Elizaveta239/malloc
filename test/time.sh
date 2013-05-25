#!/bin/bash

# aditional data processing commands here.

gnuplot << EOP

set terminal jpeg font arial 14 size 800, 600
set output "time_gettime.jpg"

set xlabel "Calls"
set ylabel "Time (mks)"

plot "list_first" using 9 title "First fit", \
     "list_best" using 9 title "Best fit", \
     "list_worst" using 9 title "Worst fit", \
     "list_glibc" using 11 title "Glibc"
     
EOP
