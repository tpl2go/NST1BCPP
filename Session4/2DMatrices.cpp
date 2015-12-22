//============================================================================
// Name        : Session4.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;





int main() {
	int num_row = 10;
	int num_col = num_row;

	int** matrix_a = new int* [num_row];
	int** matrix_b = new int* [num_row];

	for (int i = 0; i<num_col; i++){
		matrix_a[i] = new int [num_col];
		matrix_b[i] = new int [num_col];
	}
	return 0;
}
