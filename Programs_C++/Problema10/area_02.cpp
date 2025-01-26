/*We will calculate the length and area of 10 circles of different radii Ri = 1:28 + i,
i = 1; 2; : : : ; 10. We will store the values of the radii in an array R[10] of
the double type.*/


#include <iostream>
using namespace std;

int main(void) {
	double PI = 3.1415926535897932;
	double R[10];
	double area, perimeter;
	int i;

	R[0] = 2.18;
	for (i = 1; i < 10; i++) {
		R[i] = R[i - 1] + 1.0;
	}

	for (i = 0; i < 10; i++) {
		perimeter = 2.0 * PI * R[i];
		area = PI * R[i] * R[i];
		cout << (i + 1) << ") R= " << R[i] << ", perimeter= " << perimeter << ", area= " << area << '\n';
	}

	return 0;
}
