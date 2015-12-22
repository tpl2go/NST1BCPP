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

struct Particle {
	Vector2D pos;
	Vector2D vel;
	double mass = 1.0;
};

struct Simulation {
	double endTime = 10; // seconds
	double numStep = 10000;
	double timeStep = endTime/numStep;
	double time = 0.0;
};

void eulerUpdate(Particle& p1, Simulation& sim) {
	Vector2D f = force(p1.pos);
	p1.pos = p1.pos.add(p1.vel.mult(sim.timeStep));
	p1.vel = p1.vel.add(f.mult(sim.timeStep/p1.mass));
	sim.time += sim.timeStep;
}

void leapfrogUpdate(Particle& p1, Simulation& sim) {
	p1.pos = p1.pos.add(p1.vel.mult(0.5*sim.timeStep));
	sim.time += 0.5*sim.timeStep;
	Vector2D f = force(p1.pos);
	p1.vel = p1.vel.add(f.mult(sim.timeStep/p1.mass));
	p1.pos = p1.pos.add(p1.vel.mult(0.5*sim.timeStep));
	sim.time += 0.5*sim.timeStep;
}

void simulate(ofstream& logger) {
	Simulation sim1;
	sim1.endTime = 10; // seconds
	sim1.numStep = 10000;
	sim1.timeStep = sim1.endTime/sim1.numStep;
	sim1.time = 0.0;

	Particle p1;
	p1.pos = Vector2D(1.0,0.0);
	p1.vel = Vector2D(1.0,2.0);
	p1.mass = 1.0;

	while (sim1.time<sim1.endTime){
		eulerUpdate(p1,sim1);

		logger << sim1.time << "\t";
			logger << p1.pos.x << "\t" << p1.pos.y << "\t" \
				<< p1.vel.x << "\t" << p1.vel.y << "\t";
		}
		logger << "\n";

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

ofstream initLogger(){
		ofstream logger;
		logger.open ("logger.dat");
		logger << "time\t " << "x pos\t" << "y pos\t" \
				<< "x vel\t" << "y vel\t" \
				<< "x force\t" << "y force\n";

		leapfrog(logger);
		return logger;
	}
