//============================================================================
// Name        : Session1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
using namespace std;

/*
 * This program asks the user to populate an array of
 * members names and an array of visitors names. It then
 * tells the user which visitors are members and which
 * are not.
 *
 * To end the input of members, type "VISITORS"
 * To end the input of visitors, type "END"
 *
 * EXAMPLE USAGE (File Input) :
 *
 *
 * ~~~ Names.txt ~~~
Bob
Glen
Joey
Tan
Carol
VISITORS
Joyce
Bradford
Bob
Tan
END
 *  Run command:
 *  ./Session1 < Names.txt
 *
 *  Output:
~~~~~~~~~~RESULTS~~~~~~~~~~

These visitors are members:
Bob
Tan

These visitors are NOT members:
Glen
Joey
Carol
 */

int main() {
	string Members [100]; // store list of members
	string Visitor [100]; // store list of visitors

	string read = ""; // flag to stop reading and start computing
	int count;

	// Populate Members
	cout << "Enter the list of members" << endl;
	count = 0;
	while (true) {
		cin >> read;
		if (read!="VISITORS") {
			Members[count] = read;
			count++;
		}
		else {
			break;
		}
	}


	// Populate Visitor list
	cout << "Enter the list of visitors" << endl;
	count = 0;
	while (true) {
		cin >> read;
		if (read!="END") {
			Visitor[count] = read;
			count++;
		}
		else {
			break;
		}
	}

	cout << endl << "~~~~~~~~~~RESULTS~~~~~~~~~~" << endl;

	// Check visitors against Members
	cout << endl << "These visitors are members:" << endl;
	for (int i=0;i<100;i++) {
		if (Members[i]=="") {
			break;
		}
		for (int j=0; j<100; j++){
			if (Visitor[j]=="") {
				break;
			}
			if (Visitor[j]==Members[i]){
				cout << Members[i] << endl;
			}
		}
	}

	cout << endl << "These visitors are NOT members:" << endl;
	for (int i=0;i<100;i++) {
		if (Members[i]=="") {
			break;
		}
		for (int j=0; j<100; j++){
			if (Visitor[j]=="") {
				cout << Members[i] << endl;
				break;
			}
			if (Visitor[j]==Members[i]){
				break;
			}
		}
	}

	return 0;
}
