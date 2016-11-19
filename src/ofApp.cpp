#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
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
    ofBackground(0);
	
    
    ofSetColor(255);
    //フラグがたっている間は遅延処理
    
    if(gui->DrawFlg[gui->L]){
        int buf = gui->buffer%bufferSize;//0~1799
      //int index = 0;
    
        
        if(buf<(bufferSize/2)){
             index = bufferSize+(buf-bufferSize/2); //バッファサイズで補正
        }else{
             index = buf-(bufferSize/2);//単純に任意のフレーム前
        }
        
        //グリッチ各種
        gui->myGlitch[gui->L][index].setFx(OFXPOSTGLITCH_CONVERGENCE,gui->convergence);
        gui->myGlitch[gui->L][index].setFx(OFXPOSTGLITCH_SHAKER	, gui->shaker);
        gui->myGlitch[gui->L][index].setFx(OFXPOSTGLITCH_CUTSLIDER	, gui->cutslider);
        gui->myGlitch[gui->L][index].setFx(OFXPOSTGLITCH_NOISE	, gui->noise);
        gui->myGlitch[gui->L][index].setFx(OFXPOSTGLITCH_SLITSCAN	, gui->slitscan);
        gui->myGlitch[gui->L][index].setFx(OFXPOSTGLITCH_SWELL	, gui->swell);
        gui->myGlitch[gui->L][index].setFx(OFXPOSTGLITCH_CR_BLUERAISE	, gui->blueraise);
        
        gui->myGlitch[gui->L][index].generateFx();
        
        //FBOの描画
        gui->fbo[gui->L][index]->draw(0, 0,1125,ofGetHeight());
        
        counter ++;//描画の開始からインクリメント
        
        if(counter == bufferSize){//バッファサイズまで再生が完了したら
            gui->DrawFlg[gui->L] = false;
            counter = 0;
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
