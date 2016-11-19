//
//  ofMirror.hpp
//  multiWindowExample
//
//  Created by Ë´∏ÊòüÊô∫‰πü on 2016/11/15.
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
    
    int number = 0;
    bool flg = true;//エフェクトの切り替え(巻き戻し->遅延)
    
    ofSoundPlayer beatsound;
    
    
    
};

#endif /* ofMirror_hpp */
