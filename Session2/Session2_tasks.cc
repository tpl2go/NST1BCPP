/*
 * SimpleAdder.cc
 *
 *  Created on: 17 Oct 2015
 *      Author: tpl
 */

// Program to add two integers typed by user at keyboard
#include <iostream>
#include <list>
#include <cmath>
using namespace std;
int exercise1() {
	double tin, tout;
	cout << "Enter time in number of years:" << endl;
	cin >> tin;
	tout = tin * 365 * 24 * 60 * 60;
	cout << "The time in seconds is " << tout << endl;
	return 0;
}

int exercise2() {
	long sum=0;
	int N;
	cout << "We are summing the first N odd numbers" << endl;
	cout << "What do you want N to be?: ";
	cin >> N;
	for (int i=0; i<N; i++) {
		sum = sum + (2*i+1);
	}
	cout << "sum of the first" << N << "odd numbers is:";
	cout << sum;
	return 0;
}

int exercise3() {
	// initialise array
	long double results [20];
	for (int i=0; i<20; i++){
		results[i] = 0.0;
	}
	results[0] = 1;
	for (int i=0; i<20;i++){
		results[i] = 1.0 + 1.0 / results[i-1];
	}

	for (int i=0; i<20;i++){
		cout << results[i] << endl;
	}

	return 0;
}

int exercise4() {
	// initialise array
	long double results [20];
	for (int i=0; i<20; i++){
		results[i] = 0.0;
	}
	cin >> results[0];
	for (int i=0; i<20;i++){
		results[i] = 2 + 1.0 / results[i-1];
	}

	for (int i=0; i<20;i++){
		cout << results[i] << endl;
	}

	return 0;
}

int exercise5() {

	// initialise array
	long double results [20];
	for (int i=0; i<20; i++){
		results[i] = 0.0;
	}
	results[0] = 1.0;
	for (int i=0; i<20;i++){
		results[i] = sqrt(1 + results[i-1]);
	}

	for (int i=0; i<20;i++){
		cout << results[i] << endl;
	}

	return 0;
}

int exercise6() {
	cout << "We are finding all primes less than or equals to N" << endl;
	cout << "What do you want N to be?: ";
	int N;
	cin >> N;
	// initialise array
	std::list<int> results;

	for (int i=2; i<N; i++){
		bool isPrime = true;
		for (list<int>::iterator it=results.begin(); it != results.end(); ++it) {
			if (i%(*it)==0) {
				isPrime = false;
				break;
			}
		}
		if (isPrime) {
			results.push_back(i);
		}
	}

	for (list<int>::iterator it=results.begin(); it != results.end(); ++it) {
		cout << *it << endl;
	}

	return 0;
}

int main() {
	exercise6();
}
