// Camilo Huertas, 2024

#include <iostream>
#include <fstream>
#include <cmath>

int main() {
	double w, x_0, y_0, t_0, t_f, R, deltat;

	// se piden los parametros iniciales
	std::cout << "Ingresa w : " << std::endl;
	std::cin >> w;

	std::cout << "Ingresa x_0 : " << std::endl;
	std::cin >> x_0;

	std::cout << "Ingresa y_0 : " << std::endl;
	std::cin >> y_0;

	std::cout << "Ingresa t_0 : " << std::endl;
	std::cin >> t_0;

	std::cout << "Ingresa t_f : " << std::endl;
	std::cin >> t_f;

	std::cout << "Ingresa R : " << std::endl;
	std::cin >> R;

	std::cout << "Ingresa Delta t : " << std::endl;
	std::cin >> deltat;

	std::ofstream myfile("datos_circular_motion.dat");


	// Calcular trayectoria, velocidad y aceleración en cada instante de tiempo
	for (double t = t_0; t <= t_f; t += deltat) {
		double theta = w * t; // ángulo en radianes

		// Posición
		double x = x_0 + R * std::cos(theta);
		double y = y_0 + R * std::sin(theta);

		// Velocidad
		double v_x = -R * w * std::sin(theta);
		double v_y = R * w * std::cos(theta);

		// Aceleración
		double a_x = -R * w * w * std::cos(theta);
		double a_y = -R * w * w * std::sin(theta);

		myfile << t << " " << x << " " << y << " " << v_x << " " << v_y << " " << a_x << " " << a_y << std :: endl;
	}

	myfile.close();

	return 0;
}
