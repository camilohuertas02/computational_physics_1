# Configuración de terminal para generar un GIF animado
set terminal gif animate delay 10 size 800,600
set output 'box1D_animacion.gif'
set title 'Evolución de la posición en el tiempo'
set xlabel 'Tiempo (s)'
set ylabel 'Posición (m)'
set xrange [0:50]
set yrange [0:10]
set grid
do for [i=1:501] {
    plot 'box1D_datos.dat' every ::1::i using 1:2 with linespoints title sprintf('Tiempo: %.2f s', i*0.1)
}
unset output
