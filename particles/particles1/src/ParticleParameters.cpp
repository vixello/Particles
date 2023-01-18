#include "ParticleParameters.h"

void ParticleParameters::setup()
{
	rotateS = 90;
	emitterRadius = 300;
	forceRadius = 1000;
	emitterCenter = ofPoint(ofGetWidth() / 2, ofGetHeight() / 2,0);
	velLimit = 50;
	lifetimeSec = 5.0;
	force = -1000;
	spinningForce =1000;
	friction = 0.05;
	parPerSecond = 200;
	parCount = 0;
	timeDT= ofGetElapsedTimef();
	forceWorking = false;
}
