set terminal gif animate delay 100 size 600,400
set output 'triangulo_animacion.gif'
set title 'Evolución de la posición en el tiempo'
set xlabel 'Posición X (m)'
set ylabel 'Posición Y (m)'
set xrange [0:10]
set yrange [0:8.66025]
set grid
do for [i=1:401:50] {
    plot 'triangulo_datos.dat' every ::1::i using 2:3 with linespoints title sprintf('Tiempo: %.2f s', i*0.1), \
         '-' with lines notitle 
0 0
10 0
5 8.66025
0 0
e
}
