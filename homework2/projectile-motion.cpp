#include <iostream>
#include <fstream>
#include <cmath>

int main (void){
	// se declaran las variables
	double x, y, theta=0, v_0=0, t_0=0, t_f=0, x_0=0, y_0=0;
	double g = 9.8;
	double deltat = 0;
	std :: cout << "Ingresa theta: " << std :: endl;
	std :: cin >> theta;

	std :: cout << "Ingresa v_0: "<< std :: endl;
	std :: cin >> v_0;

	std :: cout << "Ingresa t_0: "<< std :: endl;
	std :: cin >> t_0;

	std :: cout << "Ingresa t_f: "<< std :: endl;
	std :: cin >> t_f;

	std :: cout << "Ingresa x_0: "<< std :: endl;
	std :: cin >> x_0;

	std :: cout << "Ingresa y_0: "<< std :: endl;
	std :: cin >> y_0;

	std :: cout << "Ingresa Delta t: "<< std :: endl;
	std :: cin >> deltat;

	// registramos los datos de y (caida libre)
	
	std :: ofstream myfile("datos_projectile-motion.dat");
	for (double i = t_0; i <= t_f; i += deltat ){	
		y = y_0 + ((v_0 * std :: sin(theta))*i) - (g*(i*i)/2);
		x= x_0 + ((v_0 * std :: cos(theta)) * i) ;
		myfile << y << " " << x << " " << i <<std :: endl;
	}
	myfile.close();

	return 0;
}

