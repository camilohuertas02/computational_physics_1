//-------------------------------------
// Autor: Camilo Huertas
// Profesor: John Diaz
// Clase: Fisica computacional 1
// Universidad Distrital
// Proyecto: Fila india
//----------------------------------- 

// Este script verifica que una fila india del ejercito esté bajo los parámetros necesarios
// en donde los subordinados siempre han de estar adelante de sus comandantes.
// Si esto no es asi, el script reportará la pareja no alineada.

#include<iostream>
#include<cstdlib>

// Se declaran las variables
int n; // número de elementos en la fila
int m; // número de subordinaciones
int* fila; // Declarar el puntero a fila de forma global
int* comandantes; // Declarar el puntero a fila de forma global
int* subordinados; // Declarar el puntero a fila de forma global

// Se anuncian las funciones
void PedirDatos();
void CrearFila();
void CrearSubordinaciones();
void VerificarRegla();

int main(void) {
	std :: cout << "-------------------------------------------------------------------" << std :: endl;
	std :: cout << "!Señor General¡, este script mantendrá a sus tropas en orden" << std ::endl;
	std :: cout << "Este codigo le pedira el tamaño de la fila (m), numero de suordinaciones (m)" << std :: endl;
	std :: cout << "y comandate-subordinado; luego verificara que todo subordinado este delante de su comandante" << std :: endl;
	std :: cout << "-------------------------------------------------------------------" << std :: endl;
	std :: cout << " " << std::endl;
	std :: cout << "Ingreso de datos generales:" << std :: endl;	
	std :: cout << "-------------------------------------------------------------------" << std :: endl;
	PedirDatos();
	std :: cout << "-------------------------------------------------------------------" << std :: endl;
	std :: cout << " " << std::endl;
	std :: cout << "Creacion de la fila: " << std :: endl;
	std :: cout << "-------------------------------------------------------------------" << std :: endl;
	CrearFila();
	std :: cout << "-------------------------------------------------------------------" << std :: endl;
	std :: cout << " " << std::endl;
	std :: cout << "Creacion de subordinaciones: " 	<< std :: endl;
	std :: cout << "-------------------------------------------------------------------" << std :: endl;
	CrearSubordinaciones();
	std :: cout << "-------------------------------------------------------------------" << std :: endl;
	std :: cout << " " << std::endl;	
	std :: cout << "Datos ingresados: " << std :: endl;
	std :: cout << "-------------------------------------------------------------------" << std :: endl;
	for (int i = 0; i < n; i++) {
		std::cout << "Elemento " << i + 1 << ": " << fila[i] << std::endl;
	}

	for (int i = 0; i < m ; i++){
		std :: cout << "Comandante " << comandantes[i] << " del subordinado " << subordinados[i] << std::endl;
	}	
	std :: cout << "-------------------------------------------------------------------" << std :: endl;
	std :: cout << " " << std::endl;
	std :: cout << "Comprobación de la regla: " << std :: endl;	
	std :: cout << "-------------------------------------------------------------------" << std :: endl;
	VerificarRegla();
	std :: cout << "-------------------------------------------------------------------" << std :: endl;
	std :: cout << " " << std::endl;	

	delete[] fila; // Libera la memoria
	delete[] comandantes; // Libera la memoria
	delete[] subordinados; // Libera la memoria

	return 0;
}


// Se declaran las funciones
void PedirDatos(){
	std::cout << "Digite el número de elementos de la fila: " << std::endl;
	std::cin >> n;
	std::cout << "Digite el número de subordinaciones: " << std::endl;
	std::cin >> m;
}

void CrearFila() {
	fila = new int[n]; // Crear un array dinámico de tamaño n
	for (int i = 0; i < n; i++) {
		std::cout << "Ingrese el elemento " << i + 1 << " de la fila: " << std::endl;
		std::cin >> fila[i];
	}
}

void CrearSubordinaciones(){
	comandantes = new int[m];
	subordinados = new int[m];
	for (int i = 0; i < m ; i++){
		std :: cout << "Ingrese el comandante " << i + 1 << std :: endl;
		std :: cin >> comandantes[i];
		std :: cout << "Ingrese el subordinado " << i + 1 << std :: endl;
		std :: cin >> subordinados[i];
	}
}

void VerificarRegla(){

	//Primero se busca el indice de la posición del comandante
	int ComprobadorDePerfeccion = 0;
	for (int i = 0; i < m ; i++){
		int indice = -1;
		for (int  j = 0; j < n; j++){	
			int PosicionActual = fila[j];
			if (PosicionActual == comandantes[i]){
				indice = j;
				break;
			}
		}
		if (indice == -1){
			std :: cout << "El comandante no existe en la fila " << std :: endl ;
			exit(0);
		}
	// Ahora aqui se evaluará la regla desde la posición del comandante hacia adelante
		int comprobador = 0;
		for (int j = indice ; j < n; j++){
			if (fila[j] == subordinados[i]){
				comprobador = 1;
				break;
			}	
		}
		if (comprobador == 0){
			ComprobadorDePerfeccion = 1;
			std :: cout << "El subordinado " << subordinados[i] << " no esta adelante de su comandante " << comandantes[i] << std :: endl;  
		}
	}
	if (ComprobadorDePerfeccion == 0){
		std :: cout << "Todo está en orden" << std:: endl;
	}
}


// Notas:
// 1. Añadir que los elementos de la fila no se pueden repetir.
// 2. Ver si existe un numero maximo de subordinaciones con respecto al tamaño de la fila.
// 3. Verifica que todos los elementos de la fila sean numeros naturales.
// 4. Al ingresar comandante-subordinado, estos deben existir en la fila.




