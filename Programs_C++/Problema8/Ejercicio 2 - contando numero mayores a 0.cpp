/*2. Realice un programa que lea de la entrada  numeros hasta que se 
introduzca un cero. En ese momento el programa debe terminar y mostrar en la 
salida  el numero de valores mayores que cero leidos.*/

#include <iostream>

using namespace std;

int main(void){
	int numero,conteo=0; 
	
	do{
		cout<<"Digite un numero: "; 
		cin>>numero;
		if(numero>0){
			conteo++; //aumentamos el conteo cada vez que encuentra un numero mayor a 0	
		}
	}while(numero != 0);
		
	cout<<"\nEl total de numeros introducidos mayores a 0 es: "<<conteo;


	return 0;
}
