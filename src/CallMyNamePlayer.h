//
//  CallMyNamePlayer.h
//  CallMyName
//
//  Created by hojun on 11/23/13.
//
//

#pragma once

#include "ofMain.h"
#include "ofxTimer.h"

class CallMyNamePlayer {
    
public:
    CallMyNamePlayer();
    ~CallMyNamePlayer();
    
    
    void setup(string filename);
    void setVolume(float vol);
    void play();
    void playAfterMs(int ms);
    void draw();
    void setRect(float x, float y, float w, float h, ofColor c);
    ofVec2f getPosition();
    
private:
    ofRectangle rect;
    ofSoundPlayer player;
    bool bWasSetup;
    ofVec2f pos;
    float width;
    float height;
    ofColor rectColor;
    ofxTimer timer;
//    void draw(ofEventArgs& event);
    void update(ofEventArgs& event);
    void play(ofEventArgs &e);
};
