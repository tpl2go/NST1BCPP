#include <iostream>
#include <stdlib.h>
#include <time.h>       /* time */
#include <math.h>
using namespace std;
#define N 4

void printMatrix(double mat[][N]) {
	for (int j=0; j<N; j++){
		for (int i = 0; i<N; i++){
			cout << mat[j][i] <<  " ";
		}
		cout << endl;
	}

}

int main() {
//TODO: Add pivoting function

	// Initialize random seed
	srand (time(NULL));

	double matrix_L[N][N];
	double matrix_U[N][N];
	double matrix_A[N][N];

	// Initialize the matrices
	for (int j = 0; j<N; j++){
		for (int i = 0; i<N; i++){
			matrix_A[j][i] = floor(100* ((double)rand() / RAND_MAX )) + 1.0;
			matrix_L[j][i] = 0.0;
			matrix_U[j][i] = 0.0;
		}
	}
	cout << "~~~~~~~~Check initialization~~~~~~~~" << endl;
	cout << "MATRIX A" << endl;
	printMatrix(matrix_A);
	cout << "MATRIX L" << endl;
	printMatrix(matrix_L);
	cout << "MATRIX U" <<endl;
	printMatrix(matrix_U);

	// Decompose!
	for (int j = 0; j<N; j++){
		matrix_L[j][j] = 1.0;
		// row
		for (int i = j; i<N; i++){
			double ans = matrix_A[j][i];
			for (int l=0; l<j; l++){
				ans -= matrix_U[l][i]*matrix_L[j][l];
			}
			matrix_U[j][i] = ans;
		}
		// column
		for (int k = j+1; k<N; k++){
			double ans = matrix_A[k][j];
			for (int l=0; l<j; l++){
				ans -= matrix_U[l][j]*matrix_L[k][l];
			}
			matrix_L[k][j] = ans / matrix_U[j][j] ;
		}
	}
	cout << "~~~~~~~~REULSTS~~~~~~~~" << endl;
	cout << "MATRIX L" << endl;
	printMatrix(matrix_L);
	cout << "MATRIX U" <<endl;
	printMatrix(matrix_U);

	return 0;
}


