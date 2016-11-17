#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxPostGlitch.h"

//カメラの台数
#define camNUM 2
//30fps*30s=900
#define bufferSize 400

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
    
    //メモリ管理の関数
    void Memory(int camera);
    //格納の経過をカウンター。実際はこれをBufferSizeで割ったあまりを用いる。
    int buffer = 0;
    bool DrawFlg[camNUM];
    
    ofVideoGrabber vidGrabber[camNUM];
    ofVideoGrabber check;//カメラのIDの確認用
    int camWidth , camHeight;//動画の描画の縦横の長さ
    ofFbo* fbo[camNUM][bufferSize];//それぞれの動画のFBOを定義
    
    
    //グリッチのインスタンス
    ofxPostGlitch myGlitch[camNUM][bufferSize];
    
    //カメラの左右の切り替え
    int L = 0;
    int R = 1;
    
    //画面エフェクト
    void Black();
};

