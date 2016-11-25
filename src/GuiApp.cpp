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
    for(int i = 0; i< effectNUM ; i ++){
        shader[i]=false;
        
    }
    //エフェクト生成のフラグの初期化
    for(int i = 0 ; i <effectNUM ;i++){
        effectFlg[i]=0;
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
    
    //いかデバッグ用
    //描画の開始
    if(key == '1'){
        DrawFlg[0] = true ;
       
    }
    if(key == '2'){
        DrawFlg[1] = true ;
    }
    
    //グリッチの切り替え
    if(key == 'q'){
        shader[0] = true;
        
    }
    if(key == 'w'){
        shader[1] = true;
       
    }
    if(key == 'e'){
        shader[2] = true;
        
    }
    if(key == 'r'){
        shader[3] = true;
        
    }
    if(key == 't'){
        shader[4] = true;
       
    }
    if(key == 'y'){
        shader[5] = true;
        
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
    
    ////////////////黒系のエフェクト////////////////
    if(key == 'm'){
        blackFlg = true;
       // center = ofGetHeight();

    }
    if(key == 'n'){
        blackCircle = true;
    }
    /////////////////////////////////////
}

//--------------------------------------------------------------
void GuiApp::keyReleased(int key){
    //グリッチの切り替え
    if(key == 'q'){
        shader[0] = false;
        
    }
    if(key == 'w'){
        shader[1] = false;
        
    }
    if(key == 'e'){
        shader[2] = false;
        
    }
    if(key == 'r'){
        shader[3] = false;
        
    }
    if(key == 't'){
        shader[4] = false;
        
    }
    if(key == 'y'){
        shader[5] = false;
        
    }
    
}

//--------------------------------------------------------------
void GuiApp::Black(){
    ofSetColor(0);
    BlackStart = BlackStart -1;
    ofDrawCircle(ofGetWidth()/2, BlackStart, ofGetWidth());

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
        
    oneGlitch[camera].setFx(OFXPOSTGLITCH_CONVERGENCE,shader[0]);
    oneGlitch[camera].setFx(OFXPOSTGLITCH_SHAKER	, shader[1]);
    oneGlitch[camera].setFx(OFXPOSTGLITCH_CUTSLIDER	, shader[2]);
    oneGlitch[camera].setFx(OFXPOSTGLITCH_NOISE	, shader[3]);
    oneGlitch[camera].setFx(OFXPOSTGLITCH_SLITSCAN	, shader[4]);
    oneGlitch[camera].setFx(OFXPOSTGLITCH_SWELL	, shader[5]);
    //Glitchの追加
    oneGlitch[camera].generateFx();
    
    //FBOの描画
   oneFbo[camera]->draw(-oneFbo[camera]->getWidth()/2, 0,1125,ofGetHeight());
}
//--------------------------------------------------------------
void GuiApp::effectControl(int counter,bool _flg){
    int i = ofRandom(900);
   
     //グリッチの切り替え
   /* if(i == 1){
        if(!shader[0]){
            shader[0] = true;
        }
    }*/
    if(i == 2){
        if(!shader[1]){
            shader[1] = true;
        }
    }
    if(i == 3){
        if(!shader[2]){
            shader[2] = true;
        }
    }
    if(i == 4){
        if(!shader[3]){
            shader[3] = true;
        }
    }
    if(i == 5){
        if(!shader[4]){
            shader[4] = true;
        }
    }
   /* if(i == 6){
        if(!shader[5]){
            shader[5] = true;
            
        }
    }*/

    //投影カメラの切り替え
    if(_flg){
        if(i==5){
            shader[i] =true;//カメラ反転の開始のフラグ
            if(L == 0){
                L = 1;
                R = 0;
            }else{
                L = 0;
                R = 1;
                
            }
            
            
        }
    }

    for(int i =0 ; i < effectNUM; i++){
        if(shader[i]){
            effectFlg[i]++;
        }
        if(i != 5){
            if(effectFlg[i]  == 20 ){//20フレーム後にOFF
                shader[i] = false;
                effectFlg[i] = 0;
            }
        }else{
            if(effectFlg[i] == 60){
                L = 0;
                R = 1;
                shader[i] = false;
            }
                
        }
    }
    
}
