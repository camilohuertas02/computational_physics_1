//------------------------------------------
// Archivo: GifChargeInB.cpp
// Autor: Camilo Huertas
// Clase: Física computacional 1
// Docente: Prof. John Diaz
//-------------------------------------------
// Este programa calcula la trayectoria de una partícula
// cargada en un campo magnético homogéneo B = Bzˆ.
// Se considera la fuerza magnética y se obtienen las 
// posiciones, velocidades y aceleraciones en términos del tiempo.
// ------------------------------------------

#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <string>

// Variables globales
double t_0, x_0, y_0, z_0, vx_0, vy_0, vz_0, B, deltat;
const double q = 1.602e-19;  // Carga del proton (Coulombs)
const double m = 1.67e-27;  // Masa del proton (kg)
std::string nombreArchivo = "datos_particula.dat";

// Se declaran las funciones
void SolicitarDatos();
void VerificarDatosEntrada(double B, double vx_0, double vy_0, double vz_0);
void generarDatos(double vx_0, double vy_0, double vz_0, double B, double q, double m, double t_0, double deltat, const std::string& nombreArchivo);
void graficarDatos(const std::string& nombreArchivo, const std::string& nombreImagen, const std::string& nombreTitulo, const std::string& nombreColumnaX, const std::string& nombreColumnaY, const std::string& usingConfig, const std::string& nombreTrayectoria);
int contarLineas(const std::string& nombreArchivo);
void generarAnimacion(const std::string& nombreArchivo, double deltat);

// Función principal
int main(void) {
	SolicitarDatos();
	VerificarDatosEntrada(B, vx_0, vy_0, vz_0);
	generarDatos(vx_0,vy_0,vz_0,B, q, m, t_0, deltat, nombreArchivo);

	// Graficar resultados
	graficarDatos(nombreArchivo, "chargeB_XVsT.jpg", "x(t) vs t", "t", "x(t)", "1:2", "x(t)");
	graficarDatos(nombreArchivo, "chargeB_YVsT.jpg", "y(t) vs t", "t", "y(t)", "1:3", "y(t)");
	graficarDatos(nombreArchivo, "chargeB_VxVsT.jpg", "vx(t) vs t", "t", "vx(t)", "1:5", "vx(t)");
	graficarDatos(nombreArchivo, "chargeB_VyVsT.jpg", "vy(t) vs t", "t", "vy(t)", "1:6", "vy(t)");
	graficarDatos(nombreArchivo, "chargeB_AxVsT.jpg", "ax(t) vs t", "t", "ax(t)", "1:8", "ax(t)");
	graficarDatos(nombreArchivo, "chargeB_AyVsT.jpg", "ay(t) vs t", "t", "ay(t)", "1:9", "ay(t)");
	graficarDatos(nombreArchivo, "chargeB_XVsY.jpg", "y(x) vs x", "x", "y(x)", "2:3", "Trayectoria");

	// Generar animación
	generarAnimacion(nombreArchivo, deltat);

	return 0;
}

// Función para solicitar los datos de entrada al usuario
void SolicitarDatos() {
	std::cout << "Ingrese el campo magnético B (en Tesla): " << std::endl;
	std::cin >> B;
	std::cout << "Ingrese velocidad inicial en x (vx_0) en m/s: " << std::endl;
	std::cin >> vx_0;
	std::cout << "Ingrese velocidad inicial en y (vy_0) en m/s: " << std::endl;
	std::cin >> vy_0;
	std::cout << "Ingrese velocidad inicial en z (vz_0) en m/s: " << std::endl;
	std::cin >> vz_0;
	std::cout << "Ingrese posición inicial en x (x_0) en metros: " << std::endl;
	std::cin >> x_0;
	std::cout << "Ingrese posición inicial en y (y_0) en metros: " << std::endl;
	std::cin >> y_0;
	std::cout << "Ingrese posición inicial en z (z_0) en metros: " << std::endl;
	std::cin >> z_0;
	std::cout << "Ingrese tiempo inicial (t_0) en segundos: " << std::endl;
	std::cin >> t_0;
	std::cout << "Ingrese delta t para los cálculos: " << std::endl;
	std::cin >> deltat;
}

// Verificación de los datos ingresados
void VerificarDatosEntrada(double B, double vx_0, double vy_0, double vz_0) {
	if (B <= 0.0) {
		std::cerr << "Valor no permitido de B <= 0.0" << std::endl;
		exit(EXIT_FAILURE);
	}
	if (vx_0 == 0.0 && vy_0 == 0.0) {
		std::cerr << "La partícula debe tener una velocidad inicial no nula en x o y" << std::endl;
		exit(EXIT_FAILURE);
	}
}

