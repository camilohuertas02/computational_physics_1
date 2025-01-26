// ------------------------
// Autor: Camilo Huertas
// Profesor: John Diaz
// Clase: Fisica Computacional 1
// Universidad Distrital
// Proyecto: Parcial 1 - Oscilador de Fermi
// ------------------------

// Este script calcula el movimiento del oscilador de Fermi, realiza una grafica Y vs T del bloque 
// y realiza una animación (gif).

// Librerias a usar#include<iostream>
#include<fstream>
#include<iostream>
#include<cmath>
#include<vector>
#include<iomanip>
#include <ostream>

const double gravedad = 9.81;
double m, M, k, h, t_colision;
int N_oscilaciones;
std::vector<double> tiempos, posiciones_bloque, posiciones_plataforma;
double v_inicial_plataforma, v_inicial_bloque, v_final_bloque, v_final_plataforma;

void PedirDatos();
void AntesColision();
void primeravelocidad();
void rec_velocidad(double w);
float Despues_colision(double w);
void GuardarDatos();
double f(double t, double w);

// para crear el .gif
//int contarLineas(const std::string& nombreArchivo);
//void generarAnimacion(const std::string& nombreArchivo, double deltat);  // Función para la animación



double velocidad_inicial_plataforma = 0.0;
double posicion_bloque_antes_colision = 0.0;
double posicion_plataforma_antes_colision = 0.0;
double tiempo_anterior_colision = 0.0;

int main(void){
	PedirDatos();
	AntesColision();
	primeravelocidad();
	const double w = std::sqrt(k/m);
	for (int i = 0; i < N_oscilaciones ; i++){
		Despues_colision(w);
		rec_velocidad(w);
	}
	GuardarDatos();
	return 0;
}

void PedirDatos(){
	std::cout << "Ingrese la masa del bloque" << std::endl;
	std::cin >> m;
	std::cout << "Ingrese la masa de la plataforma" << std::endl;
	std::cin >> M;
	std::cout << "Ingrese la constante elastica (k)" << std::endl;
	std::cin >> k;
	std::cout << "Ingrese la altura de la que se lanza el bloque" << std::endl;
	std::cin >> h;
	std::cout << "Ingrese el numero de oscilaciones" << std::endl;
	std::cin >> N_oscilaciones;
}

void AntesColision(){
	double pb, pp;
	tiempos.clear();
	posiciones_bloque.clear();
	posiciones_plataforma.clear();

	// tiempo de colisión usando caída libre
	t_colision = std::sqrt(2 * (h + (M * gravedad * (1/k))) / gravedad);
	std :: cout << "tiempo primera colisión: " << t_colision << std:: endl ;
	// trayectoria del bloque
	for (double t = 0; t <= t_colision; t += 0.01){
		pb = h - 0.5 * gravedad * t * t;
		tiempos.push_back(t);
		posiciones_bloque.push_back(pb);

		pp = - M * gravedad * (1/k);  // plataforma en reposo
		posiciones_plataforma.push_back(pp);
	}
}

void primeravelocidad(){
	// calculados la velocidad antes del choque:
	v_inicial_bloque = -1 * gravedad * t_colision;	
	v_inicial_plataforma = velocidad_inicial_plataforma;	
	// velocidad final bloque
	v_final_bloque = (((2 * M * v_inicial_plataforma) + v_inicial_bloque*(m - M))/(M + m));	
	// velocidad final plataforma
	v_final_plataforma = (((2 * m * v_inicial_bloque) + v_inicial_plataforma*(M-m))/((M + m)));	
}

// la funcion ha de ser aquella trasladada hacia la derecha despues de la colision anterior
double f(double t, double w){
	return posiciones_bloque.back() + v_final_bloque * (t - tiempos.back()) - (0.5 * gravedad * (t - tiempos.back() ) * (t - tiempos.back())) + gravedad / (w * w) - (v_final_plataforma / w) * std::sin(w * (t - tiempos.back())) - (posiciones_plataforma.back() + gravedad / (w * w)) * std::cos(w * (t - tiempos.back()));
}

double bisection(double a, double b, double tol, int max_iter, double w) {
	double mid;
	for (int i = 0; i < max_iter; ++i) {
		mid = (a + b) / 2.0;
		if (std::abs(f(mid,w)) < tol) {
			return mid; // Solución encontrada
		}
		if (f(a, w) * f(mid, w) < 0) {
			b = mid; // La raíz está en [a, mid]
		} else {
			a = mid; // La raíz está en [mid, b]
		}
	}
	return mid; // Retorna la mejor aproximación encontrada
}


