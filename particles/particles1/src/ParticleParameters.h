#pragma once
#include "ofMain.h"

class ParticleParameters
{
public:
	void setup();
	ofPoint emitterCenter;
	
	float refresh;
	float lifetimeSec;
	float emitterRadius;
	float forceRadius;
	float velLimit; //velocity limit
	float rotateS; ///Direction rotation speed in angles per second
	float force;
	float spinningForce;
	float friction;
	float parPerSecond;
	float parCount;
	float timeDT;
	bool run;
	bool forceWorking;

};

//Declaration of a global variable 
extern ParticleParameters param; //base
extern ParticleParameters param2; //Heart
extern ParticleParameters paramFire; //Fire
extern ParticleParameters paramFire2; //Fire
extern ParticleParameters paramSphere; //
