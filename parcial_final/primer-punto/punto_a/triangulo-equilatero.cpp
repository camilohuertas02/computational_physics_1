// -----------------------------------------------------
// Nombre: Camilo Huertas
// Profesor: John Díaz
// Clase: Física Computacional 1
// Fecha: 14-02-2025
// Descripción: Simulación del movimiento de una partícula dentro de un triángulo equilátero.
// -----------------------------------------------------

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstdlib>

using namespace std;

// Constantes globales
const double EPSILON = 1.0e-5; // Tolerancia para tiempo final

// Variables globales
double L, x0, y_ini, vx0, vy0, t0, tf, dt;

// Declaración de funciones
void solicitarDatos();
void verificarValores();
void generarDatos(const string &nombreArchivo);
void graficarDatos(const string &nombreArchivo, const string &nombreImagen);
int contarLineas(const string &nombreArchivo);
void generarAnimacion(const string &nombreArchivo, double dt, const string &gifSalida);

// Función principal
int main() {
    // Solicitar datos al usuario
    solicitarDatos();
    // Verificar valores iniciales
    verificarValores();
    // Generar datos de la simulación
    string nombreArchivo = "triangulo_datos.dat";
    generarDatos(nombreArchivo);
    // Graficar los datos generados
    string nombreImagen = "triangulo_grafico.png";
    graficarDatos(nombreArchivo, nombreImagen);
    // Generar la animación
    string gifSalida = "triangulo_animacion.gif";
    generarAnimacion(nombreArchivo, dt, gifSalida);
    return 0;
}

// Implementación de funciones
void solicitarDatos() {
    cout << "Ingrese el lado del triángulo equilátero L:\n";
    cin >> L;
    cout << "Ingrese la posición inicial x0 y y_ini, y las velocidades iniciales vx0 y vy0:\n";
    cin >> x0 >> y_ini >> vx0 >> vy0;
    cout << "Ingrese el tiempo inicial t0, el tiempo final tf y el paso de tiempo dt:\n";
    cin >> t0 >> tf >> dt;
}

void verificarValores() {
    if (L <= 0.0) {
        cerr << "Error: El lado del triángulo L debe ser mayor que 0.\n";
        exit(1);
    }
    if (x0 < 0.0 || x0 > L || y_ini < 0.0 || y_ini > (sqrt(3)/2)*L) {
        cerr << "Error: La posición inicial (x0, y_ini) debe estar dentro del triángulo.\n";
        exit(1);
    }
    if (dt <= 0.0) {
        cerr << "Error: El paso de tiempo dt debe ser mayor que 0.\n";
        exit(1);
    }
}

void generarDatos(const string &nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        archivo.precision(5);
        archivo << fixed;
        double t = t0, x = x0, y = y_ini, vx = vx0, vy = vy0;
        int i = 0;
        while (t <= tf + EPSILON) {
            archivo << t << "\t" << x << "\t" << y << "\t" << vx << "\t" << vy << endl;
            // Actualización de la posición
            double x_prev = x, y_prev = y;
            x += vx * dt;
            y += vy * dt;
            t = t0 + (++i) * dt;

            // Verificación de colisiones con los bordes del triángulo
            // Colisión con el borde inferior (y = 0)
            if (y < 0.0) {
                vy = -vy;
                x = x_prev;
                y = y_prev;
            }
            // Colisión con el borde izquierdo (y = sqrt(3) * x)
            if (y > sqrt(3) * x) {
                double angle = M_PI / 3.0; // 60 grados
                double vx_temp = vx * cos(2 * angle) + vy * sin(2 * angle);
                double vy_temp = vx * sin(2 * angle) - vy * cos(2 * angle);
                vx = vx_temp;
                vy = vy_temp;
                x = x_prev;
                y = y_prev;
            }
            // Colisión con el borde derecho (y = sqrt(3) * (L - x))
            if (y > sqrt(3) * (L - x)) {
                double angle = M_PI / 3.0; // 60 grados
                double vx_temp = vx * cos(2 * angle) - vy * sin(2 * angle);
                double vy_temp = -vx * sin(2 * angle) - vy * cos(2 * angle);
                vx = vx_temp;
                vy = vy_temp;
                x = x_prev;
                y = y_prev;
            }
        }
        archivo.close();
        cout << "Datos generados en el archivo: " << nombreArchivo << endl;
    } else {
        cerr << "Error: No se pudo abrir el archivo para escritura.\n";
    }
}

