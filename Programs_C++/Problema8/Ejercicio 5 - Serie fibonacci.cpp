//13. Hacer un que realize la serie fibonacci -> 1 1 2 3 5 8 13...n  

#include<iostream>

using namespace std;

int main(){
	int n,x=0,y=1,z=1;
	
	do{
		cout<<"Digite la cantidad de digitos de la serie: ";
		cin>>n;
	}while(n<=0);
	
	cout<<"1 ";
	for(int i=1;i<n;i++){
		z = x + y;
		cout<<z<<" ";
		x = y;
		y = z;		
	}

	/* La variable i en el bucle for se utiliza para controlar
	cuántas veces se ejecuta el bucle, asegurando que se generen
	y muestren los primeros n términos de la serie de Fibonacci.
	Aunque i no se usa directamente en las operaciones aritméticas,
	su papel es esencial para limitar el número de iteraciones,
	lo que garantiza que el programa funcione correctamente según 
	la cantidad de términos que el usuario desea generar.*/
	
	cout<<"\n";

	return 0;
}
