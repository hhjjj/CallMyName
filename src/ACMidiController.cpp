//
//  ACMidiController.cpp
//  CallMyName
//
//  Created by hojun on 11/26/13.
//
//

#include "ACMidiController.h"

ACMidiController::ACMidiController(){
}

ACMidiController::~ACMidiController(){
    midiIn.closePort();
    midiIn.removeListener(this);
    ofRemoveListener(ofEvents().draw, this, &ACMidiController::draw);
    ofRemoveListener(midiPortListOpenButton.pressEvent, this, &ACMidiController::buttonEventHandler);

}

void ACMidiController::setup() {
    
    font.loadFont("NewMedia Fett.ttf", 29);
    
    midiIn.ignoreTypes(true, true, true);
    
    midiPortListOpenButton.setup(20, 20, "OPEN MIDI PORTS");
    midiPortListOpenButton.setPressedColor(ofColor(255,0,0));
    midiPortListOpenButton.setReleasedColor(ofColor(255,255,255));
    
    
    midiIn.addListener(this);
    ofAddListener(midiPortListOpenButton.pressEvent, this, &ACMidiController::buttonEventHandler);
    ofAddListener(ofEvents().draw, this, &ACMidiController::draw);
}

void ACMidiController::showMidiPorts(){
    vector<string> ports = midiIn.getPortList();
    
}



void ACMidiController::openPort(string deviceName){
    midiIn.openPort(deviceName);
}

void ACMidiController::closePorts(){
    midiIn.closePort();
}

void ACMidiController::newMidiMessage(ofxMidiMessage& msg) {
    
	// make a copy of the latest message
	midiMessage = msg;
}

void  ACMidiController::draw(ofEventArgs& event){
    
    midiPortListOpenButton.draw();
    for (int i = 0; i < portLists.size(); i++) {
        portListButtons[i]->draw();
    }
}

void ACMidiController::buttonEventHandler(bool &bPress){
    if (bPress) {
        portLists.clear();
        portListButtons.clear();
        portLists = midiIn.getPortList();
        for (int i = 0; i < portLists.size(); i++) {
            
            // How can i create buttons in real time
            // that can react to mouse event?
            ACMidiButton button;
            button.setup(20, 20 + 40*i, portLists[i]);
            button.setPressedColor(ofColor(255,0,0));
            button.setReleasedColor(ofColor(255,255,255));
            portListButtons.push_back(&button);
            


        }
    }
}
