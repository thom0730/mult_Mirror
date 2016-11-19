//
//  ofMirror.hpp
//  multiWindowExample
//
//  Created by 諸星智也 on 2016/11/15.
//
//

#ifndef ofMirror_hpp
#define ofMirror_hpp

#include "ofMain.h"
#include "ofxGui.h"
#include "GuiApp.h"

class ofMirror: public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    
    shared_ptr<GuiApp> gui;
    
    int counter = 0;
    int index = 0;

};

#endif /* ofMirror_hpp */
