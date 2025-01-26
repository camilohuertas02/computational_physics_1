//------------------------------------------
// Archivo: GifProjectileAirResistance.cpp
// Autor: Camilo Huertas
// Clase: Física computacional 1
// Docente: Prof. John Diaz
//-------------------------------------------
// Este programa calcula un tipo parabolico en 
// la superficie de la tierra y se consideran 
// efectos de la resistencia del aire.
// ------------------------------------------

#include <iostream>
#include<cstdlib>
#include <cmath>
#include <fstream>
#include <ostream>
#include<string>


// variables globales
double theta, v_0, vx_0, vy_0 ,t_0, x_0, k, y_0, deltat;
double PI = 3.14159265359;
double g = 9.81;
std::string nombreArchivo = "datos_proyectil.dat";

// se declarar las funciones
void SolicitarDatos();
void VerificarDatosEntrada(double v_0, double theta);
double ConvertirGradosARadianes(double theta);
void CalcularComponentesVelocidad(double v_0, double theta, double& vx_0, double& vy_0);
void generarDatos(double vx_0, double vy_0, double g, double deltat, const std::string& nombreArchivo); 
void graficarDatos(const std::string& nombreArchivo, const std::string& nombreImagen, const std::string& nombreTitulo, const std::string& nombreColumnaX, const std::string& nombreColumnaY, const std::string& usingConfig, const std::string& nombreTrayectoria);
int contarLineas(const std::string& nombreArchivo);
void generarAnimacion(const std::string& nombreArchivo, double deltat);  // Función para la animación

// funcion principal
int main(void){
	SolicitarDatos();
	VerificarDatosEntrada(v_0, theta);
	theta = ConvertirGradosARadianes(theta);
	CalcularComponentesVelocidad(v_0, theta, vx_0, vy_0);
	generarDatos(vx_0,vy_0,g,deltat,nombreArchivo);
	graficarDatos(nombreArchivo, "XVsT.jpg", "x(t) vs t" , "t", "x(t)", "1:2", "x(t)");
	graficarDatos(nombreArchivo, "YVsT.jpg", "y(t) vs t" , "t", "y(t)", "1:3", "y(t)");
	graficarDatos(nombreArchivo, "VxVsT.jpg", "vx(t) vs t" , "t", "vx(t)", "1:4", "vx(t)");
	graficarDatos(nombreArchivo, "VyVsT.jpg", "vy(t) vs t" , "t", "vy(t)", "1:5", "vy(t)");
	graficarDatos(nombreArchivo, "AxVsT.jpg", "ax(t) vs t" , "t", "ax(t)", "1:7", "ax(t)");
	graficarDatos(nombreArchivo, "AyVsT.jpg", "at(t) vs t" , "t", "ay(t)", "1:2", "ay(t)");
	graficarDatos(nombreArchivo, "XVsY.jpg", "y(x) vs x" , "x", "y(x)", "2:3", "y(x)");

	std::cout << "Gráficas generadas y guardadas en archivos .jpg" << std::endl;

	// Generar la animación en GIF
	generarAnimacion(nombreArchivo, deltat);
	std::cout << "Animación generada en 'proyectil_animacion.gif'" << std::endl;
	return 0;
}

// se solicitan los datos y se guardan en variables
void SolicitarDatos(){
	std::cout << "Ingrese /theta" << std::endl ;
	std::cin >> theta;
	std::cout << "Ingrese velocidad inicial" << std::endl ;
	std::cin >> v_0;
	std::cout << "Ingrese tiempo inicial" << std::endl;
	std::cin >> t_0;
	std::cout << "Ingrese posicion inicial en x" << std::endl;
	std::cin >> x_0;
	std::cout << "Ingrese posicion inicial en y" << std::endl;
	std::cin >> y_0;
	std::cout << "Ingrese k" << std::endl;
	std::cin >> k;
	std::cout << "Ingrese delta t";
	std::cin >> deltat;
}

