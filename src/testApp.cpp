#include "testApp.h"

testApp::~testApp(){
    midiIn.removeListener(this);
    midiIn.closePort();
    cout<< "testApp terminated" << endl;
}

//--------------------------------------------------------------
void testApp::setup(){
    ofSetDataPathRoot("../Resources/data/");
    ofSetWindowTitle("ANTICLIMAX - Call My Name");
    ofEnableSmoothing();
    
    midiController.setup(&midiIn);
    midiIn.addListener(this);
    
    playButton.setup(300, 20, "PLAY");
    playButton.setPressedColor(ofColor(255,0,0));
    playButton.setReleasedColor(ofColor(255,255,255));
    playButton.setToggle(false, false);
    playButton.setTag(0);
    playButton.setMidiControlType(MIDI_CONTROL_BUTTON);
    ofAddListener(playButton.mousePressEvent, this, &testApp::midiTriggerEventHandler);
    ofAddListener(playButton.midiTriggerEvent, this, &testApp::midiTriggerEventHandler);
    ofAddListener(playButton.midiSetPressEvent, this, &testApp::midiSetButtonEventHandler);
    ofAddListener(playButton.tagEvent, &midiController, &ACMidiController::midiControlTagEventHandler);


    
    
    testButton.setup(500, 20, "KNOB");
    testButton.setPressedColor(ofColor(255,0,0));
    testButton.setReleasedColor(ofColor(255,255,255));
    testButton.setToggle(false, false);
    testButton.setTag(1);
    testButton.setMidiControlType(MIDI_CONTROL_KNOB);
    ofAddListener(testButton.knobValueEvent, this, &testApp::knobValueEventHandler);
    
    
    midiController.addMidiControl(&playButton);
    midiController.addMidiControl(&testButton);
    

    callMyNameController.setup("names/","wav");
    callMyNameController.setPlayerRectSize();
    
    ofSetVerticalSync(true);

}

//--------------------------------------------------------------
void testApp::update(){

    ofSoundUpdate();
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0);

    callMyNameController.draw();
    midiController.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    if (key == ' '){
        callMyNameController.playAll();
    }
    else if (key == 'e'){

        if(midiMode == MIDI_MODE_NORMAL){
            midiMode = MIDI_MODE_EDIT;
        }else
        {
            midiMode = MIDI_MODE_NORMAL;
        }
        
        midiController.setMidiMode(midiMode);
    }
    else if (key =='d'){

    }
    else if (key == 's'){

    }
    else if (key =='f'){
        ofToggleFullscreen();
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

    
    callMyNameController.setPlayerRectSize();

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

void testApp::newMidiMessage(ofxMidiMessage& msg) {
    
	// make a copy of the latest message
	midiMessage = msg;
    /*
    cout<< "status: " << ofxMidiMessage::getStatusString(midiMessage.status) << endl;
    cout<< "channel: " << midiMessage.channel << endl;
    cout<< "pitch: " << midiMessage.pitch << endl;
    cout<< "velocity: " << midiMessage.velocity << endl;
    cout<< "control: " << midiMessage.control << endl;
    cout<< "value: " << midiMessage.value << endl;
    */
    if (midiMode == MIDI_MODE_EDIT) {
        if (playButton.isSetMidiPressed()) {
            playButton.setMidiMessage(midiMessage);
        }
        
        if (testButton.isSetMidiPressed()) {
            testButton.setMidiMessage(midiMessage);
        }
    }
    else{
        playButton.triggerMidiEvent(midiMessage);
        testButton.triggerMidiEvent(midiMessage);
    }

}



void testApp::midiSetButtonEventHandler(bool &bPress){
    if (bPress) {
        
        cout << "midi set" << endl;
    }
    else{
        
    }
}

void testApp::midiTriggerEventHandler(bool &bPress){
    if(bPress){
        cout << "play" << endl;
    }
    else{
        cout << "stop" << endl;
    }
}

void testApp::knobValueEventHandler(int &val){
    cout << val << endl;
    testButton.setTitle(ofToString(val));
}


