#include "ofxAIR.h"

/**
 * Constructor
 *
 */
ofxAIR::ofxAIR(){
	sender = this;
}

/**
 * Destructor
 *
 */
ofxAIR::~ofxAIR(){
    stop();
}

/**
 * Start thread
 *
 */
void ofxAIR::start() {
	if (isThreadRunning() == false) {
        startThread(true, false);
    }
}

/**
 * Stop thread
 *
 */
void ofxAIR::stop() {
    stopThread();
}

/**
 * Thread
 *
 */
void ofxAIR::threadedFunction(){
	int cnt;
    if( isThreadRunning() == true ) {
		while (!feof(stdin)) {
			cnt = read(STDIN_FILENO, buffer, sizeof buffer); 
			
			Json::Value mes;
			bool is_parsed = reader.parse(buffer, mes);
			
			if(is_parsed) {
				AIREvent e = AIREvent(mes);	
				dispatchEvent(e);
			}
		}
    }
}

/**
 * Send json string to AIR
 * @param	Json::Value json
 *
 */
void ofxAIR::send(Json::Value json) {
	Json::FastWriter writer;
	
	string ser_json = writer.write(json);
	int size = ser_json.size();
	
	char char_ser_json[size];
	strcpy(char_ser_json, ser_json.c_str());

	write(STDOUT_FILENO, char_ser_json, size);
}

/**
 * Strip line breaks
 * @param	char * s
 *
 */
void ofxAIR::strip(char * s) {
    s[strcspn(s, "\n" )] = '\0';
}

/**
 * Add event listener
 * @param	ofxAIREventListener * listener
 *
 */
void ofxAIR::addListener(ofxAIREventListener * listener) {
	messageEvent += Poco::Delegate<ofxAIREventListener, AIREvent>(listener,&ofxAIREventListener::onAIREvent);
}

/**
 * Remove event listener
 * @param	ofxAIREventListener * listener
 *
 */
void ofxAIR::removeListener(ofxAIREventListener * listener) {
	messageEvent += Poco::Delegate<ofxAIREventListener, AIREvent>(listener,&ofxAIREventListener::onAIREvent);
}

/**
 * Dispatch event
 * @param	AIREvent message
 *
 */
void ofxAIR::dispatchEvent(AIREvent message) {
	messageEvent.notify(sender, message);
}


