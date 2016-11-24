#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
    ofSetFrameRate(30);
	ofSetCircleResolution(200);
    ofEnableAlphaBlending();
    
    beatsound.load("heartbeat.mp3");
    
    fft.setup();
    fft.setNumFFTBins(16);
    fft.setNormalize(true);

    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    Trigger();
    gui->UpdateFBO(gui->L,index);
    fft.update();
    float low = fft.getLowVal();
    float mid = fft.getMidVal();
    float high = fft.getHighVal();
    /*
    cout << "low " << low << endl;
    cout << "mid " << mid << endl;
    cout << "high " << high << endl;
     */

    
    //心拍音の再生とエフェクト同期
    if(counter == 6*BufferSize/10){
        beatsound.play();
    }
    if(low > 0.01){
        gui->shader[1] = true;
        gui->shader[4] = true;
    }else{
        gui->shader[1] = false;
        gui->shader[4] = false;
    }
    
  

}

//--------------------------------------------------------------
void ofApp::draw(){
  //  ofBackground(0);
    ofSetColor(255);
    
    
    //------------現在------------------
    if(gui->startL){
        gui->vidGrabber[gui->L].draw(-290,0,1125,ofGetHeight());
        //黒の幕開け
        ofSetColor(0,0,0,300-startCount);
        ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
        //現在映像の部分のカウンターのインクリメント
        startCount++;
        if(startCount>BufferSize/4){//だいたいこんなもん?
            gui->startL = false;//「現在」を抜ける
            gui->DrawFlg[gui->L] = true;//イントロの開始
            startCount = 0; //エフェクトスタートのトリガーのリセット
            
        }
    }
    
    //---------0.イントロ(準備)---------
    if(gui->DrawFlg[gui->L]){

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
            if(index >= BufferSize){//バッファの大きさ以上になってしまったら(補正)
                index = index - BufferSize;
            }
             number += 10; //巻き戻し用
            if(number >= (BufferSize/2)){//戻したい過去まで巻き戻したら
                flg = false;
            }
        }
    

        //------------2.描画/エフェクト----------------
        //FBOの描画全般
        //エフェクトのスイッチ
        gui->effectControl(counter);

        gui->DrawFBO(gui->L,index);
        
       // ofSetColor(255,1,1);
        //ofDrawRectangle(100 , 100, 20,20);
        
        //ここで背景色をもとに戻さないといけないっぽい
        ofSetColor(255);
        
        if(!flg){
            counter ++;//巻き戻し終了->描画の開始からインクリメント
            cout << "counter " << counter << endl;
        }

        //-----------3.アウトロ(レイヤーが重なっていく)------------
        if(counter > 6*BufferSize/10){
            cout << "END" << endl;
            ofSetColor(0, 0, 0, counter%(6*BufferSize/10));
            ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
 
            //現在の映像を流し始める
            ofSetColor(255,255, 255, counter%(6*BufferSize/10));
            gui->vidGrabber[gui->L].draw(0,0,1125,ofGetHeight());
        }
        gui->Black();

        //-------------終了処理--------------
        if(counter == BufferSize){//バッファサイズまで再生が完了したら
            gui->DrawFlg[gui->L] = false;
            counter = 0;
            flg = true;
            number = 0;
            beatsound.stop();
            //黒色エフェクトの停止処理
            gui->blackCircle = false;
            gui-> circleRadius = 0;
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
//--------------------------------------------------------------
void ofApp::Trigger(){
    if(counter == 0 ){ //counterが0の時点では動画セットは再生していない
        int i  = ofRandom(1000);
        if(i == 2){
            gui->startL = true;
            gui->startR = true;
        }
    }
}