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
    ofBackground(0);
    ofSetFrameRate(30);
    ofSetCircleResolution(200);
    
    
    
}

//--------------------------------------------------------------
void ofMirror::update(){
    
}

//--------------------------------------------------------------
void ofMirror::draw(){
    ofBackground(0);
    
    
    //フラグがたっている間は遅延処理
    if(gui->DrawFlg[gui->R]){
        int buf = gui->buffer%bufferSize;//0~1799
        
        
        if(buf<(bufferSize/2)){
            index = bufferSize+(buf-bufferSize/2); //バッファサイズで補正
        }else{
            index = buf-(bufferSize/2);//単純に任意のフレーム前
        }
        
        //FBOの描画全般
        gui->DrawFBO(gui->R,index);
        
        counter ++;//描画の開始からインクリメント
        
        if(counter == bufferSize){//バッファサイズまで再生が完了したら
            gui->DrawFlg[gui->R] = false;
            counter = 0;
        }

    }   
    
}
