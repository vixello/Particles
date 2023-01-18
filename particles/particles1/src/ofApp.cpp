#include "ofApp.h"
#include<math.h>
#include<vector>
//--------------------------------------------------------------
void ofApp::setup() {
	gui.setup();
	gui.add(rotate.setup("rotate", 0, 0, 720));
	gui.add(force.setup("force", -1000, -2000, 2000));
	gui.add(spinning.setup("spinning", 1000, -1000, 1000));
	gui.add(velLimit.setup("velLimit", 100, 0, 1000));
	gui.add(emitterRad.setup("emitterRad", 100, -100, 1000));
	gui.add(forceRad.setup("forceRad", 1000, -100, 10000));
	gui.add(forceWorking.setup("forceWorking"));
	gui.add(run.setup("run"));
	gui.add(sphere.setup("sphere"));

	ofSetFrameRate(60);
	ofEnableLighting();
	cam.setPosition(522.272, 370.552, 801.519);
	light.setPosition(0, -600, 300);

	frameCount = 0;
	rInterval = 15;
	a = 0.0;
	param2.parPerSecond = 200;
	param2.parCount = 0;
	param2.setup();

	paramFire.setup();
	paramFire2.setup();
	param.setup();
	paramSphere.setup();
	spher.setup();
	float histor = 0.995;
	ofDisableArbTex();
	//ofLoadImage(fireball, "lightball44.png");
	timeDt = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update() {
	WhichParticle(mesh,ofRandom(20, 25),param.refresh, param.parPerSecond, param.parCount, param.timeDT, par, 0);
	//WhichParticle(param2.refresh, param2.parPerSecond, param2.parCount, param2.timeDT, parH, 1);

	updateMesh(mesh,par);
	//updateMesh(parH);

	//WhichParticle(mesh2,100,paramFire.refresh, paramFire.parPerSecond, paramFire.parCount, paramFire.timeDT, parF, 11);
	//WhichParticle(mesh2,100,paramFire2.refresh, paramFire2.parPerSecond, paramFire2.parCount, paramFire2.timeDT, parFF, 12);
	
	//updateMesh(mesh2,parF);
	//updateMesh(mesh2,parFF);

}
void ofApp::updateParam()
{
	//acceleratoin for collision
	a += 0.1;
	float r = ofRandom(180, emitterRad);

	//rInterval = ofRandom(20, 25);

	//parameters

	//base
	param.force = force;
	param.refresh = 1000;
	param.rotateS = rotate;
	param.velLimit = velLimit;
	param.spinningForce = spinning;
	param.emitterRadius = emitterRad;
	param.forceRadius = forceRad;
	param.forceWorking = forceWorking;
	param.run = run;
	param.parPerSecond = 200;

	paramFire.force = force;
	paramFire.refresh = 200;
	paramFire.rotateS = rotate;
	paramFire.velLimit = velLimit;
	paramFire.spinningForce = spinning;
	paramFire.emitterRadius = emitterRad;
	paramFire.forceRadius = forceRad;
	paramFire.forceWorking = forceWorking;
	paramFire.run = run;
	paramFire.parPerSecond = 300;

	paramFire2.force = force;
	paramFire2.refresh = 18;
	paramFire2.rotateS = rotate;
	paramFire2.velLimit = velLimit;
	paramFire2.spinningForce = spinning;
	paramFire2.emitterRadius = emitterRad;
	paramFire2.forceRadius = forceRad;
	paramFire2.forceWorking = forceWorking;
	paramFire2.run = run;
	paramFire2.parPerSecond = 300;

	//heart
	param2.force = force;
	param2.rotateS = rotate;
	param2.velLimit = velLimit;
	param2.spinningForce = spinning;
	param2.emitterRadius = emitterRad;
	param2.forceRadius = forceRad;
	param2.forceWorking = forceWorking;
	param2.run = run;
	param2.parPerSecond = 200;
	param2.refresh = param2.parPerSecond;

	paramSphere.force = force;
	paramSphere.refresh = 20;
	paramSphere.rotateS = rotate;
	paramSphere.velLimit = velLimit;
	paramSphere.spinningForce = spinning;
	paramSphere.emitterRadius = emitterRad;
	paramSphere.forceRadius = forceRad;
	paramSphere.forceWorking = forceWorking;
	paramSphere.run = run;
}
template <class P>

void ofApp::DrawParitcles(std::vector<P>& par)
{
	for (int i = 0; i < par.size(); i++) {
		par[i].draw();
	}
}
template <class T>
void ofApp::WhichParticle(ofMesh& mesh,int rInterval,float& refresh, float& parPerSecond, float& parCount, float& timeDt, std::vector<T>& par, int types)
{
	//activate a particle if it is not alive
	//updates the particle state
	float time = ofGetElapsedTimef();
	//limiting dt value by 0.x
	float dt = ofClamp(time - timeDt, 0, 0.2);
	timeDt = time;

	int i = 0;
	if (frameCount % rInterval == 0)
	{
		mesh.clear();
	}

	while (i < par.size())
	{
		if (!par[i].isAlive)
		{
			par.erase(par.begin() + i);
		}

		else
		{
			i++;
		}
	}

	//new particles
	parCount += parPerSecond * dt;

	if (parCount >= refresh)
	{
		int howManyAlive = int(parCount);
		parCount -= howManyAlive;
		for (int i = 0; i < howManyAlive; i++)
		{
			//modes push x type of particle
		   //Particle newparticle;

			T newparticle1;
			switch (types) {
			case 0:
				newparticle1.emitterCenter = ofVec3f(ofGetWidth() / 2 + 600, ofGetHeight() / 2 , 0);
				break;
			case 11:
				newparticle1.emitterCenter = ofVec3f(ofGetWidth() / 2 + 100, ofGetHeight() / 2 + 20, 0);
				newparticle1.lifeTime = 7.6;
				newparticle1.radius = 3;
				break;
			case 12:
				newparticle1.emitterCenter = ofVec3f(ofGetWidth() / 2 + 170, ofGetHeight() / 2, 30);
				newparticle1.lifeTime = 5.6;
				newparticle1.radius = 2;

				break;
			}
			newparticle1.setup();

			par.push_back(newparticle1);
		}
	}

	for (int i = 0; i < par.size(); i++)
	{
		par[i].update(dt);
	}
	collision(par, dt);
	spher.update(dt);
}
template<class G>
void ofApp::collision(std::vector<G>& par, float dt)
{
	ofVec3f vecd;
	ofVec3f x, v1, v1x, v1y, v2, v2x, v2y;
	float distance, x1, x2, m1, m2;
	float radiusSum;
	ofVec3f a;
	ofVec3f delta;

	for (int i = 0; i < par.size(); i++)
	{
		//based on simple sphere collision article
		vecd = par[i].pos - spher.pos;
		distance = vecd.length();
		radiusSum = par[i].radius + spher.radius;
		if (distance <= radiusSum)
		{
			x = vecd.normalize();
			v1 = par[i].vel;
			x1 = x.dot(v1);
			v1x = x * x1;
			v1y = v1 - v1x;
			m1 = 100;

			x = x * -1;
			v2 = spher.vel;
			x2 = x.dot(v2);
			v2x = x * x2;
			v2y = v2 - v2x;
			m2 = 0;

			//par[i].vel = ofVec3f(v1x * (m1 - m2) / (m1 + m2) + v2x * (2 * m2) / (m1 + m2) + v1y);
			if (forceWorking)
			{
				delta = (par[i].pos - par[i].emitterCenter);
				a += delta * param.force;
				a.x += -delta.y * param2.spinningForce;
				a.y += delta.z * param2.spinningForce;
				a.z += delta.x * param2.spinningForce;

				par[i].vel = ofVec3f(v1x * (2 * m1) / (m1 + m2) + v2x * (m2 - m1) / (m1 + m2) + v2y) + a * dt;
				par[i].vel *= -(1 - param.friction * 10);
			}
			else
			{
				par[i].vel = ofVec3f(v1x * (2 * m1) / (m1 + m2) + v2x * (m2 - m1) / (m1 + m2) + v2y);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofSetColor(0, 0, 0, 100);
	if (frameCount % (rInterval * 100) == 0) {
		ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
	}
	ofDisableAlphaBlending();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofEnableBlendMode(OF_BLENDMODE_SCREEN);

	cam.begin();
	ofEnableDepthTest();
	ofEnableLighting();

	updateParam();

	ofRotateDeg(0, 10, 0, 1);
	light.enable();

	if (!parH.empty())
	{
		DrawParitcles(parH);
	}
	if (!par.empty())
	{
		fireball.bind();
		DrawParitcles(par);
		fireball.unbind();
		mesh.draw();
	}
	if (!parF.empty())
	{
		fireball.bind();
		DrawParitcles(parF);
		fireball.unbind();
		mesh2.draw();
	}
	if (!parFF.empty())
	{
		fireball.bind();
		DrawParitcles(parFF);
		fireball.unbind();
		mesh2.draw();
	}

	if (sphere) {
		spher.draw();
	}

	ofDisableLighting();
	ofDisableDepthTest();
	light.disable();
	cam.end();
	gui.draw();
	ofEnableLighting();
	frameCount++;
}

void ofApp::toMesh() {
	//for (auto i = 0; i < 300; i++) {
	//	for (auto j = 0; j < 300; j++) {
	//		mesh.addVertex(ofPoint(i - 300 / 2, i - 300 , j - 300 / 2));
	//		mesh.addColor(ofColor::forestGreen);
	//		mesh.addColor(ofColor::darkGreen);
	//		mesh.addColor(ofColor::forestGreen);
	//		mesh.addColor(ofColor::darkGreen);
	//		mesh.addColor(ofColor::darkGreen);

	//	}
	//}
	//for (auto i = 0; i < 298; i++) {
	//	for (auto j = 0; j < 298; j++) {
	//		mesh.addIndex(i + j * 300);
	//		mesh.addIndex((i+2) + j * 300);
	//		mesh.addIndex(i + (j+2) * 300);
	//		mesh.addIndex((i + 2) + (j + 2) * 300);
	//		mesh.addIndex(i + (j + 2) * 300);

	//	}
	//}

	//update
	//int count = 0;
	//for (auto i = 0u; i < par.size(); i++)
	//	{
	//
	//			ofVec3f position = mesh.getVertex(count);
	//			position.y = ofMap(ofNoise(count, ofGetElapsedTimef()), 1, 0 ,0, 5);
	//			mesh.setVertex(count, position);
	//			count++;

	//}
}

template <class M>
void ofApp::updateMesh(ofMesh & mesh,std::vector<M>& par)
{
	mesh.setMode(OF_PRIMITIVE_POINTS);
	glPointSize(4);
	for (auto i = 0u; i < par.size(); i++) {
		mesh.addVertex(par[i].pos);
		//mesh.addIndex(i);
		mesh.addColor(par[i].color);
	}

}
//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
}