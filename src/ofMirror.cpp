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
    
    
    
}

//--------------------------------------------------------------
void ofMirror::update(){
    if(counter == 3*bufferSize/4){
        beatsound.play();
    }
}

//--------------------------------------------------------------
void ofMirror::draw(){
    //エフェクトのイントロ
    if(gui->DrawFlg[gui->R]){
        gui->vidGrabber[gui->R].draw(0,0);
        int buf = gui->buffer%bufferSize;//バッファサイズを置換0~1799
        
        if(buf<(bufferSize/2)){//格納バッファの半分前
            index = bufferSize+(buf-bufferSize/2); //バッファサイズで補正
        }else{
            index = buf-(bufferSize/2);//単純に任意のフレーム前
        }
        //------------1.巻き戻し----------------
        //巻き戻し再生の開始
        if(flg){
            index += (bufferSize/2)-number;
            if(index >= bufferSize){//バッファの大きさ以上になってしまったら
                index = index - bufferSize;
            }
            number += 5;
            if(number >= (bufferSize/2)){//戻したい過去まで巻き戻したら
                flg = false;
                
            }
        }
        //------------2.描画/エフェクト----------------
        //FBOの描画全般
        gui->DrawFBO(gui->R,index);
        
        if(!flg){
            counter ++;//巻き戻し終了->描画の開始からインクリメント
        }
        
        //-----------3.アウトロ------------
        if(counter > 3*bufferSize/4){
            ofSetColor(0, 0, 0, counter%(3*bufferSize/4));
            ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
        }
        
        
        
        //-------------終了処理--------------
        if(counter == bufferSize){//バッファサイズまで再生が完了したら
            gui->DrawFlg[gui->R] = false;
            counter = 0;
            flg = true;
            number = 0;
            beatsound.stop();
        }
    }
    
}
