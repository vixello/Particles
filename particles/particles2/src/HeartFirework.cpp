#include "HeartFirework.h"
#include "ParticleParameters.h"
#include "ofMath.h"
ParticleParameters param2;

HeartFirework::HeartFirework()
{
	//all created particles will be inactive by default
	isAlive = false;
}

void HeartFirework::setup()
{
	emitterCenter = param2.emitterCenter;
	pos = emitterCenter + randPointInsideCircle(param2.emitterRadius);
	vel = randPointInsideCircle(param2.emitterRadius);
	time = 0;
	lifeTime = param2.lifetimeSec;
	isAlive = true; //particle becomes activeand begins to fly
	radius = 4;
}
void HeartFirework::Forces(float dt)
{
	ofVec3f a; //acceleration
	ofVec3f delta = pos - param2.emitterCenter;
	float len = delta.length();

	if (ofInRange(len, 0, param2.forceRadius))
	{
		delta.normalize();

		a += delta * param.force;

		a.x += -delta.y * param2.spinningForce;
		a.y += delta.z * param2.spinningForce;
		a.z += delta.x * param2.spinningForce;
	}
	vel += a * dt;
	vel *= (1 - param2.friction);
}
void HeartFirework::update(float dt)
{

	if (isAlive)
	{
		//vel.rotate(0, 0, param.rotateS * dt);
		if (param2.forceWorking)
		{
			Forces(dt);
		}
		//euler, update the position
		if (param2.run)
		{
			//vel.z = 100;
			pos += vel * dt;
		}
		time += dt;

		if (time >= lifeTime)
		{
			isAlive = false; // particle dies
		}
	}
}
void HeartFirework::draw()
{
	if (isAlive)
	{
		float size = ofMap(fabs(time - lifeTime / 2), 0, lifeTime / 2, radius, radius);
		color = ofColor::red;
		float hue = ofMap(time, 0, lifeTime, 128, 255);
		color.setHue(hue);
		ofSetColor(color);
		ofDrawSphere(pos, size);
	}
}

ofVec3f HeartFirework::randPointInsideCircle(float maxRand) {
	ofVec3f point;
	float radius = ofRandom(10, maxRand);
	float t = maxRand*0.1;
	float angle = ofRandom(2, M_TWO_PI);

	float theta_r = ofRandom(0, TWO_PI);
	float theta = ofRandom(0, TWO_PI);

	float r = ofRandom(maxRand);
	float x =  16 * t * pow(sin(theta), 3);
	float y =  13 * t * cos(theta) - 5 * t * cos(2 * theta) - 2 * t * cos(3 * theta) - t*cos(4 * theta);
	//float x_r = cos(theta_r) * x - sin(theta_r) * y;
	//float y_r = sin(theta_r) * x + cos(theta_r) * y;
	f = ofVec3f(x, y, 0);
	point.x = f.x;
	point.y = f.y;
	point.z = ofRandom(-50,50);
	//point.z = -tan( angle) * radius;
	return point;
}