#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include <stdlib.h>
#include <math.h>

#include <android/bitmap.h>
#include <OpenNI.h>
#include <android/log.h>

using namespace openni;

#define  LOG_TAG    "OPENNI"

class ofApp : public ofBaseApp{
	Device device;
	openni::VideoStream			depthStream, colorStream;
	openni::VideoStream**		streams;
    openni::VideoMode colorVideoMode, depthVideoMode;

public:
	void setup();
	void update();
	void draw();

	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	ofEasyCam cam;
	ofMesh mesh;
};

