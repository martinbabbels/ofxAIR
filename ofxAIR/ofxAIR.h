#ifndef _OFX_AIR_H_
#define _OFX_AIR_H_


#include "ofMain.h"
#include "ofxThread.h"
#include "json.h"
#include "Poco/BasicEvent.h"
#include "Poco/Delegate.h"

#define BUFFER_SIZE 8192


class ofxAIRListener;
class ofxAIREventManager;

struct AIREvent {
	AIREvent(Json::Value &mes) {
		message = mes;
	};
	Json::Value message;
};

class ofxAIREventListener {

public:
	virtual void onAIREvent(AIREvent &message){
	};
	void onAIREvent(const void * sender, AIREvent &response) {
		onAIREvent(response);
	}
	
};

class ofxAIR : public ofxThread {
	
public:
	
	ofxAIR();
	~ofxAIR();
	
	void threadedFunction();
	void start();
	void stop();
	void send(Json::Value json);
	
	void addListener(ofxAIREventListener *listener);
	void removeListener(ofxAIREventListener *listener);

private:
	
	char						buffer[BUFFER_SIZE];
	Json::Reader				reader;
	
	Poco::BasicEvent<AIREvent>  messageEvent;
	ofxAIR *					sender;
	
	void dispatchEvent(AIREvent message);
	void strip(char *s);
};

#endif
