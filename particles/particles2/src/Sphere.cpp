#include "Sphere.h"
#include "ParticleParameters.h"
#include "ofMath.h"
ParticleParameters paramSphere;

Sphere::Sphere()
{
	//all created particles will be inactive by default
	isAlive = false;
}

void Sphere::setup()
{
	pos = paramSphere.emitterCenter + randPointInsideCircle(paramSphere.emitterRadius);
	vel = randPointInsideCircle(param.velLimit);
	time = 0;
	radius = 100;
	lifeTime = paramSphere.lifetimeSec;
	isAlive = true; //particle becomes activeand begins to fly

}
void Sphere::Forces(float dt)
{
	ofVec3f a; //acceleration
	ofVec3f delta = pos - paramSphere.emitterCenter;
	float len = delta.length();

	if (ofInRange(len, 0, paramSphere.forceRadius))
	{
		delta.normalize();
		vel = ofVec3f(0, 0, 0);

		a += delta * param.force;

		a.x += -delta.y * paramSphere.spinningForce;
		a.y += delta.z * paramSphere.spinningForce;
		a.z += delta.x * paramSphere.spinningForce;
	}
	vel += a * dt;
	vel *= (1 - paramSphere.friction);
}
void Sphere::update(float dt)
{

	//if (isAlive)
	//{
	//	//vel.rotate(0, 0, param.rotateS * dt);
	//	if (param.forceWorking)
	//	{
	//		Forces(dt);
	//	}
	//	//euler, update the position
	//	if (param.run)
	//	{
	//		pos += vel * dt;
	//	}
	//	time += dt;

	//	if (time >= lifeTime)
	//	{
	//		isAlive = false; // particle dies
	//	}
	//}
}

void Sphere::draw()
{
		float size = ofMap(fabs(time - lifeTime / 2), 0, lifeTime / 2, radius, radius);
		ofColor color = ofColor::red;
		float hue = ofMap(time, 0, lifeTime * 2, 100, 100);
		color.setHue(hue);
		ofSetColor(color);
		//ofNoFill();
		ofDrawSphere(pos, size);
}

ofVec3f Sphere::randPointInsideCircle(float maxRand) {
	ofVec3f point;
	float radius = ofRandom(10, maxRand);
	float angle = ofRandom(2, M_TWO_PI);

	point = ofVec3f(-300, 1, 1);
	return point;
}