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
//        ofRemoveListener(ofEvents().update, this, &CallMyNamePlayer::update);
        ofRemoveListener(timer.TIMER_REACHED, this, &CallMyNamePlayer::play);
    }
    bWasSetup = false;
}

void CallMyNamePlayer::setup(string filename){

    
    pos.x = 0;
    pos.y = 0;
    width = 0;
    height = 0;
    setRect(pos.x, pos.y, width, height, ofColor(255,255,255));
    timer.setup(10, false);
    timer.pauseTimer();
    
    // load sound file into memory
//    player.loadSound(filename, false);
    player.loadSound(filename);
//    player.play();
//    player.stop();
    
    // allow multiplayer
    // not working very well..
//    player.setMultiPlay(true);
    if(!bWasSetup){
//        ofAddListener(ofEvents().draw, this, &CallMyNamePlayer::draw);
//        ofAddListener(ofEvents().update, this, &CallMyNamePlayer::update);
        ofAddListener(timer.TIMER_REACHED, this, &CallMyNamePlayer::play);
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
    timer.reset();
    player.play();
}

void CallMyNamePlayer::play(ofEventArgs &e){
    ofLogNotice("event!");
    play();
}

void CallMyNamePlayer::stop(){
    timer.pauseTimer();
    player.stop();
    player.setPosition(0);
}

void CallMyNamePlayer::playAfterMs(int ms){
    if (player.getIsPlaying()) {

        player.stop();
        player.setPosition(0);
    }
    timer.reset();
    timer.setTimer(ms);
    timer.startTimer();
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
void CallMyNamePlayer::update(ofEventArgs& event){

}

//void  CallMyNamePlayer::draw(ofEventArgs& event){
//    
//}
