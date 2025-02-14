set terminal pngcairo size 800,600
set output 'box1D_grafico.png'
set title 'Movimiento de una partícula en una caja 1D'
set xlabel 'Tiempo (s)'
set ylabel 'Posición (m)'
set grid
plot 'box1D_datos.dat' using 1:2 with lines title 'Posición vs Tiempo'
