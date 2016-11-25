//
//  config.cpp
//  mult_Mirror
//
//  Created by 牧野 覚 on 2016/11/24.
//
//

#include "config.h"

void WindowSettings::set(float X, float Y, int W, int H, bool R)
{
    settings.setPosition( ofVec2f(X,Y));
    settings.width = W;
    settings.height = H;
    settings.resizable = R;
}

void WindowSettings::update(ofRectangle rect)
{
    settings.setPosition( ofVec2f( rect.x, rect.y) );
    settings.width = rect.width;
    settings.height = rect.height;
}


void CameraSettings::set(int ID, int W, int H)
{
    id = ID;
    capWidth = W;
    capHeight = H;
}


Config::Config()
{
    config.gui.set(0, 0, 640, 720, false);
    config.mirror1.set(300, 0, 500, 750, true);
    config.mirror2.set(400, 0, 500, 750, true);
    config.cam0.set( 0, 640, 480);
    config.cam1.set( 1, 640, 480);
}

Config::~Config()
{
}


void Config::save(void)
{
    xmlConfig.clear();
    
    xmlConfig.addTag("window");
    xmlConfig.pushTag("window");
    
    xmlConfig.addTag("gui");
    xmlConfig.pushTag("gui");
    addWindowSettings(gui);
    xmlConfig.popTag();
    
    xmlConfig.addTag("mirror1");
    xmlConfig.pushTag("mirror1");
    addWindowSettings(mirror1);
    xmlConfig.popTag();
    
    xmlConfig.addTag("mirror2");
    xmlConfig.pushTag("mirror2");
    addWindowSettings(mirror2);
    xmlConfig.popTag();
    
    xmlConfig.popTag();
    
    xmlConfig.addTag("camera");
    xmlConfig.pushTag("camera");
    
    xmlConfig.addTag("dev0");
    xmlConfig.pushTag("dev0");
    xmlConfig.addValue("id", cam0.id);
    xmlConfig.addValue("width", cam0.capWidth);
    xmlConfig.addValue("height", cam0.capHeight);
    xmlConfig.popTag();
    
    xmlConfig.addTag("dev1");
    xmlConfig.pushTag("dev1");
    xmlConfig.addValue("id", cam1.id);
    xmlConfig.addValue("width", cam1.capWidth);
    xmlConfig.addValue("height", cam1.capHeight);
    xmlConfig.popTag();
    
    xmlConfig.saveFile(SETTINGFILENAME);
    ofLogNotice("setting file saved: " SETTINGFILENAME );
}


void Config::load(void)
{
    
    if ( xmlConfig.loadFile(SETTINGFILENAME) ) {
        xmlConfig.pushTag("window");
        xmlConfig.pushTag("gui");
        getWindowSettings(gui);
        xmlConfig.popTag();
        xmlConfig.pushTag("mirror1");
        getWindowSettings(mirror1);
        xmlConfig.popTag();
        xmlConfig.pushTag("mirror2");
        getWindowSettings(mirror2);
        xmlConfig.popTag();
        xmlConfig.popTag(); // "window"
        
        xmlConfig.pushTag("camera");
        xmlConfig.pushTag("dev0");
        cam0.id = xmlConfig.getValue("id", 0);
        cam0.capWidth = xmlConfig.getValue("width", 640);
        cam0.capHeight = xmlConfig.getValue("height", 480);
        xmlConfig.popTag();
        xmlConfig.pushTag("dev1");
        cam1.id = xmlConfig.getValue("id", 1);
        cam1.capWidth = xmlConfig.getValue("width", 640);
        cam1.capHeight = xmlConfig.getValue("height", 480);
        xmlConfig.popTag();
        xmlConfig.popTag();	// "camera"
        
        ofLogNotice("setting file loaded: " SETTINGFILENAME);
    }
    else {
        save();
        ofLogNotice("setting file created.");
    }
    
}

void Config::addWindowSettings(WindowSettings &ws)
{
    ofVec2f v = ws.settings.getPosition();
    xmlConfig.addValue("X", v.x);
    xmlConfig.addValue("Y", v.y);
    
    xmlConfig.addValue("W", ws.settings.width);
    xmlConfig.addValue("H", ws.settings.height);
    xmlConfig.addValue("resizeable", ws.settings.resizable);
}

void Config::getWindowSettings(WindowSettings &ws)
{
    ofVec2f v;
    v.x = xmlConfig.getValue("X", 0);
    v.y = xmlConfig.getValue("Y", 0);
    ws.settings.setPosition(v);
    
    ws.settings.width = xmlConfig.getValue("W", 100);
    ws.settings.height = xmlConfig.getValue("H", 100);
    ws.settings.resizable = xmlConfig.getValue("resizeable", true);
}


// Global 
Config config;
