// Camilo Huertas, 2024

#include <iostream>

int main(void) {

	// se declara la variable respuesta para el ciclo do-while y no terminar el script; contador_padawans para ver el total de padawans registrado
	// y contador_ladooscuro para ir contando los padawans que son una amenaza.
	int respuesta = 0;
	int contador_padawans = 0;
	int contador_ladooscuro = 0;

	std::cout << "------------------------------------------------------------------" << std::endl;
	std::cout << "-       ¡Hola, este script te ayudará a salvar la galaxia!       -"    << std::endl;
	std::cout << "------------------------------------------------------------------" << std::endl;

	// el ciclo do-while se repetirá hasta que el usuario diga que no tiene más padawans
	do {
		int numero_midiclorias = 0;
		std::cout << "¿Cuántas midiclorias tiene el padawan?" << std::endl;
		//registramos el numero de midiclorias 
		std::cin >> numero_midiclorias;
		
		//este contador nos servirá para el siguente ciclo do-while
		int comprobador = 0;
		
		//se evalua si el numero es mayor a cero, si no, entra en el ciclo if hasta que el usuario digite un numero valido
		do {
			if (numero_midiclorias < 0){
				numero_midiclorias=0;
				std :: cout << "Por favor, pon un número valido, no uses negativos ni decimales\n";
				std :: cin >> numero_midiclorias;
			} else {
			comprobador = 1;}
		} while (comprobador == 0);

		// se declaran las variables para hacer el cambio de base. Basenueva: para indicar a que base se convertirá; result[32] es un arreglo de 32 espacios
		// donde se almacerá la conversión; el index es solo cuestión del ciclo.
		int basenueva = 5;
		int result[32];
		int index = 0;

		// se realiza el cambio de base.
		do {
			result[index] = numero_midiclorias % basenueva;
			numero_midiclorias = numero_midiclorias / basenueva;
			index++;
		} while (numero_midiclorias > 0);

		// se imprime el número convertido; notar que el ciclo for recorre el intervalo de forma invertida, esto por la propia naturaleza del proceso
		// de conversion entre bases
		std:: cout << std::endl;
		std::cout << "El número de midiclorias en base 5 es: ";
		for (int i = index - 1; i >= 0; i--) {
			std::cout << result[i];
		}
		std::cout << std::endl;

		// se declara la variable que indicará el numero de digitos 4 que hay en el numero convertido
		int count_4 = 0;
		
		//el ciclo for recorre todo el arreglo result[]
		for (int i = 0; i < index; i++){
			//cada vez que encuentra un numero 4, aumenta el contador
			if (result[i] == 4){
				count_4++;
			}
		}
		// si hay más de 1 digito 4, imprime "peligro" y aumenta el contador_ladooscuro
		if (count_4 > 1) {
			std :: cout << std :: endl;
			std :: cout << "¡Cuidado!, este padawan puede unirse al imperio galáctico y \nayudar en la venganza de los Sith." << std :: endl;
			contador_ladooscuro++;
		} else {
			std :: cout << std :: endl;
			std :: cout << "Puedes estar tranquilo, es un gran aprendiz." << std :: endl;
		}

		contador_padawans++;  // se ncrementa el contador de padawans

		// se pregunta si hay más padawans
		
		std :: cout << std:: endl;
		std::cout << "¿Tienes otro padawan?" << std::endl;
		std::cout << "1. Sí, 2. No" << std::endl;
		std::cin >> respuesta;

	} while (respuesta == 1);
	
	// se calcula el porcentaje de padawans que pueden caer al lado oscuro.

	// Antes de realizar la división al ser las 2 variables enteras, se realiza un cambio de tipo de variable a contador_ladooscuro de int a float, esto porque 
	// sino la división seria entre enteros, y al ser contador_ladooscuro < contador_padawans, siempre daria 0. al cambiar una de las variables a float c++ realiza
	// ya no una división entera sino que ya permite decimales, solucionando el problema.
	float porcentaje = 0;
	porcentaje = ((static_cast<float>(contador_ladooscuro) /contador_padawans)*100);

	//se imprime los resultados
	std::cout << std::endl;
	std::cout << "-------------------------------------------------------------" << std::endl;
	std::cout << "-     ¡Has registrado " << contador_padawans << " padawans!                           -" << std::endl;
	std::cout << "-     De los cuales " << contador_ladooscuro << "("<<porcentaje << ")%"<<" pueden ser una amenaza fantasma.  -" << std::endl;
	std::cout << "-     Que la Fuerza te acompañe!                            -" << std::endl;
	std::cout << "-------------------------------------------------------------" << std:: endl;
	
	//termina el script.
	//
	//Trabajo a mejorar: se podria evaluar si el numero digitado de midiclorias efectivamente es un numero 
	//entero positivo (por el momento solo evalua que es positivo, más no entero (aunque solo almacene la 
	//parte entera por ser un int la variable numero_midiclorias))
	
	//Posible BUG: he notado que al digital un numero entero de gran cantidad de cifras, salta el ciclo do-while 
	//y no permite registrar más padawans, es necesario una revisión.
	return 0;
}
