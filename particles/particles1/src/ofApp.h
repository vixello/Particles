#pragma once

#include "ofMain.h"
#include "Particle.h"
#include "HeartFirework.h"
#include "Sphere.h"
#include "Fire.h"
#include "ParticleParameters.h"
#include "ofxGui.h"
#include<math.h>
#include<vector>
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void updateParam();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		template<class P>
		void DrawParitcles(std::vector<P>& par);
		template<class T>
		void WhichParticle(ofMesh& mesh, int rInterval, float& refresh,float& parPerSecond,float & parCount, float& timeDT,std::vector<T> &par, int types);
		template<class G>
		void collision(std::vector<G>& par,float dt);
		void toMesh();
		template <class M>
		void updateMesh(ofMesh& mesh,std::vector<M>& par);
		ofMesh mesh;
		ofMesh mesh2;
		vector<Particle> par;
		vector<HeartFirework> parH;
		vector<Fire> parF;
		vector<Fire> parFF;
		vector<ofMeshFace> meshv;

		Sphere spher;

		ofFbo bft;  //buffer for trails
		float history;
		float timeDt;
		float parPerSecond; //particles that should be born in one second.
		float parCount; //particles to be born
		float a ;
		float amount = 100;
		int frameCount;
		int rInterval; 
		ofEasyCam cam;
		ofLight light;

		ofTexture fireball;
		ofxPanel gui;
		ofxButton forceWorking;
		ofxButton run;
		ofxButton sphere;
		ofxButton Heartshape;
		ofxButton NormalShape;

		ofxIntField force;
		ofxIntField spinning; 
		ofxIntSlider rotate;
		ofxIntSlider velLimit;
		ofxIntSlider friction;
		ofxIntSlider emitterRad;
		ofxIntSlider forceRad;

};
