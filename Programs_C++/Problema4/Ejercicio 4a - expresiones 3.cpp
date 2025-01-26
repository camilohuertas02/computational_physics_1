// 3. Escribe la siguiente expresin como expresin en C++: (a+(b/c))/(d+(e/f))

#include<iostream>
#include <math.h>

using namespace std;

int main(void){
	float a,b,c,d,e,f,resultado = 0;
	
	cout<<"Digite el valor de a: "; cin>>a;
	cout<<"Digite el valor de b: "; cin>>b;
	cout<<"Digite el valor de c: "; cin>>c;
	cout<<"Digite el valor de d: "; cin>>d;
	cout<<"Digite el valor de e: "; cin>>e;
	cout<<"Digite el valor de f: "; cin>>f;
	
	resultado = (a+(b/c))/(d+(e/f));
	
	cout.precision(2);//recorta los numeros despues de la coma decimal a 2
	cout<<"El resultado es: "<<resultado;
	
	return 0;
}
