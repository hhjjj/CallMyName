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


class ACMidiButton {
    
public:
    ACMidiButton();
    ~ACMidiButton();
    
    int channel;
    
	/// message-specific values,
	/// converted from raw bytes
	int pitch;			//< 0 - 127
	int velocity;		//< 0 - 127
	int control;		//< 0 - 127
	int value;			//< depends on message status type

    
    
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
    
    void setTag(int tag);
    int getTag();
    
    void setPressed(bool bSet);
    bool isPressed();
        
    void drawPressed();
    void drawReleased();

    void draw();
    
    ofEvent<bool> pressEvent;
    ofEvent<int> tagEvent;
    
    void mouseMoved(ofMouseEventArgs& event);
    void mouseDragged(ofMouseEventArgs& event);
    void mousePressed(ofMouseEventArgs& event);
    void mouseReleased(ofMouseEventArgs& event);
    
private:
    MidiModeType midiMode;
    MidiStatus midiStatus;

    bool bWasSetup;
    bool bHasFocus;
    bool bIsPressed;
    bool bIsDragged;
    bool bToggleButton;
    bool bEnableEvents;
    
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
    float fontSize;
    float hMargin;
    float vMargin;
};
