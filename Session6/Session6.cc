#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>       /* time */
#include <cmath>
#include <assert.h>
using namespace std;



struct config {
	int numBalls; // number of balls
	int length; // size of box [meters]
};

struct simulation {
	double t;
	double dt;
	double endTime;
	double numStep;
};

struct particle {
	double x; // position
	double v; // velocity
	double m; // mass
	double im; // inverse mass
	double a; // radius
};

double pos_to_distance(particle &p1, particle &p2) {
	/*
	 * Overwrite to handle 2D position
	 */
	return fabs(p1.x-p2.x);
}

bool check_collide(particle &p1, particle &p2) {
	bool ans = (pos_to_distance(p1,p2) < (p1.a + p2.a));
	return ans;
}

void collide(particle &p1, particle &p2) {
	/* Assume p1 and p2 will collide
	 * Modify state of p1 and p2
	 */

	double mom1 = p1.m*p1.v;
	double mom2 = p2.m*p2.v;

	// Zero Momentum Frame method
	double vzmf = (mom1 + mom2)/(p1.m + p2.m);
	double vprime1 = (p1.v - vzmf);
	double vprime2 = (p2.v - vzmf);

	p1.v = vzmf - vprime1;
	p2.v = vzmf - vprime2;


}

bool resolve_collision(particle *p, config con) {
	/* N^2 algorithm to find collision
	 * returns true if there was at least a collision
	 */
	bool collision = false;
	for (int i=0; i<con.numBalls;i++) {
		for (int j=i+1; j<con.numBalls; j++){
			if (check_collide(p[i],p[j])) {
				collide(p[i],p[j]);
				collision = true;
			}
		}
	}
	return collision;
}

void bounce(particle &p1, config con){
	/* particle reflects off boundary
	 * in 1D config information is not needed
	 * in 2D we need to know which wall particle bounces off
	 */
	// VERY PRIMITIVE BOUNCE
	p1.v *= -1;
}

void resolve_bounce(particle *p, config con){
	/*
	 * find all particles that collide with boundary
	 */
	for (int i=0; i<con.numBalls; i++ ){
		if ((p[i].x<p[i].a) or ((con.length - p[i].x) <p[i].a)) {
			bounce(p[i],con);
		}
	}
}
void update(particle *p, simulation sim, config con) {
	/*
	 * update position states of all particle
	 */
	for (int i=0; i<con.numBalls; i++) {
		p[i].x += p[i].v*sim.dt;
	}
}


// base class
class Logger {
public:
	ofstream log;
	Logger(char* name){
		log.open(name);
	}
	void log1(double arg1){
		log << arg1 << "\n";
	}
	void log2(double arg1, double arg2){
		log << arg1 << "\t" << arg2 << "\n";
	}
	void log3(double arg1, double arg2, double arg3){
		log << arg1 << "\t" << arg2 << "\t" << arg3 << "\n";
	}

};

class KELogger: public Logger {
public:
	config con;
	KELogger(char* name, config config1) :Logger(name) {
		con = config1;
		log << "time\t ";
		for (int i=0; i<con.numBalls; i++) {
			log << "KE" << i << "\t";
		}
		log << "\n";
	}
	void log_KE(particle *p, simulation sim) {
		log << sim.t << "\t";
		for (int i=0; i<con.numBalls; i++) {
			log << kinetic_energy(p[i]) << "\t";
		}
		log << "\n";
	}
private:
	double kinetic_energy(particle &p1) {
		return p1.v*p1.v*0.5*p1.m;
	}
};

class VelocityLogger: public Logger {
public:
	config con;
	VelocityLogger(char* name, config config1) :Logger(name) {
		con = config1;
		log << "time\t ";
		for (int i=0; i<con.numBalls; i++) {
			log << "Velocity" << i << "\t";
		}
		log << "\n";
	}
	void log_velocity(particle *p, simulation sim) {
		log << sim.t << "\t";
		for (int i=0; i<con.numBalls; i++) {
			log << p[i].v << "\t";
		}
		log << "\n";
	}
};

class PositionLogger: public Logger {
public:
	config con;
	PositionLogger(char* name, config config1) :Logger(name) {
		con = config1;
		log << "time\t ";
		for (int i=0; i<con.numBalls; i++) {
			log << "Pos" << i << "\t";
		}
		log << "\n";
	}
	void log_position(particle *p, simulation sim) {
		log << sim.t << "\t";
		for (int i=0; i<con.numBalls; i++) {
			log << p[i].x << "\t";
		}
		log << "\n";
	}
};

class SimLogger: public Logger {
public:
	config con;
	SimLogger(char* name, simulation sim, config config1) :Logger(name) {
		con = config1;
		log << "endTime:\t " << sim.endTime << "\n";
		log << "numStep \t " << sim.numStep << "\n";
		log << "numBalls \t " << con.numBalls << "\n";
		log << "boxSize \t " << con.length << "\n";
	}
};

