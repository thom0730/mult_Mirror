#include "ofMain.h"
#include "ofApp.h"
#include "GuiApp.h"
#include "ofMirror.hpp"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
	ofGLFWWindowSettings settings;

	settings.width = 600;
	settings.height = 900;
	settings.setPosition(ofVec2f(300,0));
	settings.resizable = true;
	shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);

	settings.width = 600;
	settings.height = 600;
	settings.setPosition(ofVec2f(0,0));
	settings.resizable = false;
    settings.shareContextWith = mainWindow;
	shared_ptr<ofAppBaseWindow> guiWindow = ofCreateWindow(settings);
    
    settings.width = 600;
    settings.height = 900;
    settings.setPosition(ofVec2f(600,0));
    settings.resizable = false;
    shared_ptr<ofAppBaseWindow> mirrorWindow = ofCreateWindow(settings);

	shared_ptr<ofApp> mainApp(new ofApp);
	shared_ptr<GuiApp> guiApp(new GuiApp);
    shared_ptr<ofMirror> mirrorApp(new ofMirror);
	mainApp->gui = guiApp;

	ofRunApp(guiWindow, guiApp);
    ofRunApp(mirrorWindow, mirrorApp);
	ofRunApp(mainWindow, mainApp);
	ofRunMainLoop();

}
