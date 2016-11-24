#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxPostGlitch.h"

//カメラの台数
#define camNUM 2
//30fps*30s=900
#define BufferSize 3000
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
    
    //画面エフェクト
    void Black();
    bool blackFlg = false;
    bool blackCircle = false;//日の出エフェクトの中心位置
    int BlackStart = ofGetHeight()+ofGetWidth(); //日の出エフェクトのy座標の初期位置
    int circleRadius = 0; //中心から広がる円の半径
    
    //とりあえずランダムのエフェクトを生成
    void effectControl(int counter);
    int effectFlg[effectNUM];
    
   
};

