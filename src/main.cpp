#include "ofMain.h"
#include "ofApp.h"
#include "GuiApp.h"
#include "ofMirror.hpp"
#include "ofAppGLFWWindow.h"

#include "config.h"

//========================================================================
int main( ){
//	ofGLFWWindowSettings settings;
    // Read config.xml  --- if not, create.
    // * default values are Config::Config()
    config.load();
    //mirror 1
//	settings.width = 500;
//	settings.height = 750;
//	settings.setPosition(ofVec2f(300,0));
//	settings.resizable = true;
//	shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
	shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(config.mirror1.settings);

    //GUI
//	settings.width = 640;
//	settings.height = 720;
//	settings.setPosition(ofVec2f(0,0));
//	settings.resizable = false;
    settings.shareContextWith = mainWindow;
//	shared_ptr<ofAppBaseWindow> guiWindow = ofCreateWindow(settings);
    shared_ptr<ofAppBaseWindow> guiWindow = ofCreateWindow(config.gui.settings);
    
    //mirror 2
//	settings.width = 500;
//	settings.height = 750;
//	settings.setPosition(ofVec2f(300,0));
//	settings.resizable = true;
//	shared_ptr<ofAppBaseWindow> mirrorWindow = ofCreateWindow(settings);
    shared_ptr<ofAppBaseWindow> mirrorWindow = ofCreateWindow(config.mirror2.settings);
    
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
