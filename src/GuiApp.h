#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxPostGlitch.h"

//カメラの台数
#define camNUM 2
//30fps*30s=900
#define BufferSize 2000
//エフェクトの数
#define effectNUM 8

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
    bool startL = false;
    bool startR = false;
    
    //格納の経過をカウンター。実際はこれをBufferSizeで割ったあまりを用いる。
    int buffer = 0;
    bool DrawFlg[camNUM];
    void DrawFBO(int LorR,int i);
    void UpdateFBO(int camera, int index);
    
    ofVideoGrabber vidGrabber[camNUM];
    ofVideoGrabber check;//カメラのIDの確認用
    int camWidth , camHeight;//動画の描画の縦横の長さ
    //ofFbo* fbo[camNUM][bufferSize];//それぞれの動画のFBOを定義
    
    int capW[camNUM];
    int capH[camNUM];
    int capBytes[camNUM];
    ofTexture oneTex[camNUM];
    ofFbo* oneFbo[camNUM];
    unsigned char* videoBuf[camNUM];
    
    
    //グリッチのインスタンス
   // ofxPostGlitch myGlitch[camNUM][bufferSize];
    ofxPostGlitch oneGlitch[camNUM];
    bool shader[effectNUM] ;
   
    
    
    //カメラの左右の切り替え
    int L = 0;
    int R = 1;
    
    
    //とりあえずランダムのエフェクトを生成
    void effectControl(int counter,bool _flg);
    int effectFlg[effectNUM];
    
    //フェードアウトの変数
    float outTime = 0;
    
   
};

