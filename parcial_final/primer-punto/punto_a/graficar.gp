set terminal pngcairo size 800,600
set output 'triangulo_grafico.png'
set title 'Movimiento de una partícula en un triángulo equilátero'
set xlabel 'Posición X (m)'
set ylabel 'Posición Y (m)'
set grid
set xrange [0:10]
set yrange [0:8.66025]
plot 'triangulo_datos.dat' using 2:3 with lines title 'Trayectoria', \
     '-' with lines title 'Triángulo' 
0 0
10 0
5 8.66025
0 0
e
