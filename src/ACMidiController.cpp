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
    //ofRemoveListener(ofEvents().draw, this, &ACMidiController::draw);
    ofRemoveListener(midiPortListOpenButton.pressEvent, this, &ACMidiController::openPortEventHandler);
    for (int i = 0; i < numOfShowPortList; i++) {
        ofRemoveListener(portListButtons[i].tagEvent, this, &ACMidiController::portButtonEventHandler);
    }
}

void ACMidiController::setup() {
    
    font.loadFont("NewMedia Fett.ttf", 29);
    
    midiIn.ignoreTypes(true, true, true);
    
    midiPortListOpenButton.setup(20, 20, "OPEN MIDI PORTS");
    midiPortListOpenButton.setPressedColor(ofColor(255,0,0));
    midiPortListOpenButton.setReleasedColor(ofColor(255,255,255));
    midiPortListOpenButton.setToggle(true, false);
    
    
    for (int i = 0; i < numOfShowPortList; i++) {
        portListButtons[i].setup(20, 20, "");
        portListButtons[i].setPressedColor(ofColor(255,0,0));
        portListButtons[i].setReleasedColor(ofColor(255,255,255));
        portListButtons[i].setToggle(true, false);
        portListButtons[i].setTag(i);
        ofAddListener(portListButtons[i].tagEvent, this, &ACMidiController::portButtonEventHandler);
    }
    
    
    midiIn.addListener(this);
    ofAddListener(midiPortListOpenButton.pressEvent, this, &ACMidiController::openPortEventHandler);
    //ofAddListener(ofEvents().draw, this, &ACMidiController::draw);
    
    midiMode = MIDI_MODE_NORMAL;
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
    
    ofLogNotice("new message!!");
}
void ACMidiController::draw(){
    midiPortListOpenButton.setMidiMode(midiMode);
    midiPortListOpenButton.draw();
    
    if(midiPortListOpenButton.isPressed()){
//        for (int i = 0; i < numOfShowPortList; i++) {
        for (int i = 0; i < lists.size(); i++) {

//            portListButtons[i].enableEvents(true);
//            portListButtons[i].draw();
            lists[i]->draw();
        }
    }
    else{
        for (int i = 0; i < numOfShowPortList; i++) {
//            portListButtons[i].enableEvents(false);
        }
    }
}

//void  ACMidiController::draw(ofEventArgs& event){
//
//}

void ACMidiController::openPortEventHandler(bool &bPress){
    if (bPress) {
        cout << "open midi ports" << endl;
        portLists = midiIn.getPortList();
//        for (int i = 0; i < numOfShowPortList; i++) {
        cout<< "set size: " << portLists.size() << endl;
        for (int i = 0; i < portLists.size(); i++) {
//            portListButtons[i].setTitle(portLists[i]);
//            portListButtons[i].setPosition(20, 30 + 30 +30*i);
            
            
            
//            ACMidiButton *button = new ACMidiButton();
//            
//            button->setup(20, 30+30+30*i, portLists[i]);
//            button->setTitle(portLists[i]);
//            button->setPressedColor(ofColor(255,0,0));
//            button->setReleasedColor(ofColor(255,255,255));
//            button->setToggle(true, false);
//            button->setTag(i);
//            ofAddListener(button->tagEvent, this, &ACMidiController::portButtonEventHandler);
//            
//            lists.push_back(button);
            
            lists.push_back(new ACMidiButton());
            
            lists[i]->setup(20, 30+30+30*i, portLists[i]);
            lists[i]->setTitle(portLists[i]);
            lists[i]->setPressedColor(ofColor(255,0,0));
            lists[i]->setReleasedColor(ofColor(255,255,255));
            lists[i]->setToggle(true, false);
            lists[i]->setTag(i);
            ofAddListener(lists[i]->tagEvent, this, &ACMidiController::portButtonEventHandler);
        }
    }
    else{
        portLists.clear();
        cout << "free size:" << lists.size() << endl;
        
        for (int i = 0; i < lists.size(); i++) {
            //            portListButtons[i].setTitle(portLists[i]);
            //            portListButtons[i].setPosition(20, 30 + 30 +30*i);
            ofRemoveListener(lists[i]->tagEvent, this, &ACMidiController::portButtonEventHandler);
            delete lists[i];
            
        }
        lists.clear();
    }
}

void ACMidiController::portButtonEventHandler(int &tag){
    
    
    
//    if(portListButtons[tag].isPressed()){
//        cout << "port number: " << tag << " chosen" <<endl;
//        openPort(portLists[tag]);
//    }
//    else{
//        cout << "port closed" <<endl;
//        midiIn.closePort();
//    }
//    
//    for (int i = 0; i < numOfShowPortList; i++) {
//        if( i != tag){
//            portListButtons[i].setPressed(false);
//        }
//        
//    }
    if(lists[tag]->isPressed()){
        cout << "port number: " << tag << " chosen" <<endl;
        openPort(portLists[tag]);
    }
    else{
        cout << "port closed" <<endl;
        midiIn.closePort();
    }
    
    cout << "tag:" << tag << endl;
    cout << "list size:" << lists.size() << endl;
    for (int i = 0; i < lists.size(); i++) {
        if( i != tag){
            lists[i]->setPressed(false);
        }
        
    }
}