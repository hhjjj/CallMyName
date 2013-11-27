//
//  ACMidiSlider.cpp
//  CallMyName
//
//  Created by hojun on 11/28/13.
//
//

#include "ACMidiSlider.h"

ACMidiSlider::ACMidiSlider(){
    
}

ACMidiSlider::~ACMidiSlider(){
    if(bWasSetup){
        ofUnregisterMouseEvents(this);
    }
	bWasSetup = false;
    
}

void ACMidiSlider::setup(float x, float y, string title){
    bWasSetup = false;
    bHasFocus = false;
    bIsMidiSetPressed = false;
    bIsDragged = false;
    bEnableEvents = true;
    bEnableMidiSetEvents = false;
    
    
    mouseX = -1000.0;
    mouseY = -1000.0;
    startMouseX = -1000;
    startMouseY = -1000;
    
    
    dragX = 0.0;
    dragY = 0.0;
    
    
    midiStr = "";
    
    buttonTitle = title;
    
    tagNum = 0;
    
    fontSize = 18;
    msgFontSize = 12;
    
    font.loadFont("NewMedia Fett.ttf", fontSize);
    msgFont.loadFont("NewMedia Fett.ttf", msgFontSize);
    
    posX = x;
    posY = y;
    
    sliderVal = 0.0;
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
}


ofRectangle ACMidiSlider::getRect(){
    return rect;
}

void ACMidiSlider::setSliderColor(ofColor c){
    sliderColor = c;
}

void ACMidiSlider::setBarColor(ofColor c){
    barColor = c;
}

void ACMidiSlider::setTitle(string title){
    buttonTitle = title;
//    bBox = font.getStringBoundingBox(buttonTitle, posX, posY);
//    rect = ofRectangle(posX, posY, bBox.width+hMargin *2, bBox.height + vMargin * 2);
}

string ACMidiSlider::getTitle(){
    return buttonTitle;
}

void ACMidiSlider::setPosition(float x, float y){
    posX = x;
    posY = y;
    bBox = font.getStringBoundingBox(buttonTitle, posX, posY);
    rect = ofRectangle(posX, posY, bBox.width+hMargin *2, bBox.height + vMargin * 2);
}

void ACMidiSlider::setSize(float w){
    
    bBox = font.getStringBoundingBox(buttonTitle, posX, posY);
    rect = ofRectangle(posX, posY, w+hMargin *2, bBox.height + vMargin * 2);
}




void ACMidiSlider::setMidiMode(MidiModeType type){
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


MidiModeType ACMidiSlider::getMidiMode(){
    return midiMode;
}

void ACMidiSlider::setMidiMessage(ofxMidiMessage msg){
    midiMsg = msg;
}

ofxMidiMessage ACMidiSlider::getMidiMessage(){
    return midiMsg;
}

void ACMidiSlider::triggerMidiEvent(ofxMidiMessage msg){
    switch (msg.status) {
        case MIDI_NOTE_ON:
            if (msg.pitch == midiMsg.pitch) {
            }
            
            break;
        case MIDI_NOTE_OFF:
            if (msg.pitch == midiMsg.pitch) {
            }
            break;
        case MIDI_CONTROL_CHANGE:
            if (msg.control == midiMsg.control) {
                sliderVal =(rect.width/128.0 )* msg.value;
                ofNotifyEvent(knobValueEvent, msg.value);

            }
            
            break;
            
        default:
            break;
    }
}

void ACMidiSlider::setTag(int tag){
    tagNum = tag;
}

int ACMidiSlider::getTag(){
    return tagNum;
}

bool ACMidiSlider::isSetMidiPressed(){
    return bIsMidiSetPressed;
}

void ACMidiSlider::drawMidiMessage(){
    ofSetColor(255, 0, 0);
    switch (midiMsg.status) {
        case MIDI_NOTE_ON:
            midiStr = "";
            
            break;
        case MIDI_CONTROL_CHANGE:
            midiStr = ofToString(midiMsg.channel)+"/CC/"+ofToString(midiMsg.control);
            break;
            
        default:
            break;
    }
    
    msgFont.drawString(midiStr, posX+hMargin, posY + bBox.height +vMargin);
}

void ACMidiSlider::draw(){
    if (midiMode == MIDI_MODE_NORMAL) {
        ofSetColor(sliderColor);
        ofNoFill();
        ofRect(rect);
        ofSetColor(barColor);
        ofFill();
        // only when valute is available
  
        ofRect(ofRectangle(posX, posY, sliderVal ,bBox.height + vMargin * 2));
    }
    
    ofSetColor(255);
    font.drawString(buttonTitle, posX+hMargin, posY + bBox.height +vMargin);
    
    
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

void ACMidiSlider::enableEvents(bool bSet){
    bEnableEvents = bSet;
}

void ACMidiSlider::updateBarPos(float x, float y){
    
    x = x -posX;
    if(x > 0 && x < rect.width)
    {
        sliderVal = x;
    }
    else if (x < 0){
        sliderVal = 0;
    }
    else if ( x > rect.width){
        sliderVal = rect.width;
    }
    int val = (int)ofMap(sliderVal, 0, rect.width, 0, 127);
    ofNotifyEvent(knobValueEvent, val);
}


void ACMidiSlider::mouseMoved(ofMouseEventArgs& event){
    bHasFocus = false;
}

void ACMidiSlider::mouseDragged(ofMouseEventArgs& event){
    if(bHasFocus){
        dragX = event.x - startMouseX;
        dragY = event.y - startMouseY;
        bIsDragged = true;
//        cout << "drag x:" <<dragX << endl;
//        sliderVal = (rect.width/128.0 ) *(int)(ofMap(dragX, -ofGetWidth()/6, ofGetWidth()/6, 0, 127));
//        if (sliderVal < 0) sliderVal = 0;
//        if (sliderVal > rect.width) sliderVal = rect.width;
        updateBarPos(event.x, event.y);
    }

}

void ACMidiSlider::mousePressed(ofMouseEventArgs& event){
    bHasFocus = false;
    if (rect.inside(event.x, event.y)) {
        
        bHasFocus = true;
        
        updateBarPos(event.x, event.y);
        
        bIsMidiSetPressed = !bIsMidiSetPressed;
        

        
        startMouseX = event.x;
        startMouseY = event.y;
        
        if(bEnableEvents){
            ofNotifyEvent(tagEvent, tagNum);
        }
        
        if (bEnableMidiSetEvents) {
            ofNotifyEvent(midiSetPressEvent, bIsMidiSetPressed);
        }
    }
}

void ACMidiSlider::mouseReleased(ofMouseEventArgs& event){
    if (bHasFocus) {
        if (rect.inside(event.x, event.y)) {
            updateBarPos(event.x, event.y);
        }
        bIsDragged = false;
        dragX = 0.0;
        dragY = 0.0;
    }
    bHasFocus = false;
}
