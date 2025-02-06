//----------------------------------------
// Autor: Camilo Huertas
// Profesor: John Diaz
// Clase: Fisica computacional
// Universidad Distrital
// Proyecto: Parcial, Oscilador de Duffing
//----------------------------------------

// Este script soluciona numéricamente con RK4 el oscilador de Duffing (o variante)
// obteniendo datos de posición y tiempo. Luego, con derivación numérica (diferencias centradas)
// se calcula la velocidad y aceleración.
// Nota: Se integra el sistema completo (x y v) pero se guarda solo x y t para luego derivar.

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <string>

// Paso de integración (h) 
double h = 0.01;
int eleccion;  // 1: término cúbico, 2: término cuadrático

// Función que representa la ecuación para dv/dt = v'(x,v,t)
double vprima(double x, double v, double omg, double t, 
              double gamma, double delta, double alfa, double beta) {
    if (eleccion == 1){
        return gamma*cos(omg*t) - delta*v - alfa*x - beta*(x*x*x);
    }
    else if (eleccion == 2){
        return gamma*cos(omg*t) - delta*v - alfa*x - beta*(x*x);
    }
    // Valor por defecto si no se cumple ninguna condición
    return 0.0;
}

// Función RK4 para actualizar (x,v) en un paso
void RK4Step(double &x, double &v, double t, double gamma, double delta,
             double alfa, double beta, double omg) {

    // k1 para x y v
    double k1x = h * v;
    double k1v = h * vprima(x, v, omg, t, gamma, delta, alfa, beta);

    // k2
    double k2x = h * (v + 0.5*k1v);
    double k2v = h * vprima(x + 0.5*k1x, v + 0.5*k1v, omg, t + 0.5*h, gamma, delta, alfa, beta);

    // k3
    double k3x = h * (v + 0.5*k2v);
    double k3v = h * vprima(x + 0.5*k2x, v + 0.5*k2v, omg, t + 0.5*h, gamma, delta, alfa, beta);

    // k4
    double k4x = h * (v + k3v);
    double k4v = h * vprima(x + k3x, v + k3v, omg, t + h, gamma, delta, alfa, beta);

    // Actualización de x y v
    x += (1.0/6.0)*(k1x + 2*k2x + 2*k3x + k4x);
    v += (1.0/6.0)*(k1v + 2*k2v + 2*k3v + k4v);
}

//------------------------------------------------------------
// Variables y vectores para derivación numérica
std::vector<double> tiempos, posiciones, velocidades_3, aceleraciones_3;
double tiempo, posicion, velocidad, aceleracion;

// Prototipos de funciones para derivación y manejo de archivos
void LeerDatos();
void DerivacionCentrada();
void GuardarDatos();

