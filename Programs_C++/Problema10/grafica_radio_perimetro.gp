reset

set datafile separator ','

set title "Radio-Perimetro"
set xlabel "Eje x"
set ylabel "Eje y"



plot 'area.csv' using 1:2 with linespoints
