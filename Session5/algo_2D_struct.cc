/*
 * algo.c
 *
 *  Created on: 1 Nov 2015
 *      Author: tpl
 */
#include <iostream>
#include <fstream>
using namespace std;



enum CoordSystem {CARTESIAN, POLAR};

class Vector2D {
	// TODO: make mult and add function aware of coordinate systems
public :
	CoordSystem csys;
	double x;
	double y;

public :
	Vector2D(double a, double b, CoordSystem cs = CARTESIAN) {
		x = a;
		y = b;
		csys = cs;
	}

	Vector2D mult(double m) {
		double xx = x*m;
		double yy = y*m;

		return Vector2D(xx,yy);
	}

	Vector2D add(Vector2D v) {
		double xx = x + v.x;
		double yy = y + v.y;

		return Vector2D(xx,yy);
	}
};

Vector2D force(Vector2D pos) {
	return pos.mult(-1.0);
}

void euler(ofstream& logger) {
	double endTime = 10; // seconds
	double numStep = 10000;
	double timeStep = endTime/numStep;

	double time = 0.0;
	Vector2D pos = Vector2D(1.0,0.0);
	Vector2D vel = Vector2D(1.0,2.0);

	double mass = 1.0;
	while (time<endTime){
		Vector2D f = force(pos);
		pos = pos.add(vel.mult(timeStep));
		vel = vel.add(f.mult(timeStep/mass));
		time += timeStep;

		logger << time << "\t" << pos.x << "\t" << pos.y << "\t" \
				<< vel.x << "\t" << vel.y << "\t" \
				<< f.x << "\t" << f.y << "\n";

	}
	logger.close();
}

void leapfrog(ofstream& logger) {
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
	double numStep = 100;
	double timeStep = endTime/numStep;

	double time = 0.0;
	Vector2D pos = Vector2D(1.0,0.0);
	Vector2D vel = Vector2D(1.0,2.0);

	double mass = 1.0;
	while (time<endTime){
		pos = pos.add(vel.mult(0.5*timeStep));
		time += 0.5*timeStep;
		Vector2D f = force(pos);
		vel = vel.add(f.mult(timeStep/mass));
		pos = pos.add(vel.mult(0.5*timeStep));
		time += 0.5*timeStep;

		logger << time << "\t" << pos.x << "\t" << pos.y << "\t" \
				<< vel.x << "\t" << vel.y << "\t" \
				<< f.x << "\t" << f.y << "\n";
	}
	logger.close();

}

int main(){
		ofstream logger;
		logger.open ("logger.dat");
		logger << "time\t " << "x pos\t" << "y pos\t" \
				<< "x vel\t" << "y vel\t" \
				<< "x force\t" << "y force\n";

		leapfrog(logger);
		return 0;
	}