int main() {
    double delta, alfa, beta, gamma, omg;
    double t0 = 0, tf;
    double v0, x0;

    // Configuración de parámetros
    std::cout << "Eliga el tipo de ecuacion a solucionar:\n 1. Termino cubico (Duffing)\n 2. Termino cuadratico" << std::endl;
    std::cin >> eleccion;
    if (eleccion != 1 && eleccion != 2) {
        std::cerr << "Opcion invalida. Saliendo del programa." << std::endl;
        return 1;
    }
    
    std::cout << "Ingrese parametros del oscilador:" << std::endl;
    std::cout << "Amortiguamiento (delta): ";
    std::cin >> delta;
    std::cout << "Rigidez lineal (alfa): ";
    std::cin >> alfa;
    std::cout << "No linealidad (beta): ";
    std::cin >> beta;
    std::cout << "Amplitud fuerza (gamma): ";
    std::cin >> gamma;
    std::cout << "Frecuencia fuerza (omg): ";
    std::cin >> omg;

    std::cout << "\nIngrese condiciones iniciales:" << std::endl;
    std::cout << "Tiempo final (tf): ";
    std::cin >> tf;
    std::cout << "Posicion inicial (x0): ";
    std::cin >> x0;
    std::cout << "Velocidad inicial (v0): ";
    std::cin >> v0;

    // Archivo de salida inicial (se guardarán t y x)
    std::ofstream datafile("duffing.txt");
    if (!datafile.is_open()){
        std::cerr << "No se pudo abrir el archivo para escritura." << std::endl;
        return 1;
    }

    // Se guarda el estado inicial
    datafile << t0 << " " << x0 << std::endl;

    // Integración con RK4 para el sistema (x, v)
    while(t0 <= tf) {
        RK4Step(x0, v0, t0, gamma, delta, alfa, beta, omg);
        t0 += h;
        datafile << t0 << " " << x0 << std::endl;
    }
    datafile.close();

    // Derivacion numérica con diferencias centradas
    LeerDatos();
    DerivacionCentrada();
    GuardarDatos();

    // Generación de gráficas mediante Gnuplot
    std::ofstream scriptFile("duffing.gp");
    if (!scriptFile.is_open()){
        std::cerr << "No se pudo abrir el archivo duffing.gp para escritura." << std::endl;
        return 1;
    }
    scriptFile << "set term png\n"
               << "set output 'XvsT.png'\n"
               << "set title 'X vs T'\n"
               << "set xlabel 't'\n"
               << "set ylabel 'x'\n"
               << "plot 'duffing.txt' using 1:2 with linespoints title 'x(t)'\n"
               << "set output 'fase.png'\n"
               << "set title 'Diagrama de fase'\n"
               << "set xlabel 'x'\n"
               << "set ylabel 'v'\n"
               << "plot 'duffing.txt' using 2:3 with linespoints title 'Fase'\n"
               << "set output 'AvsT.png'\n"
               << "set title 'A vs T'\n"
               << "set xlabel 't'\n"
               << "set ylabel 'a'\n"
               << "plot 'duffing.txt' using 1:4 with linespoints title 'a(t)'\n"
               << "set output 'VvsT.png'\n"
               << "set title 'V vs T'\n"
               << "set xlabel 't'\n"
               << "set ylabel 'v'\n"
               << "plot 'duffing.txt' using 1:3 with linespoints title 'v(t)'\n";
    scriptFile.close();

    system("gnuplot duffing.gp");
    std::cout << "\nGraficas generadas." << std::endl;

    return 0;
}


// Función para leer datos (tiempo y posición) del archivo generado por RK4
void LeerDatos(){
    std::ifstream archivo("duffing.txt");
    if (!archivo){
        std::cerr << "Error al abrir el archivo duffing.txt" << std::endl;
        exit(0);
    }
    // Se limpian los vectores en caso de múltiples llamadas
    tiempos.clear();
    posiciones.clear();
    while (archivo >> tiempo >> posicion){
        tiempos.push_back(tiempo);
        posiciones.push_back(posicion);
    }
    archivo.close();
}


// Derivación centrada para calcular velocidad y aceleración a partir de x(t)
void DerivacionCentrada(){
    velocidades_3.clear();
    aceleraciones_3.clear();
    
    // Se requieren al menos 3 puntos para derivar
    if(tiempos.size() < 3) {
        std::cerr << "No hay suficientes datos para derivar." << std::endl;
        exit(0);
    }
    
    // Calcular la velocidad con diferencias centradas
    // En los extremos se asigna 0 
    velocidades_3.push_back(0);
    for (size_t i = 1; i < tiempos.size()-1; i++){
        velocidad = (posiciones[i+1]-posiciones[i-1])/(tiempos[i+1]-tiempos[i-1]);
        velocidades_3.push_back(velocidad);
    }
    velocidades_3.push_back(0);
    
    // Calcular la aceleración derivando la velocidad obtenida
    aceleraciones_3.push_back(0);
    // Para el primer punto central, usamos el siguiente; también en el último se asigna 0
    aceleraciones_3.push_back(0);
    for (size_t i = 2; i < tiempos.size()-2; i++){
        aceleracion = (velocidades_3[i+1]-velocidades_3[i-1])/(tiempos[i+1]-tiempos[i-1]);
        aceleraciones_3.push_back(aceleracion);	
    }
    aceleraciones_3.push_back(0);
    aceleraciones_3.push_back(0);
}


// Guardar los datos finales (tiempo, posición, velocidad y aceleración) en duffing.txt
void GuardarDatos(){
    std::ofstream archivo("duffing.txt");
    if (archivo.is_open()){
        archivo.precision(5);
        for (size_t i=0; i < tiempos.size() ; i++){
            archivo << tiempos[i] << " " 
                    << posiciones[i] << " " 
                    << velocidades_3[i] << " " 
                    << aceleraciones_3[i] << std::endl;
        }
    }
}
