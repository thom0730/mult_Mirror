#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
    ofSetFrameRate(30);
	ofSetCircleResolution(200);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    
  

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255);
    //フラグがたっている間は遅延処理
    
    //エフェクトのイントロ
    if(gui->DrawFlg[gui->L]){
        int buf = gui->buffer%bufferSize;//バッファサイズを置換0~1799
        
        if(buf<(bufferSize/2)){//格納バッファの半分前
             index = bufferSize+(buf-bufferSize/2); //バッファサイズで補正
        }else{
             index = buf-(bufferSize/2);//単純に任意のフレーム前
        }
        
        
        if(flg){//巻き戻し再生ON
            index += (bufferSize/2)-number;
            if(index >= bufferSize){//バッファの大きさ以上になってしまったら
                index = index - bufferSize;
            }
             number += 8;
            if(number >= (bufferSize/2)){//戻したい過去まで巻き戻したら
                flg = false;
                
            }
        }
        cout << "現在のindex = " << index << endl;
        cout << "現在のnumber = " << number << endl;



       
        //FBOの描画全般
        gui->DrawFBO(gui->L,index);
        
        counter ++;//描画の開始からインクリメント
        
        if(counter == bufferSize){//バッファサイズまで再生が完了したら
            gui->DrawFlg[gui->L] = false;
            counter = 0;
            flg = true;
            number = 0;
        }
    }

    //エフェクト
 //   gui->Black();
  
    
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