class ScatterLogger: public Logger {
public:
	double arg1 = NULL;
	double arg2 = NULL;
	ScatterLogger(char* name) :Logger(name) {
		//TODO
	}
	void log_scatter(double farg1, double farg2) {
		if (farg1!=arg1 or farg2!=arg2) {
			arg1 = farg1;
			arg2 = farg2;
			log << farg1 << "\t" << farg2 << "\n";
		}
	}
};

bool sanitycheck(particle *p, simulation sim, config con){
	double size=0.0;
	for (int i=0; i<con.numBalls; i++) {
		size += 2* p[i].a;
	}
	return (size < con.length);
}

void task1(){
	/* In Task 1, we create an animation of the balls colliding.
	 * We log the position of the balls and animate with gnuplot
	 */
	// initialization
	srand (time(NULL));

	// create simulation
	struct simulation sim1;
	sim1.t=0.0;
	sim1.endTime = 1000;
	sim1.numStep = 1000000;
	sim1.dt = sim1.endTime/sim1.numStep;

	// create configuration
	struct config config1;
	config1.numBalls = 10;
	config1.length = config1.numBalls;

	// create particles
	struct particle particles[config1.numBalls];
	for (int i=0; i<config1.numBalls; i++) {
		particles[i].x = (double) (i+0.5)*config1.length/config1.numBalls;
		particles[i].v = 1.0;
		particles[i].im = ((double)rand())/ RAND_MAX;
		particles[i].m = 1.0/particles[i].im;
		particles[i].a = 0.0625;
	}

	// create logger
	PositionLogger poslogger("TASK1-pos.dat", config1);
	SimLogger simlogger("TASK1-sim.dat",sim1, config1);

	// Sanity check
	assert (sanitycheck(particles, sim1, config1));

	// time domain simulation
	for (int i=0; i<sim1.numStep; i++) {
		// update all positions
		update(particles,sim1,config1);
		// resolve collisions
		bool collision = resolve_collision(particles, config1);
		// resolve bounces
		resolve_bounce(particles, config1);
		// update sim
		sim1.t += sim1.dt;

		if (i%200==0) {
			/* To log only when there was a collision, do
			 * if (collision)
			 */
			poslogger.log_position(particles, sim1);
		}

	}

	cout << "TASK 1 Done!";
}

void task2(){
	/* In Task 2 we create a scatterplot of velocities in a linear 2 particle system
	 */

	// initialization
	srand (time(NULL));

	// create simulation
	struct simulation sim1;
	sim1.t=0.0;
	sim1.endTime = 1000;
	sim1.numStep = 1000000;
	sim1.dt = sim1.endTime/sim1.numStep;

	// create configuration
	struct config config1;
	config1.numBalls = 2;
	config1.length = config1.numBalls;

	// create particles
	struct particle particles[config1.numBalls];
	for (int i=0; i<config1.numBalls; i++) {
		particles[i].x = (double) (i+0.5)*config1.length/config1.numBalls;
		particles[i].v = 1.0;
		particles[i].im = ((double)rand())/ RAND_MAX;
		particles[i].m = 1.0/particles[i].im;
		particles[i].a = 0.0625;
	}

	// create logger
	SimLogger simlogger("TASK2-sim.dat",sim1, config1);
	ScatterLogger scatterlogger("TASK2-scatter.dat");

	// Sanity check
	assert (sanitycheck(particles, sim1, config1));

	// time domain simulation
	for (int i=0; i<sim1.numStep; i++) {
		// update all positions
		update(particles,sim1,config1);
		// resolve collisions
		bool collision = resolve_collision(particles, config1);
		// resolve bounces
		resolve_bounce(particles, config1);
		// update sim
		sim1.t += sim1.dt;

		/* Scatter Log */
		scatterlogger.log_scatter(particles[0].v,particles[1].v);

	}

	cout << "TASK2 Done!";
}

void task3(){
	/* In Task 3 we create a scatterplot of 2 particle's velocities in a linear N particle system
	 */

	// initialization
	srand (time(NULL));

	// create simulation
	struct simulation sim1;
	sim1.t=0.0;
	sim1.endTime = 1000;
	sim1.numStep = 1000000;
	sim1.dt = sim1.endTime/sim1.numStep;

	// create configuration
	struct config config1;
	config1.numBalls = 10;
	config1.length = config1.numBalls;

	// create particles
	struct particle particles[config1.numBalls];
	for (int i=0; i<config1.numBalls; i++) {
		particles[i].x = (double) (i+0.5)*config1.length/config1.numBalls;
		particles[i].v = 1.0;
		particles[i].im = ((double)rand())/ RAND_MAX;
		particles[i].m = 1.0/particles[i].im;
		particles[i].a = 0.0625;
	}

	// create logger
	SimLogger simlogger("TASK3-sim.dat",sim1, config1);
	ScatterLogger scatterlogger("TASK3-scatter.dat");

	// Sanity check
	assert (sanitycheck(particles, sim1, config1));

	// time domain simulation
	for (int i=0; i<sim1.numStep; i++) {
		// update all positions
		update(particles,sim1,config1);
		// resolve collisions
		bool collision = resolve_collision(particles, config1);
		// resolve bounces
		resolve_bounce(particles, config1);
		// update sim
		sim1.t += sim1.dt;

		/* Scatter Log */
		scatterlogger.log_scatter(particles[0].v,particles[1].v);

	}
	cout << "TASK3 Done!";
}

