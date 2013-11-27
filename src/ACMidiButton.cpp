//
//  ACMidiButton.cpp
//  CallMyName
//
//  Created by songhojun on 11/27/13.
//
//

#include "ACMidiButton.h"

ACMidiButton::ACMidiButton(){
    
}

ACMidiButton::~ACMidiButton(){
    if(bWasSetup){
        ofUnregisterMouseEvents(this);
    }
	bWasSetup = false;
    
}

void ACMidiButton::setup(float x, float y, string title){
    bWasSetup = false;
    bHasFocus = false;
    bIsPressed = false;
    bIsMidiSetPressed = false;
    bIsDragged = false;
    bToggleButton = false;
    bEnableEvents = true;
    bEnableMidiSetEvents = false;
    
    midiStr = "";

    buttonTitle = title;
    
    tagNum = 0;
    
    fontSize = 18;
    msgFontSize = 12;
    
    font.loadFont("NewMedia Fett.ttf", fontSize);
    msgFont.loadFont("NewMedia Fett.ttf", msgFontSize);
    
    posX = x;
    posY = y;

    bBox = font.getStringBoundingBox(buttonTitle, posX, posY);
    
    hMargin = fontSize/4.0;
    vMargin = fontSize/4.0;
    
    rect = ofRectangle(posX, posY, bBox.width+hMargin *2, bBox.height + vMargin * 2);
    
    
    
    if(!bWasSetup){
        ofRegisterMouseEvents(this);
        bWasSetup = true;
	}
    
    midiPressedColor = ofColor(0,0,255,255);
    midiReleasedColor = ofColor(0,0,255,150);
    setMidiMode(MIDI_MODE_NORMAL);
    setMidiControlType(MIDI_CONTROL_BUTTON);
}

ofRectangle ACMidiButton::getButtonRect(){
    return rect;
}

void ACMidiButton::setTitle(string title){
    buttonTitle = title;
    bBox = font.getStringBoundingBox(buttonTitle, posX, posY);
    rect = ofRectangle(posX, posY, bBox.width+hMargin *2, bBox.height + vMargin * 2);
}

string ACMidiButton::getTitle(){
    return buttonTitle;
}

void ACMidiButton::setPosition(float x, float y){
    posX = x;
    posY = y;
    bBox = font.getStringBoundingBox(buttonTitle, posX, posY);
    rect = ofRectangle(posX, posY, bBox.width+hMargin *2, bBox.height + vMargin * 2);
}


void ACMidiButton::setToggle(bool bToggle, bool bDefaultVal){
    bToggleButton = bToggle;
    bIsPressed = bDefaultVal;
}

void ACMidiButton::setPressedColor(ofColor c){
    pressedColor = c;
}

void ACMidiButton::setReleasedColor(ofColor c){
    releasedColor = c;
}

void ACMidiButton::setMidiMode(MidiModeType type){
    midiMode = type;
    if (midiMode == MIDI_MODE_NORMAL){
        bIsMidiSetPressed = false;
        bEnableMidiSetEvents = false;
        bEnableEvents = true;
    }
    else if (midiMode == MIDI_MODE_EDIT){
        bEnableMidiSetEvents = true;
        bEnableEvents = false;
    }
}


void ACMidiButton::setMidiControlType(MidiControlType type){
    midiControlType = type;
}

MidiControlType ACMidiButton::getMidiControlType(){
    return midiControlType;
}


MidiModeType ACMidiButton::getMidiMode(){
    return midiMode;
}

void ACMidiButton::setMidiMessage(ofxMidiMessage msg){
    midiMsg = msg;
}

ofxMidiMessage ACMidiButton::getMidiMessage(){
    return midiMsg;
}

