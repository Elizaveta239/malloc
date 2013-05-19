#!/bin/bash

# aditional data processing commands here.

gnuplot << EOP

datafile = "st2"
set terminal jpeg font arial 10 size 700,550
set output "st.jpg"
set xlabel "Calls"
set ylabel "Fragmentation (%)"

plot datafile using 7 with lines lw 4

EOP
