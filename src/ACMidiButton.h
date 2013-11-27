//
//  ACMidiButton.h
//  CallMyName
//
//  Created by songhojun on 11/27/13.
//
//

#pragma once

#include "ofMain.h"
#include "ofxMidi.h"


enum MidiModeType{
    MIDI_MODE_NORMAL = 0,
    MIDI_MODE_EDIT = 1
};

enum MidiControlType{
    MIDI_CONTROL_BUTTON = 0,
    MIDI_CONTROL_KNOB = 1
};

class ACMidiButton {
    
public:
    ACMidiButton();
    ~ACMidiButton();
    
    
//    MidiStatus midiStatus;
//    
//    int channel;
//    
//	/// message-specific values,
//	/// converted from raw bytes
//	int pitch;			//< 0 - 127
//	int velocity;		//< 0 - 127
//	int control;		//< 0 - 127
//	int value;			//< depends on message status type

    void setup(float x, float y, string title);
    ofRectangle getButtonRect();
    
    void setTitle(string title);
    string getTitle();

    void setPosition(float x, float y);
    void setToggle(bool bToggle, bool bDefaultVal);
    void setPressedColor(ofColor c);
    void setReleasedColor(ofColor c);
    
    void enableEvents(bool bSet);
    
    void setMidiMode(MidiModeType type);
    MidiModeType getMidiMode();
    
    void setMidiControlType(MidiControlType type);
    MidiControlType getMidiControlType();
    
    void setMidiMessage(ofxMidiMessage msg);
    ofxMidiMessage getMidiMessage();
    void triggerMidiEvent(ofxMidiMessage msg);
    
    void setTag(int tag);
    int getTag();
    
    void setPressed(bool bSet);
    bool isPressed();
    
    bool isSetMidiPressed();
        
    void drawPressed();
    void drawReleased();
    void drawMidiMessage();
    void draw();
    
    ofEvent<bool> mousePressEvent;
    ofEvent<bool> midiTriggerEvent;
    ofEvent<bool> midiSetPressEvent;
    ofEvent<int> tagEvent;
    ofEvent<int> knobValueEvent;
    
    void mouseMoved(ofMouseEventArgs& event);
    void mouseDragged(ofMouseEventArgs& event);
    void mousePressed(ofMouseEventArgs& event);
    void mouseReleased(ofMouseEventArgs& event);
    
private:
    MidiModeType midiMode;
    MidiControlType midiControlType;
    ofxMidiMessage midiMsg;
    
    bool bWasSetup;
    bool bHasFocus;
    bool bIsPressed;
    bool bIsMidiSetPressed;
    bool bIsDragged;
    bool bToggleButton;
    bool bEnableEvents;
    bool bEnableMidiSetEvents;
    
    float posX;
    float posY;

    
    string buttonTitle;
    ofRectangle rect;
    ofRectangle bBox;
    
    int tagNum;
    
    ofColor pressedColor;
    ofColor releasedColor;
    ofColor midiPressedColor;
    ofColor midiReleasedColor;

    ofTrueTypeFont font;
    ofTrueTypeFont msgFont;
    float fontSize;
    float msgFontSize;
    float hMargin;
    float vMargin;
    
    string midiStr;
};
