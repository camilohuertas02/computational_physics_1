// -----------------------------------------------------
// Nombre: Camilo Huertas
// Profesor: John Díaz
// Clase: Física Computacional 1
// Fecha: 14-02-2025
// Descripción: Simulación del movimiento de una partícula en una caja unidimensional
//               con colisiones no elásticas. La partícula rebota en las paredes de la
//               caja con un coeficiente de restitución e, donde 0 < e <= 1.
// -----------------------------------------------------

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstdlib>

using namespace std;

// Constantes globales
const double EPSILON = 1.0e-5;  // Tolerancia para tiempo final

// Variables globales
double L, x0, v0, t0, tf, dt, e;

// Declaración de funciones
void solicitarDatos();
void verificarValores();
void generarDatos(const string& nombreArchivo);
void graficarDatos(const string& nombreArchivo, const string& nombreImagen);
int contarLineas(const string& nombreArchivo);
void generarAnimacion(const string& nombreArchivo, double dt, const string& gifSalida);

// Función principal
int main() {
    // Solicitar datos al usuario
    solicitarDatos();

    // Verificar valores iniciales
    verificarValores();

    // Generar datos de la simulación
    string nombreArchivo = "box1D_datos.dat";
    generarDatos(nombreArchivo);

    // Graficar los datos generados
    string nombreImagen = "box1D_grafico.png";
    graficarDatos(nombreArchivo, nombreImagen);

    // Generar la animación
    string gifSalida = "box1D_animacion.gif";
    generarAnimacion(nombreArchivo, dt, gifSalida);

    return 0;
}

// Implementación de funciones
void solicitarDatos() {
    cout << "Ingrese la longitud de la caja L:\n";
    cin >> L;
    cout << "Ingrese la posición inicial x0 y la velocidad inicial v0:\n";
    cin >> x0 >> v0;
    cout << "Ingrese el tiempo inicial t0, el tiempo final tf y el paso de tiempo dt:\n";
    cin >> t0 >> tf >> dt;
    cout << "Ingrese el coeficiente de restitución e (0 < e <= 1):\n";
    cin >> e;
}

void verificarValores() {
    if (L <= 0.0) {
        cerr << "Error: La longitud de la caja L debe ser mayor que 0.\n";
        exit(1);
    }
    if (x0 < 0.0 || x0 > L) {
        cerr << "Error: La posición inicial x0 debe estar dentro del rango [0, L].\n";
        exit(1);
    }
    if (v0 == 0.0) {
        cerr << "Error: La velocidad inicial v0 no puede ser cero.\n";
        exit(1);
    }
    if (dt <= 0.0) {
        cerr << "Error: El paso de tiempo dt debe ser mayor que 0.\n";
        exit(1);
    }
    if (e <= 0.0 || e > 1.0) {
        cerr << "Error: El coeficiente de restitución e debe estar en el rango (0, 1].\n";
        exit(1);
    }
}

void generarDatos(const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);

    if (archivo.is_open()) {
        archivo.precision(5);
        archivo << fixed;

        double t = t0, x = x0, v = v0;
        int i = 0;

        while (t <= tf + EPSILON) {
            archivo << t << "\t" << x << "\t" << v << endl;

            // Actualización de la posición y tiempo
            double x_prev = x;
            x += v * dt;
            t = t0 + (++i) * dt;

            // Verificación de rebotes
            if (x < 0.0) {
                v = -e * v;  // Invertir velocidad con coeficiente de restitución
                x = 0.0;     // Corregir posición
            } else if (x > L) {
                v = -e * v;  // Invertir velocidad con coeficiente de restitución
                x = L;       // Corregir posición
            }
        }

        archivo.close();
        cout << "Datos generados en el archivo: " << nombreArchivo << endl;
    } else {
        cerr << "Error: No se pudo abrir el archivo para escritura.\n";
    }
}

void graficarDatos(const string& nombreArchivo, const string& nombreImagen) {
    ofstream script("graficar.gp");

    if (script.is_open()) {
        script << "set terminal pngcairo size 800,600\n";
        script << "set output '" << nombreImagen << "'\n";
        script << "set title 'Movimiento de una partícula en una caja 1D'\n";
        script << "set xlabel 'Tiempo (s)'\n";
        script << "set ylabel 'Posición (m)'\n";
        script << "set grid\n";
        script << "plot '" << nombreArchivo << "' using 1:2 with lines title 'Posición vs Tiempo'\n";
        script.close();

        // Ejecutar el script de Gnuplot
        system("gnuplot graficar.gp");
        cout << "Gráfico generado: " << nombreImagen << endl;
    } else {
        cerr << "Error: No se pudo crear el archivo del script de Gnuplot.\n";
    }
}

int contarLineas(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    int lineas = 0;
    string linea;

    while (getline(archivo, linea)) {
        lineas++;
    }

    archivo.close();
    return lineas;
}

void generarAnimacion(const string& nombreArchivo, double dt, const string& gifSalida) {
    int numPuntos = contarLineas(nombreArchivo); // Número total de puntos
    ofstream archivoAnimacion("animate2D.gnu");

    if (archivoAnimacion.is_open()) {
        archivoAnimacion << "# Configuración de terminal para generar un GIF animado\n";
        archivoAnimacion << "set terminal gif animate delay 10 size 800,600\n";
        archivoAnimacion << "set output '" << gifSalida << "'\n";
        archivoAnimacion << "set title 'Evolución de la posición en el tiempo'\n";
        archivoAnimacion << "set xlabel 'Tiempo (s)'\n";
        archivoAnimacion << "set ylabel 'Posición (m)'\n";
        archivoAnimacion << "set xrange [" << t0 << ":" << tf << "]\n"; // Rango horizontal definido por el tiempo
        archivoAnimacion << "set yrange [0:" << L << "]\n";             // Rango vertical definido por la longitud de la caja
        archivoAnimacion << "set grid\n";
        archivoAnimacion << "do for [i=1:" << numPuntos << "] {\n";
        archivoAnimacion << "    plot '" << nombreArchivo << "' every ::1::i using 1:2 with linespoints title sprintf('Tiempo: %.2f s', i*" << dt << ")\n";
        archivoAnimacion << "}\n";
        archivoAnimacion << "unset output\n";

        archivoAnimacion.close();

        // Ejecutar el script de Gnuplot
        system("gnuplot animate2D.gnu");
        cout << "Animación generada: " << gifSalida << endl;
    } else {
        cerr << "Error: No se pudo crear el archivo para la animación.\n";
    }
}

