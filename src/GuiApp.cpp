/*
 * GuiApp.cpp
 *
 *  Created on: Oct 28, 2014
 *      Author: arturo
 */

#include "GuiApp.h"
//--------------------------------------------------------------
void GuiApp::setup(){
    //GUI関係
	/*parameters.setName("parameters");
	parameters.add(radius.set("radius",50,1,100));
	parameters.add(color.set("color",100,ofColor(0,0),255));
	gui.setup(parameters);
	ofBackground(0);
	ofSetVerticalSync(false);*/
    
    ofBackground(0, 0, 0);
    ofSetFrameRate(30);
    
    ofEnableSmoothing();
    //画面の混色の設定を加算合成にする
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    
    //キャプチャするムービーのサイズを指定
    camWidth = ofGetWidth();
    camHeight = ofGetHeight()/2;
    
    
    for(int i = 0 ; i < camNUM; i++){
        vidGrabber[i].setVerbose(true);//カメラの準備
        DrawFlg[i] = false;//フラグの初期化

    }
    
    //カメラのIDは直接入力が良さそう
     vidGrabber[0].setDeviceID(0);
     vidGrabber[0].initGrabber(camWidth, camHeight);
     vidGrabber[1].setDeviceID(2);
     vidGrabber[1].initGrabber(camWidth, camHeight);
    
    
    
    //カメラの接続確認
    ofSetLogLevel(OF_LOG_VERBOSE);
    check.setVerbose(true);
    check.listDevices();
    

    
    for(int i = 0; i< camNUM;i++){
        for(int j = 0 ; j < bufferSize ; j++){
             fbo[i][j] = new ofFbo();
            //FBOの準備
            fbo[i][j]->allocate(camWidth, camHeight, GL_RGB);
            myGlitch[i][j].setup(fbo[i][j]);
        }
    }
}
//--------------------------------------------------------------
void GuiApp::update(){
    for(int i = 0 ; i < camNUM; i++){
        vidGrabber[i].update();
    }
    
    //バッファに常に書き込む
    for(int i = 0 ; i < camNUM;i++){
        Memory(i);
    }
    buffer ++;

    
}
//--------------------------------------------------------------
void GuiApp::draw(){
    //GUIの描画
    gui.draw();
    
    //カメラ映像の描画
    for(int i = 0 ; i < camNUM; i++){
        vidGrabber[i].draw(0,i*camHeight);
    }
    
}
//--------------------------------------------------------------
void GuiApp::keyPressed(int key){
    
    //描画の開始
    if(key == '1'){
        DrawFlg[0] = true ;
       
    }
    if(key == '2'){
        DrawFlg[1] = true ;
    }
    
    //グリッチの切り替え
    if(key == 'q'){
        convergence = true;
        
    }
    if(key == 'w'){
        shaker = true;
       
    }
    if(key == 'e'){
        cutslider = true;
        
    }
    if(key == 'r'){
        noise = true;
        
    }
    if(key == 't'){
        slitscan = true;
       
    }
    if(key == 'y'){
        swell = true;
        
    }
    if(key == 'u'){
        blueraise = true;
       
    }
    
    //投影カメラの切り替え
    if(key == 'o'){
        if(L == 0){
            L = 1;
        }else{
            L = 0;
        }
    }
    
    if(key == 'p'){
        if(R == 0){
            R = 1;
        }else{
            R = 0;
        }
        
    }
}

//--------------------------------------------------------------
void GuiApp::keyReleased(int key){
    //グリッチの切り替え
    if(key == 'q'){
        convergence = false;
        
    }
    if(key == 'w'){
        shaker = false;
        
    }
    if(key == 'e'){
        cutslider = false;
        
    }
    if(key == 'r'){
        noise = false;
        
    }
    if(key == 't'){
        slitscan = false;
        
    }
    if(key == 'y'){
        swell = false;
        
    }
    if(key == 'u'){
        blueraise = false;
        
    }
    
 
}

//--------------------------------------------------------------
void GuiApp::Black(){
    ofSetColor(0);
    for(int i = 0 ; i < 3 ; i++){
        ofRect(2*i*ofGetWidth()/6, 0,ofGetWidth()/6,ofGetHeight());
    }
}
//--------------------------------------------------------------
void GuiApp::Memory(int camera){
    int index = buffer%bufferSize ;
    //FBOの準備
   // fbo[camera][index]->allocate(camWidth, camHeight, GL_RGB);
    //FBOに書き込む
    fbo[camera][index]->begin();
    vidGrabber[camera].draw(0, 0, fbo[camera][index]->getWidth(), fbo[camera][index]->getHeight());
    fbo[camera][index]->end();
    
    
}