float Despues_colision(double w){
	
	double a = tiempos.back(), b = (tiempos.back()+100); 
	double tol = 1e-8;         // Tolerancia
	int max_iter = 10000;       // Máximo número de iteraciones

	// Validar cambio de signo
	if (	f(a, w) * f(b, w) > 0 ) {
		std::cerr << "El intervalo no contiene una raíz (f(a) * f(b) > 0).\n";
		return -1;
	}

	// Encontrar raíz
	double root = bisection(a, b, tol, max_iter, w);
	std::cout << "La colisión ocurre en t = " << root << " s\n";
	double pp = 0.0;
	double pb = 0.0;

	posicion_bloque_antes_colision = posiciones_bloque.back();
	posicion_plataforma_antes_colision = posiciones_plataforma.back();
	tiempo_anterior_colision = tiempos.back();
	

	// aqui se toma el ultimo valor de la posicion registrado, el cual es la posicion inicial para el siguiente movimiento
	// trayectoria del bloque
	for (double t = tiempos.back(); t <= root; t += 0.01){
		tiempos.push_back(t);
		// La funcion ha de ser trasladada hacia la derecha en un factor de tiempo_anterior_colision
		pb = posicion_bloque_antes_colision + v_final_bloque * (t - tiempo_anterior_colision) - (0.5 * gravedad * (t - tiempo_anterior_colision) * (t - tiempo_anterior_colision));
		posiciones_bloque.push_back(pb);

		pp = (-1 * (gravedad / (w * w))) + ((v_final_plataforma / w) * std :: sin(w * (t - tiempo_anterior_colision))) + (posicion_plataforma_antes_colision + (gravedad / (w * w))) * std :: cos(w * (t - tiempo_anterior_colision)) ; 
		posiciones_plataforma.push_back(pp);
	}
	return 0;
}


void rec_velocidad(double w){
	// calculados la velocidad antes del choque:
	float vel_bloque_de_choque = v_final_bloque -1 * gravedad * tiempos.back();	
	float vel_plataforma_de_choque = v_final_plataforma * std :: cos( w * tiempos.back()) - (posicion_plataforma_antes_colision * w + (gravedad  / w)) * std :: sin(w * tiempos.back());	
	// velocidad final bloque
	v_final_bloque = (((2 * M * vel_plataforma_de_choque) + (vel_bloque_de_choque * (m - M)))/(M + m));
	// velocidad final plataforma
	v_final_plataforma = (((2 * m * vel_bloque_de_choque) + vel_plataforma_de_choque*(M-m))/((M + m)));	
}


void GuardarDatos(){
	std::ofstream archivo("datos_calculados.dat");
	if (archivo.is_open()){
		archivo.precision(5);
		for (int i = 0; i < tiempos.size(); i++){
			archivo << tiempos[i] << " " << posiciones_bloque[i] << " " << posiciones_plataforma[i] << std::endl;
		}
	}
}


//int contarLineas() {
//	std::ifstream archivo('datos_calculados.dat');
//	int lineas = 0;
//	std::string linea;
//
//	// Contamos el número de líneas
//	while (getline(archivo, linea)) {
//		lineas++;
//	}
//
//	archivo.close();
//	return lineas;
//}


// Función para generar una animación en GIF usando Gnuplot
//void generarAnimacion(double dt) {
//
//	int numPuntos = contarLineas();  // Número total de puntos de datos
//	std::ofstream archivoAnimacion("animate2D.gnu");
//
//	if (archivoAnimacion.is_open()) {
//		archivoAnimacion << "# Configuración de terminal para generar un GIF animado\n";
//		archivoAnimacion << "set terminal gif animate delay 10 size 800,600\n";
//		archivoAnimacion << "set output 'proyectil_animacion.gif'\n";
//		archivoAnimacion << "set title 'Movimiento del proyectil'\n";
//		archivoAnimacion << "set xlabel 'x(t)'\n";
//		archivoAnimacion << "set ylabel 'y(t)'\n";
//		archivoAnimacion << "set xrange [0:1150]\n";  // Ajusta según tus datos
//		archivoAnimacion << "set yrange [0:275]\n";  // Ajusta según tus datos
//		archivoAnimacion << "set grid\n"; 
//		archivoAnimacion << "do for [i=1:" << numPuntos << "] {\n";
//		archivoAnimacion << "    plot '" << 'datos_calculados.dat' << "' every ::1::i using 2:3 with linespoints title sprintf('Tiempo: %.2f s', i*" << dt << ")\n";
//		archivoAnimacion << "}\n";
//		archivoAnimacion << "unset output\n";
//
//		archivoAnimacion.close();
//
//		// Ejecutar el script de Gnuplot para generar la animación
//		system("gnuplot animate2D.gnu");
//
//		// Elimina el archivo de script después de generar el GIF
//		remove("animate2D.gnu");
//	} else {
//		std::cerr << "No se pudo crear el archivo para la animación.\n";
//	}
//}

