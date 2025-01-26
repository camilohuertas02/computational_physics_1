/*3. Realice un programa que calcule y muestre en la salida  la suma de 
los cuadrados de los 10 primeros enteros mayores que cero.*/

#include<iostream>

using namespace std;

int main(void){
	int suma=0,cuadrado;
	
	for(int i=1;i<=10;i++){
		cuadrado = i * i;
		suma += cuadrado;		
	}
	
	cout<<"\nLa suma de los cuadrados es: "
	<<suma;

	return 0;
}
