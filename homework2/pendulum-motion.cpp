// Camilo Huertas, 2024

#include <iostream>
#include <fstream>
#include <cmath>

int main() {
    double theta_0, w_0, t_0, t_f, l, deltat;
    double g = 9.81;

    // Se piden los parámetros iniciales
    std::cout << "Ingresa theta_0: " << std::endl;
    std::cin >> theta_0;

    std::cout << "Ingresa w_0 : " << std::endl;
    std::cin >> w_0;

    std::cout << "Ingresa t_0 : " << std::endl;
    std::cin >> t_0;

    std::cout << "Ingresa t_f : " << std::endl;
    std::cin >> t_f;

    std::cout << "Ingresa l : " << std::endl;
    std::cin >> l;

    std::cout << "Ingresa Delta t : " << std::endl;
    std::cin >> deltat;

    std::ofstream myfile("datos_pendulum_motion.dat");


    // se calcula en el ciclo for la trayectoria, velocidad, y aceleracion
    for (double t = t_0; t <= t_f; t += deltat) {
        
	double theta = theta_0 * std ::cos (w_0 * t) ;
	double omega = - theta_0  * w_0 * std :: sin(w_0 * t) ;

        // trayectoria
        double x = l * std :: sin(theta);
        double y = -l * std :: cos(theta);

        // Velocidad 
        double v_x = l * omega  * std ::cos(theta) ;
        double v_y = l * omega * std ::sin (theta);

        // Aceleración 
        double a_x = - l * (w_0*w_0) * std ::sin(theta) ;
        double a_y = l * (w_0*w_0) * std ::cos(theta) ;

        // Se carga los datos calculados en el .dat
        myfile << t << " " << x << " " << y << " " << v_x << " " << v_y << " " << a_x << " " << a_y << std :: endl;
    }

    myfile.close();

    return 0;
}
