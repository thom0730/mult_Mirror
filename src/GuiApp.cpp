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
    

    //Glitchとエフェクトの準備
  /*  for(int i = 0; i< camNUM;i++){
        for(int j = 0 ; j < bufferSize ; j++){
             fbo[i][j] = new ofFbo();
            //FBOの準備
            fbo[i][j]->allocate(camWidth, camHeight, GL_RGB);
            myGlitch[i][j].setup(fbo[i][j]);
        }
    }*/
    for(int cam = 0; cam< camNUM; cam++){
        
        // get capture size
        capW[cam] = vidGrabber[cam].getWidth();
        capH[cam] = vidGrabber[cam].getHeight();
        capBytes[cam] = capW[cam] * capH[cam] * 3;
        
        // Create capture buffer
        videoBuf[cam] = (unsigned char *) malloc ( capBytes[cam] * BufferSize );
        
        // Create FBO & Glitch & Tex
        oneFbo[cam] = new ofFbo();
        oneFbo[cam]->allocate(camWidth, camHeight, GL_RGB);
        oneGlitch[cam].setup(oneFbo[cam]);
        oneTex[cam].allocate(capW[cam], capH[cam], GL_RGB);
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
    
    //映像演出のスタート
    if(key == 'z'){
        startL = true;
        startR = true;
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
    
    ////////////////デバッグ////////////////
    if(key == 'm'){
        blackFlg = true;
        center = ofGetHeight();

    }
    /////////////////////////////////////
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
    if(blackFlg){
        ofSetColor(0);
        center = center -2;
        ofDrawCircle(ofGetWidth()/2, center, ofGetWidth());
    }
}
//--------------------------------------------------------------
void GuiApp::Memory(int camera){
    int index = buffer%BufferSize ;

    // Store to pixel buffer
    unsigned char* src = vidGrabber[camera].getPixels().getData();
    int pos = index * capBytes[camera];
    unsigned char* dst = videoBuf[camera] + pos;
    memcpy( dst, src, capBytes[camera] );
    

    
    
}
void GuiApp::UpdateFBO(int camera, int index)
{
    oneFbo[camera]->begin();
    
    // mem to texture
    int pos = index * capBytes[camera];
    oneTex[camera].loadData( videoBuf[camera]+pos, capW[camera], capH[camera], GL_RGB);
    oneTex[camera].draw( 0, 0);
    
    oneFbo[camera]->end();
    
}
void GuiApp::DrawFBO(int camera, int index){
        
    oneGlitch[camera].setFx(OFXPOSTGLITCH_CONVERGENCE,convergence);
    oneGlitch[camera].setFx(OFXPOSTGLITCH_SHAKER	, shaker);
    oneGlitch[camera].setFx(OFXPOSTGLITCH_CUTSLIDER	, cutslider);
    oneGlitch[camera].setFx(OFXPOSTGLITCH_NOISE	, noise);
    oneGlitch[camera].setFx(OFXPOSTGLITCH_SLITSCAN	, slitscan);
    oneGlitch[camera].setFx(OFXPOSTGLITCH_SWELL	, swell);
    oneGlitch[camera].setFx(OFXPOSTGLITCH_CR_BLUERAISE	, blueraise);
    
    oneGlitch[camera].generateFx();
    
    //FBOの描画
   oneFbo[camera]->draw(-oneFbo[camera]->getWidth()/2, 0,1125,ofGetHeight());
}
//--------------------------------------------------------------
void GuiApp::effectSwitch(){
    int i = ofRandom(600);
    cout << "ランダム   " << i << endl;
     //グリッチの切り替え
    if(i == 1){
        if(convergence){
            convergence = false;
        }else
        convergence = true;
        
    }
    if(i == 2){
        if(shaker){
            shaker = false;
        }else
        shaker = true;
        
        
    }
    if(i == 3){
        if(cutslider){
            cutslider = false;
        }else
        cutslider = true;
        
    }
    if(i == 4){
        if(noise){
            noise = false;
        }else
        noise = true;
       
    }
    if(i == 5){
        if(slitscan){
            slitscan = false;
        }else
        slitscan = true;
       
        
    }
    if(i == 6 || i == 16){
        if(swell){
            swell = false;
        }else
        swell = true;
        
        
    }
   /* if(i == 7){
        if(blueraise){
            blueraise = false;
        }else
        blueraise = true;
        
        
    }*/
    
    //投影カメラの切り替え
    if(i == 8 || i == 19){
        if(L == 0){
            L = 1;
        }else{
            L = 0;
        }
    }
    
    if(i == 9){
        if(R == 0){
            R = 1;
        }else{
            R = 0;
        }
        
    }

    
}
