//
//  ACMidiController.cpp
//  CallMyName
//
//  Created by hojun on 11/26/13.
//
//

#include "ACMidiController.h"

ACMidiController::ACMidiController(){
}

ACMidiController::~ACMidiController(){
    midiIn.closePort();
    midiIn.removeListener(this);
    ofRemoveListener(ofEvents().draw, this, &ACMidiController::draw);
    ofRemoveListener(midiPortListOpenButton.pressEvent, this, &ACMidiController::buttonEventHandler);
    for (int i = 0; i < numOfShowPortList; i++) {
        ofRemoveListener(portListButtons[i].tagEvent, this, &ACMidiController::portButtonEventHandler);
    }
}

void ACMidiController::setup() {
    
    font.loadFont("NewMedia Fett.ttf", 29);
    
    midiIn.ignoreTypes(true, true, true);
    
    midiPortListOpenButton.setup(20, 20, "OPEN MIDI PORTS");
    midiPortListOpenButton.setPressedColor(ofColor(255,0,0));
    midiPortListOpenButton.setReleasedColor(ofColor(255,255,255));
    
    
    for (int i = 0; i < numOfShowPortList; i++) {
        portListButtons[i].setup(20, 20, "");
        portListButtons[i].setPressedColor(ofColor(255,0,0));
        portListButtons[i].setReleasedColor(ofColor(255,255,255));
        portListButtons[i].setTag(i);
        ofAddListener(portListButtons[i].tagEvent, this, &ACMidiController::portButtonEventHandler);
    }
    
    
    midiIn.addListener(this);
    ofAddListener(midiPortListOpenButton.pressEvent, this, &ACMidiController::buttonEventHandler);
    ofAddListener(ofEvents().draw, this, &ACMidiController::draw);
}

void ACMidiController::showMidiPorts(){
    vector<string> ports = midiIn.getPortList();
    
}



void ACMidiController::openPort(string deviceName){
    midiIn.openPort(deviceName);
}

void ACMidiController::closePorts(){
    midiIn.closePort();
}

void ACMidiController::newMidiMessage(ofxMidiMessage& msg) {
    
	// make a copy of the latest message
	midiMessage = msg;
    
    ofLogNotice("new message!!");
}

void  ACMidiController::draw(ofEventArgs& event){
    
    midiPortListOpenButton.draw();
    for (int i = 0; i < numOfShowPortList; i++) {
        portListButtons[i].draw();
    }
}

void ACMidiController::buttonEventHandler(bool &bPress){
    if (bPress) {
        
        portLists = midiIn.getPortList();
        for (int i = 0; i < numOfShowPortList; i++) {
            portListButtons[i].setTitle(portLists[i]);
            portListButtons[i].setPosition(20, 30 + 30 +30*i);
        }
    }
}

void ACMidiController::portButtonEventHandler(int &tag){
    openPort(portLists[tag]);
}