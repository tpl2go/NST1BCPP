/*
 * algo.c
 *
 *  Created on: 1 Nov 2015
 *      Author: tpl
 */
#include <iostream>
using namespace std;

double force(double pos) {
	return -10*pos;
}

void euler() {
	double endTime = 10; // seconds
	double numStep = 10000;
	double timeStep = endTime/numStep;

	double time = 0.0;
	double pos = 0.0;
	double vel = 1.0;

	double mass = 1.0;
	while (time<endTime){
		double f = force(pos);
		pos += timeStep*vel;
		vel += timeStep*f/mass;
		time += timeStep;
	}
}

void leapfrog() {
	// In the leapfrog method, the position and velocity are half
	// steps in time away from each other. Assume velocity is initially
	// half step of time ahead of position. When velocity updates
	// position with a full time step, it brings position half step ahead in time of itself.
	// From position, we compute the force and then update velocity a full time step
	// bringing velocity once again half step in time ahead of position

	// This leapfrog algorithm is slightly different from the one I studied.
	// In the one i studied, the velocity is out of sync with position and force.
	// in this algo the force is out of sync with the position and velocity.


	double endTime = 10; // seconds
	double numStep = 10000;
	double timeStep = endTime/numStep;

	double time = 0.0;
	double pos = 0.0;
	double vel = 1.0;

	double mass = 1.0;
	while (time<endTime){
		pos += 0.5*timeStep*vel;
		time += 0.5*timeStep;
		double f = force(pos);
		vel += timeStep*f/mass;
		pos += 0.5*timeStep*vel;
		time += 0.5*timeStep;
	}
}
