#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(255);
    ofSetFrameRate(30);
	ofSetCircleResolution(200);
    
    

}

//--------------------------------------------------------------
void ofApp::update(){
    
    /*コメント解除でグリッチを生成
     gui->myGlitch[0][counter].setFx(OFXPOSTGLITCH_CR_BLUERAISE	, true);
     gui->myGlitch[0][counter].generateFx(); //グリッチを生成
     */

}

//--------------------------------------------------------------
void ofApp::draw(){
	
    
    ofSetColor(255);
    //フラグがたっている間は遅延処理
    if(gui->DrawFlg[gui->L]){
        int index = gui->buffer%(bufferSize/2); //800フレーム前を参照
        gui->fbo[gui->L][index]->draw(0, 0,1125,ofGetHeight());
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
