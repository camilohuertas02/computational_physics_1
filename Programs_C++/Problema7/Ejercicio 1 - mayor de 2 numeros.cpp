/*1. Escriba un programa que lea dos numeros y determine cual de ellos es 
el mayor.*/

#include<iostream>

using namespace std;

int main(void){
	int n1,n2;
	
	cout<<"Digite 2 numeros: "; 
	cin>>n1>>n2; //guardando los 2 numeros
	
	
	if(n1==n2){
		cout<<"Ambos numeros son iguales";
	}
	else if(n1>n2){
		cout<<"El mayor es: "<<n1;
	}
	else{
		cout<<"El mayor es: "<<n2;
	}
	
	return 0;
}
