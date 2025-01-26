//4. Escribe la siguiente expresion como expresion en C++: a + (b/(c-d))

#include<iostream>
#include <math.h>

using namespace std;

int main(void){
	float a,b,c,d,resultado = 0;
	
	cout<<"Digite el valor de a: "; cin>>a;
	cout<<"Digite el valor de b: "; cin>>b;
	cout<<"Digite el valor de c: "; cin>>c;
	cout<<"Digite el valor de d: "; cin>>d;
	
	resultado = a + (b/(c-d));
	
	cout.precision(5);
	
	cout<<"El resultado es: "<<resultado;
	
	return 0;
}
