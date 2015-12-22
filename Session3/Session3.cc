#include <iostream>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>
#include <time.h>
using namespace std;

#define ranfx() ((double) rand() / (RAND_MAX)) + 1;
#define ranfy() ((double) rand() / (RAND_MAX));

int main() {
	int seed = time(NULL);
	int N = 1000000;
	srandom(seed);

	int outcome, count_in;
	double x, y;

	// Perform N experiments.
	for(int n=1; n<=N; n++) {
		x = ranfx(); // ranf() returns a real number in [0,1)
		y = ranfy();
		outcome = ( x*y < 1.0 ) ? 1 : 0 ;
		count_in += outcome ;
	}

	cout << "The value of ln(2) is approximately: " << ((double) count_in) / N;

	return 0;
}
