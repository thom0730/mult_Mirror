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
    
    beatsound.load("heartbeat.mp3");
    
    
}

//--------------------------------------------------------------
void ofMirror::update(){
    gui->UpdateFBO(gui->R,index);
    
    if(counter == 3*BufferSize/4){
        beatsound.play();
    }
}

//--------------------------------------------------------------
void ofMirror::draw(){
    ofBackground(0);
    ofSetColor(255);
    
    
    //------------現在------------------
    if(gui->startR){
        gui->vidGrabber[gui->R].draw(0,0,1125,ofGetHeight());
        startCount++;
        if(startCount>BufferSize/4){//だいたいこんなもん?
            gui->startR = false;//「0.現在」を抜ける
            gui->DrawFlg[gui->R] = true;//イントロの開始
            startCount = 0; //エフェクトスタートのトリガーのリセット
        }
    }

    //---------0.イントロ(準備)---------
    if(gui->DrawFlg[gui->R]){
      
        int buf = gui->buffer%BufferSize;//バッファサイズを置換0~1799
        
        if(buf<(BufferSize/2)){//格納バッファの半分前
            index = BufferSize+(buf-BufferSize/2); //バッファサイズで補正
        }else{
            index = buf-(BufferSize/2);//単純に任意のフレーム前
        }
        //------------1.巻き戻し----------------
        //巻き戻し再生の開始
        if(flg){
            index += (BufferSize/2)-number;
            if(index >= BufferSize){//バッファの大きさ以上になってしまったら
                index = index - BufferSize;
            }
            number += 5;
            if(number >= (BufferSize/2)){//戻したい過去まで巻き戻したら
                flg = false;
                
            }
        }
        //------------2.描画/エフェクト----------------
        //FBOの描画全般
        gui->DrawFBO(gui->R,index);
        
        gui->Black();
        
        if(!flg){
            counter ++;//巻き戻し終了->描画の開始からインクリメント
        }
        
        
        //-----------3.アウトロ(レイヤーが重なっていく)------------
        if(counter > 3*BufferSize/4){
            ofSetColor(0, 0, 0, counter%(3*BufferSize/4));
            ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
            
            //現在の映像を流し始める
            ofSetColor(255,255, 255, counter%(3*BufferSize/4));
            gui->vidGrabber[gui->R].draw(0,0,1125,ofGetHeight());
        }
        
        //-------------終了処理--------------
        if(counter == BufferSize){//バッファサイズまで再生が完了したら
            gui->DrawFlg[gui->R] = false;
            counter = 0;
            flg = true;
            number = 0;
            beatsound.stop();
        }
    }
}
