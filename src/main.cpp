#include "ofMain.h"
#include "ofApp.h"
#include "GuiApp.h"
#include "ofMirror.hpp"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
	ofGLFWWindowSettings settings;

    //mirror 1
	settings.width = 500;
	settings.height = 750;
	settings.setPosition(ofVec2f(300,0));
	settings.resizable = true;
	shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);

    //GUI
	settings.width = 640;
	settings.height = 720;
	settings.setPosition(ofVec2f(0,0));
	settings.resizable = false;
    settings.shareContextWith = mainWindow;
	shared_ptr<ofAppBaseWindow> guiWindow = ofCreateWindow(settings);
    
    //mirror 2
    settings.width = 500;
    settings.height = 750;
    settings.setPosition(ofVec2f(300,0));
    settings.resizable = false;
    shared_ptr<ofAppBaseWindow> mirrorWindow = ofCreateWindow(settings);

	shared_ptr<ofApp> mainApp(new ofApp);
	shared_ptr<GuiApp> guiApp(new GuiApp);
    shared_ptr<ofMirror> mirrorApp(new ofMirror);
	mainApp->gui = guiApp;
    mirrorApp->gui = guiApp;


	ofRunApp(guiWindow, guiApp);
    ofRunApp(mirrorWindow, mirrorApp);
	ofRunApp(mainWindow, mainApp);
	ofRunMainLoop();

}
