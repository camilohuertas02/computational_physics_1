#include <iostream>
#include <fstream>

int main() {
	double v0 = 5.0;
	double a = -9.81;
	double t;
	double y;

	std :: ofstream file ("datos_movimiento.txt");

	if (file.is_open()){
		for (t = 0; t <= 10; t += 0.5){
			y = v0 * t + 0.5 * a * t * t;
			file << t << " " << y << '\n';
		}
		file.close();
		std :: cout << "Datos guardados en datos_movimiento.txt\n";
	} else {	
		std :: cerr << "No se pudo abrir el archivo para escritura.\n";
	}
	
	return 0;
}

