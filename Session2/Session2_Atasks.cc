/*
 * Session2_Atasks.cc
 *
 *  Created on: 18 Oct 2015
 *      Author: tpl
 */

#include <iostream>
#include <vector>
using namespace std;

int LeviCivita(vector<int> suffix) {
	int n = suffix.size();
	bool checklist[n];
	for (int i=0;i<n;i++) {
		checklist[i] = false;
		suffix[i] = suffix[i] - 1;
	}
	int next, index=0, checkcount=0, cyclecount=0;

	// check for no repeats
	for (int i=0; i<n; i++) {
		for (int j=0; j<i ;j++) {
			if (suffix[i] == suffix[j]) {
				return 0;
			}
		}
	}

	while (checkcount<n) {
		// find an unchecked element
		int k=0;
		while (checklist[index]){
			index = (index + 1)%n;
			k++;
			if (k>n) {
				throw 0;
			}
		}
		// branch out
		checklist[index] = true;
		checkcount++;
		next = suffix[index];

		// draw back
		if (checklist[next]){
			cyclecount++;
			index = next;
		}
		else {
			index = next;
		}
	}

	int result =  (cyclecount%2==0) ? 1 : -1;
	result = result * ((n%2==0) ? 1 : -1);

	return result;

}

int main() {
	int permutation [] = {4,1,2,3,5,7,6,8}; // input natural number permutation here
	vector<int> suffix (permutation, permutation + sizeof(permutation) / sizeof(int) );
	cout << LeviCivita(suffix);
}
