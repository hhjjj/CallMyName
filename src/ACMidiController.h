//
//  ACMidiController.h
//  CallMyName
//
//  Created by hojun on 11/26/13.
//
//

#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include "ofxUI.h"

class ACMidiController: public ofxMidiListener{
public:
    ACMidiController();
    ~ACMidiController();
    
    void setup();
    
    void showMidiPorts();
    void openPort(string deviceName);
    void closePorts();
    void newMidiMessage(ofxMidiMessage& eventArgs);
private:
    ofxMidiIn midiIn;
	ofxMidiMessage midiMessage;
    
    vector<string> portLists;
    
    ofxUICanvas *gui;
    ofxUIDropDownList *ddl;
	void guiEvent(ofxUIEventArgs &e);
    
    void draw(ofEventArgs& event);
};