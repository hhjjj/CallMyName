//
//  ACMidiSlider.h
//  CallMyName
//
//  Created by hojun on 11/28/13.
//
//

#pragma once

#include "ofMain.h"
#include "ACMidiController.h"




class ACMidiSlider {
    
public:
    ACMidiSlider();
    ~ACMidiSlider();
    
    
    void setup(float x, float y, string title);
    ofRectangle getRect();
    
    void setTitle(string title);
    string getTitle();
    
    void setPosition(float x, float y);
    void setSize(float w);

    void setSliderColor(ofColor c);
    void setBarColor(ofColor c);
    
    void enableEvents(bool bSet);
    
    void setMidiMode(MidiModeType type);
    MidiModeType getMidiMode();
    
    
    void setMidiMessage(ofxMidiMessage msg);
    ofxMidiMessage getMidiMessage();
    void triggerMidiEvent(ofxMidiMessage msg);
    
    void setTag(int tag);
    int getTag();
    
    
    bool isSetMidiPressed();
    
    
    void drawMidiMessage();
    void draw();
    
    ofEvent<bool> midiSetPressEvent;
    ofEvent<int> tagEvent;
    ofEvent<int> knobValueEvent;
    void updateBarPos(float x, float y);
    void mouseMoved(ofMouseEventArgs& event);
    void mouseDragged(ofMouseEventArgs& event);
    void mousePressed(ofMouseEventArgs& event);
    void mouseReleased(ofMouseEventArgs& event);
    
private:
    MidiModeType midiMode;
    ofxMidiMessage midiMsg;
    
    bool bWasSetup;
    bool bHasFocus;
    bool bIsMidiSetPressed;
    bool bIsDragged;
    bool bEnableEvents;
    bool bEnableMidiSetEvents;
    
    float dragX;
    float dragY;
    
    float mouseX;
    float mouseY;
    float startMouseX;
    float startMouseY;
    
    float sliderVal;
    
    
    
    float posX;
    float posY;
    
    
    string buttonTitle;
    ofRectangle rect;
    ofRectangle bBox;
    
    int tagNum;
    
    ofColor sliderColor;
    ofColor barColor;

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

