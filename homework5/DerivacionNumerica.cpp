//----------------------------------------
// Autor: Camilo Huertas
// Profesor: John Diaz
// Clase: Fisica computacional
// Universidad Distrital
// Proyecto: Derivacion numerica por 3 metodos
// ---------------------------------------

// Este script recibe datos de un .dat de tiempo, posicion, y calcula velocidad y aceleracion 
// haciendo uso de 3 metodos de derivacion numerica (forward, backward, y diferencias centradas)

// Librerias a usar:
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<ostream>
#include<string>

// Pasos:
// 1. Leer el .dat (Hecho)
// 2. Realizar la operación por los 3 casos y cargarlos a un archivo
// 3. Leerlos y hacer 2 graficas v y a para cada metodo.

// Variables
std::vector<double> tiempos, posiciones, velocidades_1, aceleraciones_1, velocidades_2, aceleraciones_2, velocidades_3, aceleraciones_3;
double tiempo, posicion, velocidad, aceleracion;

// Funciones
void LeerDatos();
void DerivacionForward();
void DerivacionBackward();
void DerivacionCentrada();
void GuardarDatos();
void GraficarDatos(const std::string& nombreImagen, const std::string& nombreTitulo, const std::string& nombreColunmaX, const std::string& nombreColumnaY, const std::string& usingConfig, const std::string& nombreTrayectoria);


int main(void){
	LeerDatos();
	DerivacionForward();
	DerivacionBackward();
	DerivacionCentrada();
	GuardarDatos();
	GraficarDatos("VvsT_Forward.jpg" , "Metodo Forward / V vs T" , "Tiempo (s)" , "Velocidad (m/s)" , "1:3" , "V");
	GraficarDatos("AvsT_Forward.jpg" , "Metodo Forward / A vs T" , "Tiempo (s)" , "Aceleracion (m/s**2)" , "1:6" , "A");
	GraficarDatos("VvsT_Backward.jpg" , "Metodo Backward / V vs T" , "Tiempo (s)" , "Velocidad (m/s)" , "1:4" , "V");
	GraficarDatos("AvsT_Backward.jpg" , "Metodo Backward / A vs T" , "Tiempo (s)" , "Aceleracion (m/s**2)" , "1:7" , "A");
	GraficarDatos("VvsT_Centradas.jpg" , "Diferencias centradas / V vs T" , "Tiempo (s)" , "Velocidad (m/s)" , "1:5" , "V");
	GraficarDatos("AvsT_Centradas.jpg" , "Diferencias centradas / A vs T" , "Tiempo (s)" , "Aceleracion (m/s**2)" , "1:8" , "A");
	
	std :: cout << "Graficas generadas y guardadas en archivos .jpg" << std ::endl;

	return 0;
}

void LeerDatos(){
	std :: ifstream archivo("DatosCaida.dat");
	if (!archivo){
		std :: cerr << "Error al abrir el archivo" << std :: endl;
		exit(0);
	}
		while (archivo >> tiempo >> posicion){
		tiempos.push_back(tiempo);
		posiciones.push_back(posicion);
	}
	archivo.close();
}

void DerivacionForward(){
	velocidades_1.clear();
	aceleraciones_1.clear();
	for (int i = 0 ; i < (tiempos.size() - 1);i++){
		velocidad = 0;
		velocidad = ((posiciones[i+1]-posiciones[i])/(tiempos[i+1]-tiempos[i]));
		velocidades_1.push_back(velocidad);
	}
	velocidades_1.push_back(0);
	for (int i = 0 ;  i < (tiempos.size() - 2); i++){
		aceleracion = 0;
		aceleracion = ((velocidades_1[i+1]-velocidades_1[i])/(tiempos[i+1]-tiempos[i]));
		aceleraciones_1.push_back(aceleracion);	
	}
	aceleraciones_1.push_back(0);
	aceleraciones_1.push_back(0);
}

void DerivacionBackward(){
	velocidades_2.clear();
	aceleraciones_2.clear();
	velocidades_2.push_back(0);
	for (int i = 1 ; i < tiempos.size();i++){
		velocidad = 0;
		velocidad = ((posiciones[i]-posiciones[i-1])/(tiempos[i]-tiempos[i-1]));
		velocidades_2.push_back(velocidad);
	}
	aceleraciones_2.push_back(0);
	aceleraciones_2.push_back(0);
	for (int i = 2 ;  i < tiempos.size(); i++){
		aceleracion = 0;
		aceleracion = ((velocidades_2[i]-velocidades_2[i-1])/(tiempos[i]-tiempos[i-1]));
		aceleraciones_2.push_back(aceleracion);	
	}
}


void DerivacionCentrada(){
	velocidades_3.clear();
	aceleraciones_3.clear();
	velocidades_3.push_back(0);
	for (int i = 1 ; i < (tiempos.size() - 1);i++){
		velocidad = 0;
		velocidad = ((posiciones[i+1]-posiciones[i-1])/(tiempos[i+1]-tiempos[i-1]));
		velocidades_3.push_back(velocidad);
	}
	velocidades_3.push_back(0);
	aceleraciones_3.push_back(0);
	aceleraciones_3.push_back(0);
	for (int i = 2 ;  i < (tiempos.size() - 2); i++){
		aceleracion = 0;
		aceleracion = ((velocidades_3[i+1]-velocidades_3[i-1])/(tiempos[i+1]-tiempos[i-1]));
		aceleraciones_3.push_back(aceleracion);	
	}
	aceleraciones_3.push_back(0);
	aceleraciones_3.push_back(0);
}

void GuardarDatos(){
	std::ofstream archivo("datos_calculados.dat");
	if (archivo.is_open()){
		archivo.precision(5);
		for (int i=0; i < tiempos.size() ; i++){
			archivo << tiempos[i] << " " << posiciones[i] << " " << velocidades_1[i] << " " << velocidades_2[i] << " " << velocidades_3[i] << " " << aceleraciones_1[i] << " " << aceleraciones_2[i] << " " << aceleraciones_3[i] << std :: endl ;	
		}
	}
}
void GraficarDatos(const std::string& nombreImagen, const std::string& nombreTitulo, const std::string& nombreColunmaX, const std::string& nombreColumnaY, const std::string& usingConfig, const std::string& nombreTrayectoria){
	std :: string comando = "gnuplot -e \"set terminal jpeg; "
		"set output '" + nombreImagen + "'; "
		"set title '" + nombreTitulo + "'; "
		"set xlabel '" + nombreColunmaX + "'; "
		"set ylabel '" + nombreColumnaY + "'; "
		"set grid; "
		"plot 'datos_calculados.dat' using " + usingConfig + " with linespoints title '" + nombreTrayectoria + "'\"";	
	system(comando.c_str());
}

