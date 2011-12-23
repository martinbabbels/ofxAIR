#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxAIR.h"

typedef struct {
	int x;
	int y;
} MousePos;

class testApp : public ofBaseApp, public ofxAIREventListener {

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
	
private:
		void onAIREvent(AIREvent &e);
		void storeMousePos(int x, int y);
	
		ofxAIR air;
		ofImage mousePointer;
		int	mouseX;
		int mouseY;
		vector<MousePos> mouseHistory;
};

#endif