void task4(){
	/* In Task 4 we find the average KE of each particle
	 * in a linear N particle system
	 */

	// initialization
	srand (time(NULL));

	// create simulation
	struct simulation sim1;
	sim1.t=0.0;
	sim1.endTime = 1000;
	sim1.numStep = 1000000;
	sim1.dt = sim1.endTime/sim1.numStep;

	// create configuration
	struct config config1;
	config1.numBalls = 10;
	config1.length = config1.numBalls;

	// create particles
	struct particle particles[config1.numBalls];
	for (int i=0; i<config1.numBalls; i++) {
		particles[i].x = (double) (i+0.5)*config1.length/config1.numBalls;
		particles[i].v = 1.0;
		particles[i].im = ((double)rand())/ RAND_MAX;
		particles[i].m = 1.0/particles[i].im;
		particles[i].a = 0.0625;
	}

	// create logger
	SimLogger simlogger("TASK4-sim.dat",sim1, config1);
	KELogger KElogger("TASK4-KE.dat", config1);

	// Sanity check
	assert (sanitycheck(particles, sim1, config1));

	// time domain simulation
	for (int i=0; i<sim1.numStep; i++) {
		// update all positions
		update(particles,sim1,config1);
		// resolve collisions
		bool collision = resolve_collision(particles, config1);
		// resolve bounces
		resolve_bounce(particles, config1);
		// update sim
		sim1.t += sim1.dt;

		if (collision) {
			/* To log only when there was a collision, do
			 * if (collision)
			 */
			KElogger.log_KE(particles, sim1);
		}

	}
	cout << "TASK4 Done!";
}

void task5(){
	/* In Task 5 we find the velocity of particles
	 * in a linear N particles system
	 */

	// initialization
	srand (time(NULL));

	// create simulation
	struct simulation sim1;
	sim1.t=0.0;
	sim1.endTime = 1000;
	sim1.numStep = 1000000;
	sim1.dt = sim1.endTime/sim1.numStep;

	// create configuration
	struct config config1;
	config1.numBalls = 10;
	config1.length = config1.numBalls;

	// create particles
	struct particle particles[config1.numBalls];
	for (int i=0; i<config1.numBalls; i++) {
		particles[i].x = (double) (i+0.5)*config1.length/config1.numBalls;
		particles[i].v = 1.0;
		particles[i].im = ((double)rand())/ RAND_MAX;
		particles[i].m = 1.0/particles[i].im;
		particles[i].a = 0.0625;
	}

	// create logger
	SimLogger simlogger("TASK5-sim.dat",sim1, config1);
	VelocityLogger vlogger("TASK5-vel.dat", config1);

	// Sanity check
	assert (sanitycheck(particles, sim1, config1));

	// time domain simulation
	for (int i=0; i<sim1.numStep; i++) {
		// update all positions
		update(particles,sim1,config1);
		// resolve collisions
		bool collision = resolve_collision(particles, config1);
		// resolve bounces
		resolve_bounce(particles, config1);
		// update sim
		sim1.t += sim1.dt;

		if (collision) {
			/* To log only when there was a collision, do
			 * if (collision)
			 */
			vlogger.log_velocity(particles, sim1);
		}

	}
	cout << "TASK5 Done!";
}

void task6(){
	/* In Task 6 we find the kinetic energy of a particle
	 * in a linear N particles system
	 */

	// initialization
	srand (time(NULL));

	// create simulation
	struct simulation sim1;
	sim1.t=0.0;
	sim1.endTime = 1000;
	sim1.numStep = 1000000;
	sim1.dt = sim1.endTime/sim1.numStep;

	// create configuration
	struct config config1;
	config1.numBalls = 10;
	config1.length = config1.numBalls;

	// create particles
	struct particle particles[config1.numBalls];
	for (int i=0; i<config1.numBalls; i++) {
		particles[i].x = (double) (i+0.5)*config1.length/config1.numBalls;
		particles[i].v = 1.0;
		particles[i].im = ((double)rand())/ RAND_MAX;
		particles[i].m = 1.0/particles[i].im;
		particles[i].a = 0.0625;
	}

	// create logger
	SimLogger simlogger("TASK6-sim.dat",sim1, config1);
	KELogger KElogger("TASK6-KE.dat", config1);

	// Sanity check
	assert (sanitycheck(particles, sim1, config1));

	// time domain simulation
	for (int i=0; i<sim1.numStep; i++) {
		// update all positions
		update(particles,sim1,config1);
		// resolve collisions
		bool collision = resolve_collision(particles, config1);
		// resolve bounces
		resolve_bounce(particles, config1);
		// update sim
		sim1.t += sim1.dt;

		if (collision) {
			/* To log only when there was a collision, do
			 * if (collision)
			 */
			KElogger.log_KE(particles, sim1);
		}

	}
	cout << "TASK6 Done!";
}
int main() {
	task5();
}
