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


class ACMidiController : public ofxMidiListener{
public:
    ACMidiController();
    ~ACMidiController();
    
    void setup();
    void draw();
    
    void setMidiMode(MidiModeType type);
    
    void showMidiPorts();
    void openPort(string deviceName);
    void closePorts();
    void newMidiMessage(ofxMidiMessage& eventArgs);
    
private:
    MidiStatus midiStatus;
    MidiModeType midiMode;
    
    ofTrueTypeFont font;
    ofxMidiIn midiIn;
	ofxMidiMessage midiMessage;
    
    vector<string> portLists;
    void draw(ofEventArgs& event);
    
    ACMidiButton midiPortListOpenButton;
    ACMidiButton playButton;
    
    vector<ACMidiButton*> lists;
    

    
    void openPortEventHandler(bool &bPress);
    void controlButtonEventHandler(int &tag);
    void portButtonEventHandler(int &tag);
    
};