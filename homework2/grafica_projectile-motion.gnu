set title 'Projectile Motion'
set ylabel 'y = y_0 + v_0*sen(theta)*t + ((g*(t*t))/2) ; (MRUA)'
set xlabel 'x = x_0 + v_0*cos(theta)*t ; (MRU)'

set grid

plot 'datos_projectile-motion.dat' using 2:1 with linespoints


