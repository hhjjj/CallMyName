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
}

void ACMidiController::setup() {
    midiIn.ignoreTypes(true, true, true);
    // add testApp as a listener
    midiIn.addListener(this);
    
    gui = new ofxUICanvas();

    //gui->addButton("Open MIDI Lists", false);
    //gui->addLabel("MIDI Ports",OFX_UI_FONT_MEDIUM);
    //gui->addSpacer();
//    gui->addLabelButton("Open MIDI Lists", false, true);
//    gui->setDrawWidgetPadding(true);
    
    ddl = gui->addDropDownList("Open MIDI Ports", portLists);
    ddl->setAllowMultiple(false);
    
    gui->autoSizeToFitWidgets();
    

    
    ofAddListener(gui->newGUIEvent, this, &ACMidiController::guiEvent);
    ofAddListener(ofEvents().draw, this, &ACMidiController::draw);
    
    gui->setColorBack(ofColor(255,100));
    gui->setWidgetColor(OFX_UI_WIDGET_COLOR_BACK, ofColor(255,100));
    
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
    
}

void ACMidiController::guiEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
    int kind = e.widget->getKind();
    
    cout << "WIDGET NAME: " << name << endl;
    
    if( name == "Open MIDI Ports"){
        portLists.clear();
        vector<string> p = midiIn.getPortList();
        ofLogNotice(ofToString(p.size()));
        for (int i = 0 ; i < p.size(); i++){
            ddl->addToggle(p[i]);
        }
    }
    
//    if(name == "DDL SHOW ACTIVE ITEM")
//    {
//        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
//        ddl->setShowCurrentSelected(toggle->getValue());
//    }
//    else if(name == "DYNAMIC DROP DOWN")
//    {
//        ofxUIDropDownList *ddlist = (ofxUIDropDownList *) e.widget;
//        vector<ofxUIWidget *> &selected = ddlist->getSelected();
//        for(int i = 0; i < selected.size(); i++)
//        {
//            cout << "SELECTED: " << selected[i]->getName() << endl;
//        }
//    }
}