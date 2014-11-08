#include "ofApp.h"

	
//--------------------------------------------------------------
void ofApp::setup(){
	openni::OpenNI::initialize();
	ofSetVerticalSync(true);
	
    openni::Status rc = device.open(openni::ANY_DEVICE);
    device.setDepthColorSyncEnabled(true);

    rc = depthStream.create(device, openni::SENSOR_DEPTH);
    rc = depthStream.start();

    rc = colorStream.create(device, openni::SENSOR_COLOR);
    rc = colorStream.start();

    streams = new openni::VideoStream*[2];
    streams[0] = &depthStream;
    streams[1] = &colorStream;

    depthVideoMode = depthStream.getVideoMode();
	colorVideoMode = colorStream.getVideoMode();

	cam.setDistance(0.4f);
}


//--------------------------------------------------------------
void ofApp::update(){
	mesh.clear();
	mesh.setMode(OF_PRIMITIVE_POINTS);

	openni::VideoFrameRef depthFrame, colorFrame;
	colorStream.readFrame( &colorFrame );
	depthStream.readFrame( &depthFrame );

	__android_log_print(ANDROID_LOG_INFO, "OPENNI", "Depth %d, %d", depthFrame.getHeight(), depthFrame.getWidth());
	__android_log_print(ANDROID_LOG_INFO, "OPENNI", "Color %d, %d", colorFrame.getHeight(), colorFrame.getWidth());

	if (depthFrame.isValid() && colorFrame.isValid()) {

		short* pDepthRow = (short *)depthFrame.getData();
		const openni::RGB888Pixel* pImageRow = (const openni::RGB888Pixel*)colorFrame.getData();

		int step = 1;
		for (int y = 0; y < depthFrame.getHeight(); y = y + step) {
			for (int x = 0; x < depthFrame.getWidth(); x = x + step) {
				short z = pDepthRow[y* depthVideoMode.getResolutionX()+x];
				if (z > 0 && z < 1200) {
					ofColor cur(pImageRow[y* depthVideoMode.getResolutionX()+x].r,
							pImageRow[y* depthVideoMode.getResolutionX()+x].g,
							pImageRow[y* depthVideoMode.getResolutionX()+x].b);
					mesh.addColor(cur);
					ofVec3f pos(x, y, -z);
					mesh.addVertex(pos);
				}
			}
		}
	}

	ofEnableDepthTest();
	glEnable(GL_POINT_SMOOTH);
	glPointSize(2);
	__android_log_print(ANDROID_LOG_INFO, "OPENNI", "Particles %d", mesh.getVertices().size());
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackgroundGradient(ofColor::gray, ofColor::black, OF_GRADIENT_CIRCULAR);

	// even points can overlap with each other, let's avoid that
	cam.begin();
	ofScale(0.7, -0.7, 0.7); // flip the y axis and zoom in a bit
//	ofRotateY(90);
	ofTranslate(-depthVideoMode.getResolutionX() / 2, -depthVideoMode.getResolutionY() / 2);
	mesh.draw();
	cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
	
}
