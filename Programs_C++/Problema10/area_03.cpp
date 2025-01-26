/*We will calculate the length and area of 10 circles of different radii Ri =
* 1:28 + i,
i = 1; 2; : : : ; 10. We will store the values of the radii in an array R[10] of
the double type.*/


#include <iostream>
#include <fstream>
using namespace std;

int main(void) {

	const int N = 10;
	const double PI = 3.1415926535897932;
	double R[N];
	double area, perimeter;
	int i;

	for (i = 0; i < N; i++) {
		cout << "Enter radius of circle: ";
		cin >> R[i];
		cout << "i = " << (i + 1) << " R(i) = " << R[i] << endl;
	}
	ofstream myfile("area.csv");
	for (i = 0; i < N; i++) {
		perimeter = 2.0 * PI * R[i];
		area = PI * R[i] * R[i];
		myfile << R[i] << "," << perimeter << "," << area << endl;
	}
	myfile.close();	
	return 0;

}
