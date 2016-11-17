//
//  ofMirror.cpp
//  multiWindowExample
//
//  Created by 諸星智也 on 2016/11/15.
//
//

#include "ofMirror.hpp"

//--------------------------------------------------------------
void ofMirror::setup(){
    ofBackground(255);
    ofSetFrameRate(30);
    ofSetCircleResolution(200);
    
    
    
}

//--------------------------------------------------------------
void ofMirror::update(){
    
}

//--------------------------------------------------------------
void ofMirror::draw(){
    
    
    
    //フラグがたっている間は遅延処理
    if(gui->DrawFlg[gui->R]){
        int index = gui->buffer%(bufferSize/2); //800フレーム前を参照
        gui->fbo[gui->R][index]->draw(0, 0,1125,ofGetHeight());
    }   
    
}
