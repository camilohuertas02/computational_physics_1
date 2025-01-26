# Configuración de terminal para generar un GIF animado
set terminal gif animate delay 10 size 800,600
set output 'proyectil_animacion.gif'
set title 'Movimiento del proyectil'
set xlabel 'x(t)'
set ylabel 'y(t)'
set xrange [0:1150]
set yrange [0:275]
set grid
do for [i=1:200] {
    plot 'datos_proyectil.txt' every ::1::i using 2:3 with linespoints title sprintf('Tiempo: %.2f s', i*0.1)
}
unset output
