#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxPostGlitch.h"

//カメラの台数
#define camNUM 2
//30fps*30s=900
#define bufferSize 900

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
    
    //メモリ管理の配列
    void Memory(int camera);
    int buffer = 0;
    
    ofVideoGrabber vidGrabber[camNUM];
    ofVideoGrabber check;//カメラのIDの確認用
    int camWidth , camHeight;//動画の描画の縦横の長さ
    ofFbo* fbo[camNUM][bufferSize];//それぞれの動画のFBOを定義
    
    bool RecFlg[camNUM];
    bool DrawFlg[camNUM];
    int counter[camNUM];
    
    //グリッチのインスタンス
    ofxPostGlitch myGlitch[camNUM][bufferSize];
    
    //カメラの左右の切り替え
    int L = 0;
    int R = 1;
    
    //画面エフェクト
    void Black();
};

