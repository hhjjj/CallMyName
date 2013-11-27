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


class ACMidiController{
public:
    ACMidiController();
    ~ACMidiController();
    
    void setup(ofxMidiIn* midi);
    void draw();
    
    void setMidiMode(MidiModeType type);
    
    void showMidiPorts();
    void openPort(string deviceName);
    void closePorts();
//    void newMidiMessage(ofxMidiMessage& eventArgs);
    
    void addMidiControl(ACMidiButton* midiControl);
    void midiControlTagEventHandler(int &tag);
private:
    MidiStatus midiStatus;
    MidiModeType midiMode;
    
    ofTrueTypeFont font;
    
    ofxMidiIn* midiIn;
//	ofxMidiMessage midiMessage;
    
    
    vector<string> portLists;
    void draw(ofEventArgs& event);
    
    ACMidiButton midiPortListOpenButton;
    
    vector<ACMidiButton*> midiControlItem;
    
    vector<ACMidiButton*> lists;
    

    
    void openPortEventHandler(bool &bPress);
    void portButtonEventHandler(int &tag);
    
    

//    void controlButtonEventHandler(int &tag);
//    void midiTriggerEventHandler(bool &bPress);
//    void midiSetButtonEventHandler(bool &bPress);
    
};