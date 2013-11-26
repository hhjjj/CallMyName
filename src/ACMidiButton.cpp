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
    bIsDragged = false;
    bToggleButton = false;

    buttonTitle = title;
    
    tagNum = 0;
    
    fontSize = 18;
    font.loadFont("NewMedia Fett.ttf", fontSize);
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

void ACMidiButton::draw(){
    
    if (bIsPressed) {
        drawPressed();
    }
    
    drawReleased();
    ofSetColor(255);
    font.drawString(buttonTitle, posX+hMargin, posY + bBox.height +vMargin);
    
}

void ACMidiButton::mouseMoved(ofMouseEventArgs& event){
    
}

void ACMidiButton::mouseDragged(ofMouseEventArgs& event){
    
}

void ACMidiButton::mousePressed(ofMouseEventArgs& event){
    bHasFocus = false;
    if (rect.inside(event.x, event.y)) {
        
        bHasFocus = true;
        
        if (bToggleButton) {
            bIsPressed = !bIsPressed;
        }
        else{
            bIsPressed = true;
        }
        ofNotifyEvent(pressEvent, bIsPressed);
    }
}

void ACMidiButton::mouseReleased(ofMouseEventArgs& event){
    if (bHasFocus) {
        
        if (bToggleButton) {
        }
        else{
            bIsPressed = false;
        }
        
    }
    bHasFocus = false;
}
