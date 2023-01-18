#include "Fire.h"
#include "ParticleParameters.h"
#include "ofMath.h"
ParticleParameters paramFire;
ParticleParameters paramFire2;
Fire::Fire()
{
	//all created particles will be inactive by default
	setup();
	isAlive = false;

}

void Fire::setup()
{
	
	//emitterCenter = ofVec3f(ofGetWidth() / 2 + ofRandom(100, 300), ofGetHeight() / 2 - 100, 0);
	pos = emitterCenter + randPointInsideCircle(paramFire.emitterRadius);
	//pos.x += 500;
	vel = randPointInsideCircle(paramFire.velLimit);
	time = 0;
	//lifeTime = paramFire.lifetimeSec;
	isAlive = true; //particle becomes activeand begins to fly
	radius = 3;
	acc = 0.0;
}
void Fire::Forces(float dt)
{
	ofVec3f a; //acceleration
	ofVec3f delta = pos - emitterCenter;


	float len = delta.length();

	if (ofInRange(len, 0, paramFire.forceRadius))
	{
		delta.normalize();
		vel = ofVec3f(0, 0, 0);

		a += delta * paramFire.force;

		a.x += -delta.y * paramFire.spinningForce;
		a.y += delta.z * paramFire.spinningForce;
		a.z += delta.x * paramFire.spinningForce;
	}
	vel += a * dt;
	vel *= (1 - paramFire.friction);
}
void Fire::update(float dt)
{

	if (isAlive)
	{
		//vel.rotate(0, 0, paramFire.rotateS * dt);
		if (paramFire.forceWorking)
		{
			//pos += vel * dt;
			Forces(dt);
		}
		//euler, update the position
		if (paramFire.run)
		{
			//pos += vel * dt;
			float r = ofRandom(180, paramFire.emitterRadius);
			acc += 0.1;

			pos += ofVec3f(vel.x * cos(acc) + vel.z * sin(acc)+ofRandom(-100,100)*sin(60), abs(vel.y), vel.z * cos(acc) - vel.x * sin(acc)) * dt;

			//pos.y += abs(vel.y * dt)*ofRandom(1,10);
		}
		time += dt;

		if (time >= lifeTime)
		{
			isAlive = false; // particle dies
		}
	}
}

void Fire::draw()
{
	if (isAlive)
	{
		float size = ofMap(fabs(time - lifeTime / 2), 0, lifeTime, radius, radius + 5);
		color = ofColor::red;
		float hue = ofMap(time, 0, lifeTime, 0, 40);
		float saturation = ofMap(time, 0, lifeTime * 1.7, 255, 0);
		float brightness = ofMap(time, 0, lifeTime * 4, 255, 0);
		if (abs(vel.y) <= 4)
		{
			color.setHue(ofMap(time, 0, lifeTime * 2, 0, 36));
		}
		else if (abs(vel.y) <= 15)
		{
			color.setHue(ofMap(time, 0, lifeTime * 1.2, 0, 40));
		}
		else
		{
			color.setHue(hue);
			color.setSaturation(saturation);
		}
		ofSetColor(color);
		//sphere.draw();
		ofDrawSphere(pos, size);

	}
}

ofVec3f Fire::randPointInsideCircle(float maxRand) {
	ofVec3f point;
	float radius = ofRandom(0, maxRand);
	float angle = ofRandom(2, M_TWO_PI);

	float azimuthAngle = ofRandom(0, 360);
	float elevationAngle = ofRandom(-90, 180);
	float r = paramFire.emitterRadius;
	r = ofRandom(maxRand);
	point.x = r * cos(azimuthAngle / 180 * M_TWO_PI / 2) * sin(elevationAngle / 180 * M_TWO_PI / 2);

	point.y = r * sin(azimuthAngle / 180 * M_TWO_PI / 2) * sin(elevationAngle / 180 * M_TWO_PI / 2);

	point.z = r * cos(elevationAngle / 180 * M_TWO_PI / 2);

	float theta = ofRandom(0, TWO_PI);
	point.x = r * cos(azimuthAngle / 180 * M_TWO_PI / 2) * sin(elevationAngle / 180 * M_TWO_PI / 2);

	point.y = r * sin(azimuthAngle / 180 * M_TWO_PI / 2) * sin(elevationAngle / 180 * M_TWO_PI / 2);

	point.z = r * cos(elevationAngle / 180 * M_TWO_PI / 2);

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