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
#include "ACMidiButton.h"

#define numOfShowPortList (3)

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
    ofTrueTypeFont font;
    ofxMidiIn midiIn;
	ofxMidiMessage midiMessage;
    
    vector<string> portLists;
    void draw(ofEventArgs& event);
    
    ACMidiButton midiPortListOpenButton;
    ACMidiButton portListButtons [numOfShowPortList];
//    vector<ACMidiButton*> portListButtons;
    
    void buttonEventHandler(bool &bPress);
    void portButtonEventHandler(int &tag);
    
};