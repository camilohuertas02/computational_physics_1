// Camilo Huertas, 2024

#include <iostream>

int main (void){
	int numero_casilleros = 0;
	int cantidad_casilleros_abiertos = 0;
	std :: cout << "-----------------------------------------------" << std :: endl;
	std :: cout << "-  Hola, este es el juego de los casilleros   -" << std :: endl;
	std :: cout << "-----------------------------------------------" << std :: endl;
	std :: cout << std :: endl;
	std :: cout << "Digita el número de casilleros: " << std:: endl;
	std :: cin >> numero_casilleros;
	std :: cout << std ::endl;
	for (int i = 1; i <= numero_casilleros; i++){
		int contador=0;
		for (int j = 1; j <= i; j++){
			int division = i % j;	
			if (division == 0){
				contador++;	
			}
		}
		if (contador % 2 != 0){
			std :: cout << "El casillero número " << i<< " queda abierto" << std :: endl;
			cantidad_casilleros_abiertos++;

		} 
	}
	std :: cout << std:: endl;
	std :: cout << "De los " << numero_casilleros << " , " << cantidad_casilleros_abiertos << " quedan abiertos." << std :: endl; 
	return 0;
}


