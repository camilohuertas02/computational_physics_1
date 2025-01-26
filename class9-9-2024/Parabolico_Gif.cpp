#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cmath>

using namespace std;

// Declaración de las funciones (estereotipadas)
void solicitarDatos();
void verificarValores(double v0, double theta);
double convertirARadianes(double theta);
void calcularComponentesVelocidad(double v0, double theta, double& v0x, double& v0y);
void generarDatos(double v0x, double v0y, double g, double tf, double dt, const string& nombreArchivo);
void graficarDatos(const string& nombreArchivo, const string& nombreImagen, const string& nombreTitulo, const string& nombreColumnaX, const string& nombreColumnaY, const string& usingConfig, const string& nombreTrayectoria);
int contarLineas(const string& nombreArchivo);
void generarAnimacion(const string& nombreArchivo, double dt);  // Función para la animación

// Variables globales
double v0, theta, tf, dt, v0x, v0y;
string nombreArchivo = "datos_proyectil.txt";

// Función principal
int main(void) {
	solicitarDatos();
	verificarValores(v0, theta);  // Verifica que los datos de entrada sean válidos
	theta = convertirARadianes(theta);  // Convierte el ángulo a radianes
	calcularComponentesVelocidad(v0, theta, v0x, v0y);  // Calcula las componentes iniciales de la velocidad

	// Generar datos y guardarlos en un archivo
	generarDatos(v0x, v0y, 9.81, tf, dt, nombreArchivo);

	// Generar varias gráficas con diferentes configuraciones
	graficarDatos(nombreArchivo, "grafica1.jpg", "x(t) vs t", "t", "x(t)", "1:2","x(t)");  // Usar columnas 1 y 2 para la gráfica 1
	graficarDatos(nombreArchivo, "grafica2.jpg", "y(t) vs t", "t", "y(t)", "1:3", "y(t)");  // Usar columnas 1 y 3 para la gráfica 2
	graficarDatos(nombreArchivo, "grafica3.jpg", "y(x) vs x", "x", "y(x)", "2:3", "y(x)");  // Usar columnas 2 y 3 para la gráfica 3

	cout << "Gráficas generadas y guardadas en archivos .jpg" << endl;

	// Generar la animación en GIF
	generarAnimacion(nombreArchivo, dt);
	cout << "Animación generada en 'proyectil_animacion.gif'" << endl;

	return 0;
}

// Definición de las funciones

// Función para solicitar datos de entrada al usuario
void solicitarDatos() {
	cout << "# Ingrese v0 (velocidad inicial) y theta (ángulo en grados):\n"; cin >> v0 >> theta;
	cout << "# Ingrese tf (tiempo final) y dt (intervalo de tiempo):\n"; cin >> tf >> dt;
}

// Función para verificar los valores de entrada
void verificarValores(double v0, double theta) {
	if (v0 <= 0.0) {
		cerr << "Valor no permitido de v0 <= 0\n"; exit(1);  // Termina el programa si v0 es inválido
	}
	if (theta <= 0.0 || theta >= 90.0) {
		cerr << "Valor no permitido de theta (0 < theta < 90)\n"; exit(1);  // Termina el programa si theta no está en el rango válido
	}
}

// Función para convertir theta de grados a radianes
double convertirARadianes(double theta) {
	return (M_PI / 180.0) * theta;  // Convierte grados a radianes
}

// Función para calcular las componentes iniciales de la velocidad
void calcularComponentesVelocidad(double v0, double theta, double& v0x, double& v0y) {
	v0x = v0 * cos(theta);  // Componente horizontal
	v0y = v0 * sin(theta);  // Componente vertical
}

// Función para generar datos de posición y tiempo en el movimiento del proyectil
void generarDatos(double v0x, double v0y, double g, double tf, double dt, const string& nombreArchivo) {
	ofstream archivo(nombreArchivo);

	if (archivo.is_open()) {  // Verifica que el archivo se abra correctamente
		double t = 0.0;  // Tiempo inicial
		archivo.precision(5);  // Precisión en la escritura de los datos
		while (t <= tf) {
			// Cálculos de posición y velocidad en cada intervalo de tiempo
			double x = v0x * t;
			double y = v0y * t - 0.5 * g * t * t;
			double vx = v0x;
			double vy = v0y - g * t;

			archivo << t << "\t" << x << "\t" << y << "\t" << vx << "\t" << vy << endl;  // Escribe los datos en el archivo
			t += dt;  // Incrementa el tiempo en cada iteración
		}
		archivo.close();  // Cierra el archivo
	} else {
		cerr << "No se pudo abrir el archivo para escritura.\n";
	}
}

// Función para graficar los datos usando Gnuplot
void graficarDatos(const string& nombreArchivo, const string& nombreImagen, const string& nombreTitulo, const string& nombreColumnaX, const string& nombreColumnaY, const string& usingConfig, const string& nombreTrayectoria) {
	// Comando para ejecutar gnuplot y generar las gráficas con diferentes configuraciones
	string comando = "gnuplot -e \"set terminal jpeg; "
		"set output '" + nombreImagen + "'; "
		"set title '" + nombreTitulo + "'; "  
		"set xlabel '" + nombreColumnaX + "'; "
		"set ylabel '" + nombreColumnaY + "'; "
		"plot '" + nombreArchivo + "' using " + usingConfig + " with lines title '" + nombreTrayectoria + "'\"";

	// Ejecuta el comando en el sistema
	system(comando.c_str());
}

// Función para contar el número de líneas en un archivo (número de puntos)
int contarLineas(const string& nombreArchivo) {
	ifstream archivo(nombreArchivo);
	int lineas = 0;
	string linea;

	// Contamos el número de líneas
	while (getline(archivo, linea)) {
		lineas++;
	}

	archivo.close();
	return lineas;
}


// Función para generar una animación en GIF usando Gnuplot
void generarAnimacion(const string& nombreArchivo, double dt) {

	int numPuntos = contarLineas(nombreArchivo);  // Número total de puntos de datos
	ofstream archivoAnimacion("animate2D.gnu");

	if (archivoAnimacion.is_open()) {
		archivoAnimacion << "# Configuración de terminal para generar un GIF animado\n";
		archivoAnimacion << "set terminal gif animate delay 10 size 800,600\n";
		archivoAnimacion << "set output 'proyectil_animacion.gif'\n";
		archivoAnimacion << "set title 'Movimiento del proyectil'\n";
		archivoAnimacion << "set xlabel 'x(t)'\n";
		archivoAnimacion << "set ylabel 'y(t)'\n";
		archivoAnimacion << "set xrange [0:1150]\n";  // Ajusta según tus datos
		archivoAnimacion << "set yrange [0:275]\n";  // Ajusta según tus datos
		archivoAnimacion << "set grid\n"; 
		archivoAnimacion << "do for [i=1:" << numPuntos << "] {\n";
		archivoAnimacion << "    plot '" << nombreArchivo << "' every ::1::i using 2:3 with linespoints title sprintf('Tiempo: %.2f s', i*" << dt << ")\n";
		archivoAnimacion << "}\n";
		archivoAnimacion << "unset output\n";

		archivoAnimacion.close();

		// Ejecutar el script de Gnuplot para generar la animación
		system("gnuplot animate2D.gnu");

		// Elimina el archivo de script después de generar el GIF
		// remove("animate2D.gnu");
	} else {
		cerr << "No se pudo crear el archivo para la animación.\n";
	}
}

