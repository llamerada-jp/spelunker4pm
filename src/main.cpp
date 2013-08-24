#include "spelunker_app.h"
#include "ofAppGlutWindow.h"

#include "const.h"

//--------------------------------------------------------------
int main() {
	ofAppGlutWindow window; // create a window
	// set width, height, mode (OF_WINDOW or OF_FULLSCREEN)
	ofSetupOpenGL(&window, SCREEN_W, SCREEN_H, OF_WINDOW);
	ofRunApp(new SpelunkerApp()); // start the app
}
