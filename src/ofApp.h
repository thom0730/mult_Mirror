#pragma once

#include "ofMain.h"
#include "GuiApp.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void stop();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		shared_ptr<GuiApp> gui;
    
    int counter = 0;//遅延処理の開始から終了までを管理
    int index = 0;//遅延処理のバッファのインデックス
    int startCount = 0;
    
    int number = 0;
    bool flg = true; //エフェクトの切り替え(巻き戻し->遅延)
    
    ofSoundPlayer beatsound;
    
   
    
    
};
