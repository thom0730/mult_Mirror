#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(255);
	ofSetCircleResolution(200);
    
    

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	
    
    ofSetColor(255);
    if(gui->DrawFlg[gui->L]){
        if(counter < gui->fbo[gui->L].size()){
            /*コメント解除でグリッチを生成
            gui->myGlitch[0][counter].setFx(OFXPOSTGLITCH_CR_BLUERAISE	, true);
            gui->myGlitch[0][counter].generateFx(); //グリッチを生成
             */
            gui->fbo[gui->L][counter]->draw(0, 0,1125,ofGetHeight());
            cout << "デバッグ " << counter <<endl;
        }else{
            counter = 0;
        }
            }
    counter ++ ;
    
    //エフェクト
    gui->Black();
    
    
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
