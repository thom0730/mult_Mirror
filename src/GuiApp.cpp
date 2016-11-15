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
        vidGrabber[i].setVerbose(true);
       // vidGrabber[i].setDeviceID(i);
       // vidGrabber[i].initGrabber(camWidth, camHeight);
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
    
    
    //FBOの準備
    for(int i = 0;i<camNUM;i++){
        DrawFlg[i] = false;//フラグの初期化
        RecFlg[i] = false;//フラグの初期化
        counter[i] = 0;
    }
    
}
//--------------------------------------------------------------
void GuiApp::update(){
    for(int i = 0 ; i < camNUM; i++){
        vidGrabber[i].update();
    }
    //FBOへの格納
    for(int i = 0 ; i < camNUM;i++){
        if(RecFlg[i]){
            FboUpdate(i);
            cout << "FBOカクノウ" << endl;
        }
    }
    
}
//--------------------------------------------------------------
void GuiApp::draw(){
    //GUIの描画
    gui.draw();
    
    //カメラ映像の描画
    for(int i = 0 ; i < camNUM; i++){
        vidGrabber[i].draw(0,i*camHeight);
    }
    
    //FBOの描画
    for(int i = 0 ; i < camNUM;i++){
        if(DrawFlg[i]){
            cout << i << endl;
           FboDraw(i);
        }
        
    }

}
//--------------------------------------------------------------
void GuiApp::keyPressed(int key){
    
    //カメラ1
    if (key == 'z' || key == 'Z'){
        RecFlg[0] = true; //録音の開始
    }
    if(key == '1'){
        DrawFlg[0] = true ; //描画の開始
    }
    //カメラ2
    if (key == 'x' || key == 'X'){
        RecFlg[1] = true; //録音の開始
    }
    if(key == '2'){
        DrawFlg[1] = true ; //描画の開始
    }
   
    
    
}

//--------------------------------------------------------------
void GuiApp::keyReleased(int key){
    
    //カメラ(FBO)の処理
    
    //カメラ1
    if (key == 'z' || key == 'Z'){
        RecFlg[0] = false; //録音の停止
    }
    if(key == '1'){
        stop(0);
    }
    //カメラ2
    if (key == 'x' || key == 'X'){
        RecFlg[1] = false; //録音の停止
    }
    if(key == '2'){
        stop(1);
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
    
    
    
    //グリッチ加工の処理
    
}
//--------------------------------------------------------------
void GuiApp::FboUpdate(int camera){
    
    fbo[camera].push_back(new ofFbo);//任意のカメラのFBOにバッファを追加
    int num = fbo[camera].size()-1;
    fbo[camera][num]->allocate(camWidth, camHeight, GL_RGB); //FBOの準備
    //FBOの書き込み
    fbo[camera][num]->begin();
    vidGrabber[camera].draw(0, 0, fbo[camera][num]->getWidth(), fbo[camera][num]->getHeight());
    fbo[camera][num]->end();
    
    
    /*//グリッジ
    myGlitch[camera].push_back(*new ofxPostGlitch);//グリッチ用のインスタンスをカメラ番号の動的配列に格納
    myGlitch[camera][num].setup(fbo[camera][num]);//初期化
    //エフェクトの指定
    myGlitch[camera][num].setFx(OFXPOSTGLITCH_CR_BLUERAISE	, true);*/
    
}
//--------------------------------------------------------------
void GuiApp::stop(int number){
    DrawFlg[number] = false ;
    counter[number] = 0;
    fbo[number].clear();
}
//--------------------------------------------------------------
void GuiApp::FboDraw(int camera){
    int position = camera + 1;//生成位置の指定(最終的には必要ない処理)
    if(counter[camera] < fbo[camera].size()){
    
        fbo[camera][counter[camera]]->draw(position*camWidth,camHeight);
        
        cout << "FBO描画" << endl;
    }else{
        stop(camera);
    }
    
    counter[camera]++;
    
    
    
}