void ACMidiButton::triggerMidiEvent(ofxMidiMessage msg){
    switch (msg.status) {
        case MIDI_NOTE_ON:
            if (msg.pitch == midiMsg.pitch) {
                bIsPressed = true;
                ofNotifyEvent(midiTriggerEvent, bIsPressed);
            }
            
            break;
        case MIDI_NOTE_OFF:
            if (msg.pitch == midiMsg.pitch) {
                bIsPressed = false;
                ofNotifyEvent(midiTriggerEvent, bIsPressed);
            }
            break;
        case MIDI_CONTROL_CHANGE:
            if (msg.control == midiMsg.control) {
                if(midiControlType == MIDI_CONTROL_BUTTON){
                    if (msg.value > 64) {
                        bIsPressed = true;
                        ofNotifyEvent(midiTriggerEvent, bIsPressed);
                    }
                    else{
                        bIsPressed = false;
                        ofNotifyEvent(midiTriggerEvent, bIsPressed);
                    }
                }
            }
            else if (midiControlType == MIDI_CONTROL_KNOB){
                ofNotifyEvent(knobValueEvent, msg.value);
            }
            
            break;
            
        default:
            break;
    }
}

void ACMidiButton::setTag(int tag){
    tagNum = tag;
}

int ACMidiButton::getTag(){
    return tagNum;
}

void ACMidiButton::setPressed(bool bSet){
    bIsPressed = bSet;
}

bool ACMidiButton::isPressed(){
    return bIsPressed;
}

bool ACMidiButton::isSetMidiPressed(){
    return bIsMidiSetPressed;
}

void ACMidiButton::drawPressed(){
    ofSetColor(pressedColor);
    ofFill();
    ofRect(rect);
    

}



void ACMidiButton::drawReleased(){
    ofSetColor(releasedColor);
    ofNoFill();
    ofRect(rect);
}

void ACMidiButton::drawMidiMessage(){
    ofSetColor(255, 0, 0);
    switch (midiMsg.status) {
        case MIDI_NOTE_ON:
            midiStr = ofToString(midiMsg.channel)+"/NO/"+ofToString(midiMsg.pitch);
            
            break;
        case MIDI_CONTROL_CHANGE:
            midiStr = ofToString(midiMsg.channel)+"/CC/"+ofToString(midiMsg.control);
            break;
            
        default:
            break;
    }
    
    msgFont.drawString(midiStr, posX+hMargin, posY + bBox.height +vMargin);
}

void ACMidiButton::draw(){
    if (bIsPressed && midiMode == MIDI_MODE_NORMAL) {
        drawPressed();
    }
    
    ofSetColor(255);
    font.drawString(buttonTitle, posX+hMargin, posY + bBox.height +vMargin);
    
    drawReleased();
    
    if(midiMode == MIDI_MODE_EDIT){

        if (bIsMidiSetPressed) {
            ofSetColor(midiPressedColor);
            ofFill();
            ofRect(rect);
            drawMidiMessage();
        }
        else{
            ofSetColor(midiReleasedColor);
            ofFill();
            ofRect(rect);

        }
        
        
    }
    
}

void ACMidiButton::enableEvents(bool bSet){
    bEnableEvents = bSet;
}

void ACMidiButton::mouseMoved(ofMouseEventArgs& event){
    
}

void ACMidiButton::mouseDragged(ofMouseEventArgs& event){
    
}

void ACMidiButton::mousePressed(ofMouseEventArgs& event){
    bHasFocus = false;
    if (rect.inside(event.x, event.y)) {
        
        bHasFocus = true;
        
        bIsMidiSetPressed = !bIsMidiSetPressed;
        
        if (bToggleButton) {
            bIsPressed = !bIsPressed;
        }
        else{
            bIsPressed = true;
        }
        if(bEnableEvents){
            ofNotifyEvent(pressEvent, bIsPressed);
            ofNotifyEvent(tagEvent, tagNum);
        }
        
        if (bEnableMidiSetEvents) {
            ofNotifyEvent(midiSetPressEvent, bIsMidiSetPressed);
        }
    }
}

void ACMidiButton::mouseReleased(ofMouseEventArgs& event){
    if (bHasFocus) {
        
        if (bToggleButton) {
        }
        else{
            bIsPressed = false;
            if(bEnableEvents){
                ofNotifyEvent(pressEvent, bIsPressed);
            }
        }
        
    }
    bHasFocus = false;
}