void graficarDatos(const string &nombreArchivo, const string &nombreImagen) {
    ofstream script("graficar.gp");
    if (script.is_open()) {
        script << "set terminal pngcairo size 800,600\n";
        script << "set output '" << nombreImagen << "'\n";
        script << "set title 'Movimiento de una partícula en un triángulo equilátero'\n";
        script << "set xlabel 'Posición X (m)'\n";
        script << "set ylabel 'Posición Y (m)'\n";
        script << "set grid\n";
        script << "set xrange [0:" << L << "]\n";
        script << "set yrange [0:" << (sqrt(3)/2)*L << "]\n";
        script << "plot '" << nombreArchivo << "' using 2:3 with lines title 'Trayectoria', \\" << endl;
        script << "     '-' with lines title 'Triángulo' \n";
        script << "0 0\n";
        script << L << " 0\n";
        script << L/2 << " " << (sqrt(3)/2)*L << "\n";
        script << "0 0\n";
        script << "e\n";
        script.close();
        system("gnuplot graficar.gp");
        cout << "Gráfico generado: " << nombreImagen << endl;
    } else {
        cerr << "Error: No se pudo crear el archivo del script de Gnuplot.\n";
    }
}

int contarLineas(const string &nombreArchivo) {
    ifstream archivo(nombreArchivo);
    int lineas = 0;
    string linea;
    while (getline(archivo, linea)) {
        lineas++;
    }
    archivo.close();
    return lineas;
}

void generarAnimacion(const string &nombreArchivo, double dt, const string &gifSalida) {
    int numPuntos = contarLineas(nombreArchivo);
    ofstream archivoAnimacion("animate_triangulo.gnu");
    if (archivoAnimacion.is_open()) {
        archivoAnimacion << "set terminal gif animate delay 100 size 600,400\n"; // Aumentar el delay y reducir la resolución
        archivoAnimacion << "set output '" << gifSalida << "'\n";
        archivoAnimacion << "set title 'Evolución de la posición en el tiempo'\n";
        archivoAnimacion << "set xlabel 'Posición X (m)'\n";
        archivoAnimacion << "set ylabel 'Posición Y (m)'\n";
        archivoAnimacion << "set xrange [0:" << L << "]\n";
        archivoAnimacion << "set yrange [0:" << (sqrt(3)/2)*L << "]\n";
        archivoAnimacion << "set grid\n";
        archivoAnimacion << "do for [i=1:" << numPuntos << ":50] {\n"; // Reducir la cantidad de frames procesados
        archivoAnimacion << "    plot '" << nombreArchivo << "' every ::1::i using 2:3 with linespoints title sprintf('Tiempo: %.2f s', i*" << dt << "), \\" << endl;
        archivoAnimacion << "         '-' with lines notitle \n";
        archivoAnimacion << "0 0\n";
        archivoAnimacion << L << " 0\n";
        archivoAnimacion << L/2 << " " << (sqrt(3)/2)*L << "\n";
        archivoAnimacion << "0 0\n";
        archivoAnimacion << "e\n";
        archivoAnimacion << "}\n";
        archivoAnimacion.close();
        system("gnuplot animate_triangulo.gnu");
        cout << "Animación generada: " << gifSalida << endl;
    } else {
        cerr << "Error: No se pudo crear el archivo para la animación.\n";
    }
}

