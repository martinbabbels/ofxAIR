#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	// Setup OF
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
	
	// Setup ofxAIR
	air.addListener(this); // Add the event listener
	air.start(); // Start
	
	// Load image
	mousePointer.loadImage("mouse_pointer.gif");
	
	// Setup mouse position
	mouseX = 0;
	mouseY = 0;
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(255, 255, 255);
	ofSetColor(255, 255, 255);
	
	// Draw the mouse pointer image
	mousePointer.draw(mouseX, mouseY);
	
	ofSetColor(0, 0, 0);
	
	MousePos p;
	p.x = 0;
	p.y = 0;
	
	ofEnableSmoothing();
	
	for(int i=0; i<mouseHistory.size(); i++) {
		ofLine(p.x, p.y, mouseHistory[i].x, mouseHistory[i].y);
		p = mouseHistory[i];
	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key=='d') {
		mouseHistory.clear();
		Json::Value params;
		params["type"] = "Clear";
		air.send(params);
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
	
	if(x>ofGetWidth() || x<0)
		return;
	
	if(y>ofGetHeight() || y<0)
		return;
	
	storeMousePos(mouseX, mouseY);
	
	mouseX = x;
	mouseY = y;
	
	Json::Value params;
	
	params["type"] = "MousePos";
	params["x"] = x;
	params["y"] = y;

	air.send(params);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

void testApp::storeMousePos(int x, int y) {
	MousePos p;
	p.x = mouseX;
	p.y = mouseY;
	
	mouseHistory.push_back(p);
}

// ofxAIR event callback
void testApp::onAIREvent(AIREvent &e) {
	storeMousePos(mouseX, mouseY);
	
	mouseX = e.message["x"].asInt();
	mouseY = e.message["y"].asInt();

	
}

