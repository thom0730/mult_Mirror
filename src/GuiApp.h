#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxPostGlitch.h"

//カメラの台数
#define camNUM 2

class GuiApp: public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
    void keyPressed(int key);
    void keyReleased(int key);
   

    //いらない。最終的に消す
	ofParameterGroup parameters;
	ofParameter<float> radius;
	ofParameter<ofColor> color;
	ofxPanel gui;
    
    void FboUpdate(int camera);//FBOの格納
    void FboDraw(int camera);//FBOの描画
    void stop(int number); //描画の停止用関数
    
    ofVideoGrabber vidGrabber[camNUM];
    ofVideoGrabber check;//カメラのIDの確認用
    int camWidth , camHeight;//動画の描画の縦横の長さ
    vector<ofFbo*> fbo[camNUM];//それぞれの動画のFBOを定義
    
    bool RecFlg[camNUM];
    bool DrawFlg[camNUM];
    int counter[camNUM];
    
    //グリッチのインスタンス
    vector<ofxPostGlitch> myGlitch[camNUM];
    
    //カメラの左右の切り替え
    int L = 0;
    int R = 1;
    
    //画面エフェクト
    void Black();
};

