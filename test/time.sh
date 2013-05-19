#!/bin/bash

# aditional data processing commands here.

gnuplot << EOP

set terminal jpeg font arial 14 size 800, 600
set output "time_c.jpg"

set xlabel "Calls"
set ylabel "Time (mks)"

plot "zip_first" using 9 title "First fit", \
     "zip_best" using 9 title "Best fit", \
     "zip_worst" using 9 title "Worst fit", \
     "zip_glibc" using 11 title "Glibc"
     
EOP
