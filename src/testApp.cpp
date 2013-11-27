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
    ofAddListener(playButton.mousePressEvent, this, &testApp::playButtonEventHandler);
    ofAddListener(playButton.midiTriggerEvent, this, &testApp::playButtonEventHandler);

    
    playNumSlider.setup(300, 50, "PLAY NUM");
    playNumSlider.setSize(200);
    playNumSlider.setSliderColor(ofColor(255,255,255));
    playNumSlider.setBarColor(ofColor(255,0,0));
    ofAddListener(playNumSlider.knobValueEvent, this, &testApp::playNumEventHandler);

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
    
    playButton.setMidiMode(midiMode);
    playButton.draw();
    
    playNumSlider.setMidiMode(midiMode);
    playNumSlider.draw();
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
        

        if (playNumSlider.isSetMidiPressed()) {
            playNumSlider.setMidiMessage(midiMessage);
        }
    }
    else{
        playButton.triggerMidiEvent(midiMessage);
        playNumSlider.triggerMidiEvent(midiMessage);

    }

}


void testApp::playButtonEventHandler(bool &bPress){
    if(bPress){
        cout << "play" << endl;
    }
    else{
        cout << "stop" << endl;
    }
}

void testApp::delayValueEventHandler(int &val){
    cout << val << endl;
}

void testApp::playNumEventHandler(int &val){
    cout << val << endl;
}
