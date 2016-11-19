#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
    ofSetFrameRate(30);
	ofSetCircleResolution(200);
    ofEnableAlphaBlending();
    
    beatsound.load("heartbeat.mp3");
    
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    gui->UpdateFBO(gui->L,index);

    if(counter == 3*bufferSize/4){
        beatsound.play();
    }
    
  

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255);
    
    
    //------------現在------------------
    if(gui->startL){
        gui->vidGrabber[gui->L].draw(0,0,1125,ofGetHeight());
        startCount++;
        if(startCount>bufferSize/4){//だいたいこんなもん?
            gui->startL = false;//「0.現在」を抜ける
            gui->DrawFlg[gui->L] = true;//イントロの開始
            startCount = 0; //エフェクトスタートのトリガーのリセット
        }
    }
    
    //---------0.イントロ(準備)---------
    if(gui->DrawFlg[gui->L]){

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
        gui->DrawFBO(gui->L,index);

        gui->Black();
        
        if(!flg){
            counter ++;//巻き戻し終了->描画の開始からインクリメント
        }
        
 
        //-----------3.アウトロ(レイヤーが重なっていく)------------
        if(counter > 3*bufferSize/4){
            ofSetColor(0, 0, 0, counter%(3*bufferSize/4));
            ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
 
            //現在の映像を流し始める
            ofSetColor(255,255, 255, counter%(3*bufferSize/4));
            gui->vidGrabber[gui->L].draw(0,0,1125,ofGetHeight());
        }

        //-------------終了処理--------------
        if(counter == bufferSize){//バッファサイズまで再生が完了したら
            gui->DrawFlg[gui->L] = false;
            counter = 0;
            flg = true;
            number = 0;
            beatsound.stop();
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){


}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
   

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
//--------------------------------------------------------------
void ofApp::stop(){
    beatsound.stop();
    
}