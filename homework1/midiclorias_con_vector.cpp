#include <iostream>
#include <vector>

int main(void){

	// declaramos las variables
	int number_padawans=0;
	int basenueva = 5;

	// se guarda el numero de padawans que tiene el maestro Jedi
	std :: cout << "---------------------------------------------------\n";
	std :: cout << "Este script te ayudará a salvar la galaxia\n";
	std :: cout << "---------------------------------------------------\n";
	std :: cout << "Ingresa el número de padawans que tienes: ";
	std :: cout << " \n";
	std :: cin >> number_padawans;

	// se usará un vector ya que es dinamico
	std :: vector<int> number_midiclorias(number_padawans);  

	// number_midiclorias será un vector donde se guarde el numero de midiclorias
	for (int i = 0; i < number_padawans; i++){
		std :: cout << "Ingresa el numero de midiclorias para el padawans " << i+1 << ": "<< std :: endl;
		std :: cin >> number_midiclorias[i];
		int contador = number_padawans - i -1 ;
		std :: cout << " " << std :: endl;
		std :: cout << "Te faltan " << contador << " padawans por registrar.\n" << std:: endl; 		
	}
	// En este ciclo for se convertirá a base 5 y se imprimirá el resultado
	for (int i = 0; i <number_padawans; i++){
		std :: vector<int> number_midiclorias_new;
		int numero_actual = number_midiclorias[i];

		// convertimos a base 5

		while (numero_actual > 0) {
			number_midiclorias_new.push_back(numero_actual % basenueva);
			numero_actual /= basenueva; 
		}

		// imprimimos el resultado

		std :: cout << "El numero en base 5 del padawan " << i+1 << " es: " << std ::endl;

		for (int j = number_midiclorias_new.size() - 1; j >= 0; j--){
			std :: cout << number_midiclorias[j];
		}
		std :: cout << std :: endl;


	}

	return 0;	
}



