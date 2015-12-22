#include <iostream>
#include <fstream>
#include <cmath>
#define _USE_MATH_DEFINES
using namespace std;

#define N 36

enum CoordSystem {CARTESIAN, POLAR};

class Vector2D {
	// TODO: make mult and add function aware of coordinate systems
public :
	CoordSystem csys;
	double x;
	double y;

public :
	Vector2D(double a=0.0, double b=0.0, CoordSystem cs = CARTESIAN) {
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

	double mag() {
		return sqrt(x*x + y*y);
	}
	double magsquare() {
		return x*x + y*y;
	}
};

Vector2D force(Vector2D pos) {
	/* 1/r^2 force law */
	return pos.mult(-2.0/(pos.magsquare()*pos.mag()));

	/* 1/r force law */
	//return pos.mult(-2.0/(pos.magsquare()));
}


struct Particle {
	Vector2D pos;
	Vector2D vel;
	Vector2D acc;
	double mass = 1.0;
};

struct Simulation {
	double endTime = 10; // seconds
	double numStep = 10000;
	double timeStep = endTime/numStep;
	double time = 0.0;
};

void eulerUpdate(Particle& p1, Simulation& sim) {
	p1.pos = p1.pos.add(p1.vel.mult(sim.timeStep));
	p1.acc = force(p1.pos).mult(1/p1.mass);
	p1.vel = p1.vel.add(p1.acc.mult(sim.timeStep));
}

void leapfrogUpdate(Particle& p1, Simulation& sim) {
	p1.pos = p1.pos.add(p1.vel.mult(0.5*sim.timeStep));
	sim.time += 0.5*sim.timeStep;

	p1.acc = force(p1.pos).mult(1/p1.mass);
	p1.vel = p1.vel.add(p1.acc.mult(sim.timeStep));

	p1.pos = p1.pos.add(p1.vel.mult(0.5*sim.timeStep));
	sim.time -= 0.5*sim.timeStep;
}

void simulate(ofstream& logger) {
	Simulation sim1;
	sim1.endTime = 20; // seconds
	sim1.numStep = 20000;
	sim1.timeStep = sim1.endTime/sim1.numStep;
	sim1.time = 0.0;

	Particle parts[N];
	for(int i=0; i<N; i++) {
		Particle p;
		p.pos = Vector2D(1.0,1.0);
		p.vel = Vector2D(cos(2*M_PI*i/N),sin(2*M_PI*i/N));
		p.mass = 1.0;
		p.acc = Vector2D(0.0,0.0);
		parts[i] = p;
	}

	while (sim1.time<sim1.endTime){
		for(int i=0; i<N; i++) {
			leapfrogUpdate(parts[i],sim1);
		}
		sim1.time += sim1.timeStep;

		logger << sim1.time << "\t";
		for(int i=0; i<N; i++) {
			logger << parts[i].pos.x << "\t" << parts[i].pos.y << "\t" \
				<< parts[i].vel.x << "\t" << parts[i].vel.y << "\t" \
				<< parts[i].acc.x << "\t" << parts[i].acc.y << "\t";
		}
		logger << "\n";

	}
	logger.close();
}


int main() {
	ofstream logger;
	logger.open ("task2.dat");
	logger << "time\t ";
	for (int i=0; i<N; i++) {
		logger << "x pos\t" << "y pos\t" \
			<< "x vel\t" << "y vel\t" \
			<< "x acc\t" << "y acc\t";
	}
	logger << "\n";
	simulate(logger);
}
