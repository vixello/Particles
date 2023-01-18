#pragma once
#include "ofMain.h"

class HeartFirework
{
public:
	HeartFirework(); //Class constructor
	void setup(); //Start particle
	void Forces(float dt);
	void update(float dt); //Recalculate physics
	void draw(); //Draw particle
	ofVec3f randPointInsideCircle(float maxRand);


	ofPoint pos; //Position
	ofPoint vel; //Velocity
	ofVec3f f;
	ofVec3f emitterCenter;
	ofColor color;

	bool isAlive; //Is it live
	float time; //Time of living
	float lifeTime; // lifetime of the particle
	float radius;

};

