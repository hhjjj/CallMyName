//
//  CallMyNamePlayer.cpp
//  CallMyName
//
//  Created by hojun on 11/23/13.
//
//

#include "CallMyNamePlayer.h"

CallMyNamePlayer::CallMyNamePlayer(){
    bWasSetup = false;
}

CallMyNamePlayer::~CallMyNamePlayer(){
    if(bWasSetup){
//        ofRemoveListener(ofEvents().draw, this, &CallMyNamePlayer::draw);
    }
    bWasSetup = false;
}

void CallMyNamePlayer::setup(string filename){

    
    pos.x = 0;
    pos.y = 0;
    width = 0;
    height = 0;
    setRect(pos.x, pos.y, width, height, ofColor(255,255,255));
    
    // load sound file into memory
    player.loadSound(filename, false);
    // allow multiplayer
    // not working very well..
//    player.setMultiPlay(true);
    if(!bWasSetup){
//        ofAddListener(ofEvents().draw, this, &CallMyNamePlayer::draw);
        bWasSetup = true;
    }
}

void CallMyNamePlayer::setRect(float x, float y, float w, float h, ofColor c){
    pos.x = x;
    pos.y = y;
    width = w;
    height = h;
    rectColor = c;
    rect = ofRectangle(pos.x, pos.y, width, height);
}

ofVec2f CallMyNamePlayer::getPosition(){
    return pos;
}

void CallMyNamePlayer::setVolume(float vol){
    player.setVolume(vol);
}


void CallMyNamePlayer::play(){
    player.play();
}

void CallMyNamePlayer::draw(){
    ofPushStyle();
    ofSetColor(rectColor);
    if (player.getIsPlaying()) {
        ofFill();
        ofRect(ofRectangle(pos.x, pos.y, player.getPosition() * width, height));
    }
    ofNoFill();
    ofRect(rect);
    ofPopStyle();
}

//void  CallMyNamePlayer::draw(ofEventArgs& event){
//    
//}