// Función para generar los datos del movimiento de la partícula
void generarDatos(double vx_0, double vy_0, double vz_0, double B, double q, double m, double t_0, double deltat, const std::string& nombreArchivo) {
	std::ofstream archivo(nombreArchivo);

	if (archivo.is_open()) {
		archivo.precision(5);  // Precisión en la escritura de los datos
		double t = t_0;
		double omega = q * B / m;  // Frecuencia ciclotrón

		// Generar datos mientras el tiempo t avanza
		while (t < t_0 + 10) {  // Simulación de 1 segundo

			// para la posición	
			double x = x_0 + (vx_0/omega)*std::sin(omega * t) - (vy_0/omega)*(1 - std::cos(omega * t));
			double y = y_0 + (vy_0/omega)*std::cos(omega * t) + (vx_0/omega)*(1 - std::cos(omega * t));
			double z = z_0 + vz_0*t;

			// velocidad

			double vx = (vx_0 * std::cos(omega*t)) + (vy_0 * std::sin(omega*t)); 
			double vy = (vy_0 * std::cos(omega*t)) - (vx_0 * std::sin(omega*t));
			double vz = vz_0;

			// aceleracion
			double ax = omega * vy;
			double ay = -omega * vx;
			double az = 0;



			// Escribir los datos en el archivo
			archivo << t << "\t" << x << "\t" << y << "\t" << z << "\t" << vx << "\t" << vy << "\t" << vz << "\t" <<  ax << "\t" << ay << "\t" << az << std::endl;

			// Incrementar tiempo
			t += deltat;
		}
		archivo.close();  // Cerrar archivo
	} else {
		std::cerr << "No se pudo abrir el archivo para escritura." << std::endl;
	}
}

// Función para graficar los datos con gnuplot
void graficarDatos(const std::string& nombreArchivo, const std::string& nombreImagen, const std::string& nombreTitulo, const std::string& nombreColumnaX, const std::string& nombreColumnaY, const std::string& usingConfig, const std::string& nombreTrayectoria) {
	std::string comando = "gnuplot -e \"set terminal jpeg; "
		"set output '" + nombreImagen + "'; "
		"set title '" + nombreTitulo + "'; "
		"set xlabel '" + nombreColumnaX + "'; "
		"set ylabel '" + nombreColumnaY + "'; "
		"set autoscale;"
		"plot '" + nombreArchivo + "' using " + usingConfig + " with lines title '" + nombreTrayectoria + "'\"";
	system(comando.c_str());  // Ejecutar comando gnuplot
}

// Función para contar el número de líneas en un archivo (número de puntos)
int contarLineas(const std::string& nombreArchivo) {
	std::ifstream archivo(nombreArchivo);
	int lineas = 0;
	std::string linea;

	// Contamos el número de líneas
	while (getline(archivo, linea)) {
		lineas++;
	}

	archivo.close();
	return lineas;
}


// Función para generar la animación de la trayectoria
void generarAnimacion(const std::string& nombreArchivo, double deltat) {

	int numPuntos = contarLineas(nombreArchivo);  // Número total de puntos de datos
	std::ofstream archivoAnimacion("Charge_In_B_3D.gnu");

	if (archivoAnimacion.is_open()) {
		archivoAnimacion << "# Configuración de terminal para generar un GIF animado\n";
		archivoAnimacion << "set terminal gif animate delay 10 size 800,600\n";
		archivoAnimacion << "set output 'carga_animacion.gif'\n";
		archivoAnimacion << "set title 'Movimiento de la carga'\n";
		archivoAnimacion << "set xlabel 'x(t)'\n";
		archivoAnimacion << "set ylabel 'y(t)'\n";
		archivoAnimacion << "set zlabel 'z(t)'\n";
		archivoAnimacion << "set xrange [-30000:30000] \n";
		archivoAnimacion << "set yrange [-30000:30000] \n";
		archivoAnimacion << "set zrange [-30000:30000] \n";
		archivoAnimacion << "set hidden3d \n";
		archivoAnimacion << "set palette \n";
		archivoAnimacion << "do for [i=1:" << numPuntos << "] {\n";
		archivoAnimacion << "    splot '" << nombreArchivo << "' every ::1::i using 2:3:4 with lines title sprintf('Tiempo: %.2f s', i*" << deltat << ")\n";
		archivoAnimacion << "}\n";
		archivoAnimacion << "unset output\n";

		archivoAnimacion.close();

		// Ejecutar el script de Gnuplot para generar la animación
		system("gnuplot Charge_In_B_3D.gnu");

		// Elimina el archivo de script después de generar el GIF
		remove("Charge_In_B_3D.gnu");
	} else {
		std::cerr << "No se pudo crear el archivo para la animación.\n";
	}
}
