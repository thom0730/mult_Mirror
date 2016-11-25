//
//  config.hpp
//  mult_Mirror
//
//  Created by 牧野 覚 on 2016/11/24.
//
//

#ifndef config_h
#define config_h

#include <stdio.h>
#include "ofMain.h"
#include "ofxXmlSettings.h"

// Window pos,size
class WindowSettings
{
public:
    ofGLFWWindowSettings settings;
    
    void set(float X, float Y, int W, int H, bool R);
    void update(ofRectangle rect);
};

class CameraSettings
{
public:
    int id;
    int capWidth;
    int capHeight;
    void set(int ID, int W, int H);
};

#define SETTINGFILENAME "config.xml"

class Config
{
public:
    ofxXmlSettings xmlConfig;
    
    WindowSettings gui;
    WindowSettings mirror1;
    WindowSettings mirror2;
    CameraSettings cam0;
    CameraSettings cam1;
    
    Config();
    ~Config();
    
    void save(void);
    void addWindowSettings(WindowSettings &ws);
    
    void load(void);
    void getWindowSettings(WindowSettings &ws);
};

// config is global
extern Config config;




#endif /* config_h */
