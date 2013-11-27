//
//  ACMidiButton.h
//  CallMyName
//
//  Created by songhojun on 11/27/13.
//
//

#pragma once

#include "ofMain.h"


enum MidiModeType{
    MIDI_MODE_NORMAL = 0,
    MIDI_MODE_EDIT = 1
};


class ACMidiButton {
    
public:
    ACMidiButton();
    ~ACMidiButton();
    void setup(float x, float y, string title);
    ofRectangle getButtonRect();
    
    void setTitle(string title);
    string getTitle();

    void setPosition(float x, float y);
    void setToggle(bool bToggle, bool bDefaultVal);
    void setPressedColor(ofColor c);
    void setReleasedColor(ofColor c);
    
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
    bool bWasSetup;
    bool bHasFocus;
    bool bIsPressed;
    bool bIsDragged;
    bool bToggleButton;
    
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
