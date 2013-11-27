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
    cout<< "midicontroller terminated" << endl;
//    midiIn->closePort();
//    midiIn.removeListener(this);
    //ofRemoveListener(ofEvents().draw, this, &ACMidiController::draw);
    ofRemoveListener(midiPortListOpenButton.mousePressEvent, this, &ACMidiController::openPortEventHandler);
//    for ( int i = 0; i < midiControlItem.size();i++){
//        ofRemoveListener(midiControlItem[i]->tagEvent, this, &ACMidiController::midiControlTagEventHandler);
//    }

}

void ACMidiController::setup(float x, float y, ofxMidiIn *midi) {
    posX = x;
    posY = y;
    midiIn = midi;
    font.loadFont("NewMedia Fett.ttf", 18);
    
    midiIn->ignoreTypes(true, true, true);
    
    midiPortListOpenButton.setup(posX, posY, "OPEN MIDI PORTS");
    midiPortListOpenButton.setPressedColor(ofColor(255,0,0));
    midiPortListOpenButton.setReleasedColor(ofColor(255,255,255));
    midiPortListOpenButton.setToggle(true, false);
    

    
//    midiIn.addListener(this);
    ofAddListener(midiPortListOpenButton.mousePressEvent, this, &ACMidiController::openPortEventHandler);
    //ofAddListener(ofEvents().draw, this, &ACMidiController::draw);
    setMidiMode(MIDI_MODE_NORMAL);
}

void ACMidiController::addMidiControl(ACMidiButton* midiControl){
//    ofAddListener(midiControl->tagEvent, this, &ACMidiController::midiControlTagEventHandler);
    midiControlItem.push_back(midiControl);
}

void ACMidiController::setMidiMode(MidiModeType type){
    midiMode = type;
}


void ACMidiController::showMidiPorts(){
    vector<string> ports = midiIn->getPortList();
    
}



void ACMidiController::openPort(string deviceName){
    midiIn->openPort(deviceName);
}

void ACMidiController::closePorts(){
    midiIn->closePort();
}

//void ACMidiController::newMidiMessage(ofxMidiMessage& msg) {
//    
//	// make a copy of the latest message
//	midiMessage = msg;
//    
////    cout<< "status: " << ofxMidiMessage::getStatusString(midiMessage.status) << endl;
////    cout<< "channel: " << midiMessage.channel << endl;
////    cout<< "pitch: " << midiMessage.pitch << endl;
////    cout<< "velocity: " << midiMessage.velocity << endl;
////    cout<< "control: " << midiMessage.control << endl;
////    cout<< "value: " << midiMessage.value << endl;
//    
//    
////    if (midiMessage.control == 55) {
////        if(midiMessage.value > 64){
////            playButton.setPressed(true);
////            cout << "play" << endl;
////        }
////        else{
////            playButton.setPressed(false);
////            cout << "stop" << endl;
////        }
////    }
//
////    if (midiMode == MIDI_MODE_EDIT) {
////        if (playButton.isSetMidiPressed()) {
////            playButton.setMidiMessage(midiMessage);
////        }
////    }
////    else{
////        playButton.triggerMidiEvent(midiMessage);
////    }
//    
//
//}

void ACMidiController::draw(){

    midiPortListOpenButton.draw();
//    playButton.setMidiMode(midiMode);
//    playButton.draw();
    
    for (int i = 0 ; i < midiControlItem.size(); i ++){
        midiControlItem[i]->setMidiMode(midiMode);
        midiControlItem[i]->draw();
    }
    
    if(midiPortListOpenButton.isPressed()){
        for (int i = 0; i < lists.size(); i++) {

            lists[i]->draw();
        }
    }
}
string ACMidiController::getCurrentMidiPort(){
    return midiIn->getName();
}
//void  ACMidiController::draw(ofEventArgs& event){
//
//}

void ACMidiController::openPortEventHandler(bool &bPress){
    if (bPress) {
        cout << "open midi ports" << endl;
        portLists = midiIn->getPortList();
        cout<< "set size: " << portLists.size() << endl;
        for (int i = 0; i < portLists.size(); i++) {

            
            
            
//            ACMidiButton *button = new ACMidiButton();
//            
//            button->setup(20, 30+30+30*i, portLists[i]);
//            button->setTitle(portLists[i]);
//            button->setPressedColor(ofColor(255,0,0));
//            button->setReleasedColor(ofColor(255,255,255));
//            button->setToggle(true, false);
//            button->setTag(i);
//            ofAddListener(button->tagEvent, this, &ACMidiController::portButtonEventHandler);
//            lists.push_back(button);
            
            lists.push_back(new ACMidiButton());
            
            lists[i]->setup(posX, posY+30+30*i, portLists[i]);
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
            ofRemoveListener(lists[i]->tagEvent, this, &ACMidiController::portButtonEventHandler);
            // delete manually!!!!!
            delete lists[i];
            
        }
        // important!!!!
        lists.clear();
    }
}

void ACMidiController::portButtonEventHandler(int &tag){
    if(lists[tag]->isPressed()){
        cout << "port number: " << tag << " chosen" <<endl;
        openPort(portLists[tag]);
    }
    else{
        cout << "port closed" <<endl;
        midiIn->closePort();
    }

    for (int i = 0; i < lists.size(); i++) {
        if( i != tag){
            lists[i]->setPressed(false);
        }
        
    }
}

//void ACMidiController::controlButtonEventHandler(int &tag){
//    switch (tag) {
//        case 0:
//            cout << "play" << endl;
//            break;
//            
//        default:
//            break;
//    }
//}
//
//void ACMidiController::midiSetButtonEventHandler(bool &bPress){
//    if (bPress) {
//
//        cout << "midi set" << endl;
//    }
//    else{
//        
//    }
//}
//
//void ACMidiController::midiTriggerEventHandler(bool &bPress){
//    if(bPress){
//        cout << "play" << endl;
//    }
//    else{
//        cout << "stop" << endl;
//    }
//}

void ACMidiController::midiControlTagEventHandler(int &tag){
    cout<< tag << endl;
}

