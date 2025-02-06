#include <iostream>
#include <fstream>
#include <cmath>

double h = 205.2364/12255;

double vprima(double x, double v, double omg, double t, 
             double gamma, double delta, double alfa, double beta) {
    return gamma*cos(omg*t) - delta*v - alfa*x - beta*pow(x,2);
}

// Funciones para Runge-Kutta 4
double k1(double v) { return h*v; }
double l1(double x, double v, double omg, double t, 
         double gamma, double delta, double alfa, double beta) {
    return h*vprima(x, v, omg, t, gamma, delta, alfa, beta);
}

double k2(double x, double v, double omg, double t, 
         double gamma, double delta, double alfa, double beta) {
    return h*(v + 0.5*l1(x, v, omg, t, gamma, delta, alfa, beta));
}

double l2(double x, double v, double omg, double t, 
         double gamma, double delta, double alfa, double beta) {
    return h*vprima(x + 0.5*k1(v), 
                   v + 0.5*l1(x, v, omg, t, gamma, delta, alfa, beta), 
                   omg, t + 0.5*h, gamma, delta, alfa, beta);
}

double k3(double x, double v, double omg, double t, 
         double gamma, double delta, double alfa, double beta) {
    return h*(v + 0.5*l2(x, v, omg, t, gamma, delta, alfa, beta));
}

double l3(double x, double v, double omg, double t, 
         double gamma, double delta, double alfa, double beta) {
    return h*vprima(x + 0.5*k2(x, v, omg, t, gamma, delta, alfa, beta), 
                   v + 0.5*l2(x, v, omg, t, gamma, delta, alfa, beta), 
                   omg, t + 0.5*h, gamma, delta, alfa, beta);
}

double k4(double x, double v, double omg, double t, 
         double gamma, double delta, double alfa, double beta) {
    return h*(v + l3(x, v, omg, t, gamma, delta, alfa, beta));
}

double l4(double x, double v, double omg, double t, 
         double gamma, double delta, double alfa, double beta) {
    return h*vprima(x + k3(x, v, omg, t, gamma, delta, alfa, beta), 
                   v + l3(x, v, omg, t, gamma, delta, alfa, beta), 
                   omg, t + h, gamma, delta, alfa, beta);
}

double rungekuttax(double x, double v, double omg, double t, 
                  double gamma, double delta, double alfa, double beta) {
    return x + (1.0/6.0)*(k1(v) + 2*k2(x,v,omg,t,gamma,delta,alfa,beta) 
                        + 2*k3(x,v,omg,t,gamma,delta,alfa,beta) 
                        + k4(x,v,omg,t,gamma,delta,alfa,beta));
}

double rungekuttav(double x, double v, double omg, double t, 
                  double gamma, double delta, double alfa, double beta) {
    return v + (1.0/6.0)*(l1(x,v,omg,t,gamma,delta,alfa,beta) 
                        + 2*l2(x,v,omg,t,gamma,delta,alfa,beta) 
                        + 2*l3(x,v,omg,t,gamma,delta,alfa,beta) 
                        + l4(x,v,omg,t,gamma,delta,alfa,beta));
}

int main() {
    double delta, alfa, beta, gamma, omg;
    double t0 = 0, tf, v0, x0;

    // Configuración de parámetros
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

    // Archivo de salida
    std::ofstream datafile("duffing.txt");

    // Integración con Runge-Kutta
    while(t0 <= tf) {
        double new_v = rungekuttav(x0, v0, omg, t0, gamma, delta, alfa, beta);
        double new_x = rungekuttax(x0, v0, omg, t0, gamma, delta, alfa, beta);
        
	v0 = new_v;
        x0 = new_x;

        datafile << t0 << " " << x0 << " " << v0 << std::endl;
        
        t0 += h;
    }
    datafile.close();

    // Generación de gráficas
    std::ofstream scriptFile("duffing.gp");
    scriptFile << "set term png\n"
               << "set output 'duffing.png'\n"
               << "set title 'Solucion de la ecuacion de Duffing'\n"
               << "set xlabel 't'\n"
	       << "set ylabel 'x'\n"
               << "plot 'duffing.txt' using 1:2 with linespoints\n"
               << "set output 'fase.png'\n"
               << "set title 'Diagrama de fase'\n"
               << "set xlabel 'x'\n"
               << "set ylabel 'v'\n"
               << "plot 'duffing.txt' using 2:3 with linespoints\n";
    scriptFile.close();

    system("gnuplot duffing.gp");
    std::cout << "\nGraficas generadas: duffing.png y fase.png" << std::endl;

    return 0;
}