// se verifica que los datos sean validos
void VerificarDatosEntrada(double v_0, double theta){
	if (v_0 <= 0.0) {
		std::cerr << "Valor no permitido de v_0 <= 0.0" << std::endl;
	}
	if (theta <= 0.0 || theta >= 90.0) {
		std::cerr << "Valor no permitido de theta <=0.0 o >=90.0" << std::endl;
	}
}

double ConvertirGradosARadianes(double theta){
	return ((PI / 180) *theta);
}

void CalcularComponentesVelocidad(double v_0, double theta, double& vy_0, double& vx_0){
	vx_0 = v_0 * std::cos(theta); 
	vy_0 = v_0 * std::sin(theta); 
}

// Función para generar datos de posición y tiempo en el movimiento del proyectil
void generarDatos(double v0x, double v0y, double g, double dt, const std::string& nombreArchivo) {
	std::ofstream archivo(nombreArchivo);

	if (archivo.is_open()) {  // Verifica que el archivo se abra correctamente
		archivo.precision(5);  // Precisión en la escritura de los datos
		double t = t_0;	
		double tf = (2 / k) * std::log((g + k * vy_0)/ g);
		double ymax = (2/k)*((vy_0 + (g/k))/(k))*(std::log(g + k*vy_0/g))-((g/k*k)*tf) ;
		double xmax = (vx_0 / k) * (1 - std::exp(-k * tf));

		std::cout << "--------------------------------------" << std::endl;
		std::cout << "Tiempo de vuelo: "<< tf << std::endl;
		std::cout << "Altura maxima: "<< ymax << std::endl;
		std::cout << "alcance maximo: " << xmax	<< std::endl;
		std::cout << "--------------------------------------" << std::endl;
		while (t < tf) {
			double x = ((vx_0/k)*(1 - std::exp(-k*t) ));
			double y = ((vy_0 + (g/k))*((1 - std::exp(-k*t))/k))-((g/k)*t);
			double vx = (vx_0 * std::exp(-k*t)); 
			double vy = ((vy_0+(g/k))*(std::exp(-k*t)))-(g/k);
			double ax = (-k * vx);
			double ay = ((-k * vy) - g);
			archivo << t << "\t" << x << "\t" << y << "\t" << vx<< "\t" << vy<<  "\t" << ax << "\t" << ay << std::endl;  // Escribe los datos en el archivo
			t += deltat;  // Incrementa el tiempo en cada iteración
		}
		archivo.close();  // Cierra el archivo
	} else {
		std::cerr << "No se pudo abrir el archivo para escritura." << std::endl;
	}
}

void graficarDatos(const std::string& nombreArchivo, const std::string& nombreImagen, const std::string& nombreTitulo, const std::string& nombreColumnaX, const std::string& nombreColumnaY, const std::string& usingConfig, const std::string& nombreTrayectoria) {
	// Comando para ejecutar gnuplot y generar las gráficas con diferentes configuraciones
	std::string comando = "gnuplot -e \"set terminal jpeg; "
		"set output '" + nombreImagen + "'; "
		"set title '" + nombreTitulo + "'; "  
		"set xlabel '" + nombreColumnaX + "'; "
		"set ylabel '" + nombreColumnaY + "'; "
		"plot '" + nombreArchivo + "' using " + usingConfig + " with lines title '" + nombreTrayectoria + "'\"";

	// Ejecuta el comando en el sistema
	system(comando.c_str());
}


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


// Función para generar una animación en GIF usando Gnuplot
void generarAnimacion(const std::string& nombreArchivo, double dt) {

	int numPuntos = contarLineas(nombreArchivo);  // Número total de puntos de datos
	std::ofstream archivoAnimacion("animate2D.gnu");

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
		remove("animate2D.gnu");
	} else {
		std::cerr << "No se pudo crear el archivo para la animación.\n";
	}
}




