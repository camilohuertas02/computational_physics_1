/*1. Escribe un programa que lea de la entrada de dos numeros y muestre 
en la salida  su suma, resta, multiplicacion y divisin.*/

#include<iostream>

using namespace std;

int main( void){
	float n1,n2; 
	float suma = 0; 
	float resta = 0; 
	float multiplicacion=0; 
	float division=0;
	cout<<"Digite un numero: ";
	cin>>n1;
	cout<<"Digite otro numero: "; 
	cin>>n2;
	
	suma = n1 + n2;
	resta = n1 - n2;
	multiplicacion = n1 * n2;
	division = n1 / n2;
	
	cout <<"\n La suma es: " <<suma <<endl;
	cout <<"La resta es: " <<resta <<endl;
	cout <<"La multiplicacion es: " <<multiplicacion <<endl;
	cout <<"La division es: " <<division <<endl;
		
	return 0;
}

