#include "Particle.h"
#include "ParticleParameters.h"
#include "ofMath.h"
ParticleParameters param;
Particle::Particle()
{
	//all created particles will be inactive by default
	setup();
	isAlive = false;
}

void Particle::setup()
{
	pos = emitterCenter + randPointInsideCircle(param.emitterRadius);
	vel = randPointInsideCircle(param.velLimit);
	time = 0;
	lifeTime = param.lifetimeSec;
	isAlive = true; //particle becomes activeand begins to fly
	radius = 3;
	acc = 0.0;
}
void Particle::Forces(float dt)
{
	ofVec3f a; //acceleration
	ofVec3f delta = pos - param.emitterCenter;

	float len = delta.length();

	if (ofInRange(len, 0, param.forceRadius))
	{
		delta.normalize();

		a += delta * param.force;

		a.x += -delta.y * param.spinningForce;
		a.y += delta.z * param.spinningForce;
		a.z += delta.x * param.spinningForce;
	}
	vel += a * dt;
	vel *= (1 - param.friction);
}
void Particle::update(float dt)
{
	if (isAlive)
	{
		//vel.rotate(0, 0, param.rotateS * dt);
		if (param.forceWorking)
		{
			//pos += vel * dt;
			Forces(dt);
		}
		//euler, update the position
		if (param.run)
		{
			pos += vel * dt;
			float r = ofRandom(180, param.emitterRadius);
			acc += 0.1;
		}
		time += dt;

		if (time >= lifeTime)
		{
			isAlive = false; // particle dies
		}
	}
}

void Particle::draw()
{
	if (isAlive)
	{
		float size = ofMap(fabs(time - lifeTime / 2), 0, lifeTime, radius, radius + 5);
		color = ofColor::red;
		float hue = ofMap(time, 0, lifeTime, 0, 128);
		float saturation = ofMap(time, 0, lifeTime , 255, 200);
		//float brightness = ofMap(time, 0, lifeTime * 4, 255, 0);

			color.setHue(hue);
			color.setSaturation(saturation);
		//}
		ofSetColor(color);
		//sphere.draw();
		ofDrawSphere(pos, size);
	}
}

ofVec3f Particle::randPointInsideCircle(float maxRand) {
	ofVec3f point;
	float radius = ofRandom(0, maxRand);
	float angle = ofRandom(2, M_TWO_PI);

	float azimuthAngle = ofRandom(0, 360);
	float elevationAngle = ofRandom(-90, 180);
	float r = param.emitterRadius;
	//r = ofRandom(maxRand);
	point.x = r * cos(azimuthAngle / 180 * M_TWO_PI / 2) * sin(elevationAngle / 180 * M_TWO_PI / 2);

	point.y = r * sin(azimuthAngle / 180 * M_TWO_PI / 2) * sin(elevationAngle / 180 * M_TWO_PI / 2);

	point.z = r * cos(elevationAngle / 180 * M_TWO_PI / 2);

	float theta = ofRandom(0, TWO_PI);
	float theta_r = ofRandom(0, TWO_PI);

	float t = maxRand * 0.5;
	float x = t * sin(theta) * cos(theta) * log(abs(theta));
	float y = -t * pow(abs(theta), 0.3) * sqrt(cos(theta));

	//RYBA
	//float x =- (13 * t * cos(theta) - 5 * t * cos(2 * theta) - 2 * t * cos(3 * theta) - t * cos(4 * theta));
	//float y = 16 * t * pow(sin(theta), 3) * cos(theta);

	//float x = 16 * t * pow(sin(theta), 3) * sin(theta);
	//float y =  -(13 * t * cos(theta) - 5 * t * cos(2 * theta) - 2 * t * cos(3 * theta) - t * cos(4 * theta));

	//f = ofVec3f(x, y, 0);
	//point.x = f.x;
	//point.y = f.y;
	//point.z = ofRandom(-10, 10);
	//
	//
	//float theta_r = ofRandom(0, TWO_PI);
	//float theta = ofRandom(0, TWO_PI);

	//float r = ofRandom(2, maxRand) / 10;
	//float x = 16 * pow(sin(theta), 3);
	//float y = 13 * cos(theta) - 5 * cos(2 * theta) - 2 * cos(3 * theta) - cos(4 * theta);
	//float x_r = cos(theta_r) * x - sin(theta_r) * y;
	//float y_r = sin(theta_r) * x + cos(theta_r) * y;
	//f = ofVec3f(x, y, 0);
	//point.x =f.x;
	//point.y = f.y;
	//point.z = 0;
	//point.z = -tan( angle) * radius;
	return point;
}