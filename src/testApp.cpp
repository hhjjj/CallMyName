#include "testApp.h"

testApp::~testApp(){
    midiIn.removeListener(this);
    midiIn.closePort();
    cout<< "testApp terminated" << endl;
}

//--------------------------------------------------------------
void testApp::setup(){
    ofSetDataPathRoot("../Resources/data/");
    ofSetWindowTitle("ANTICLIMAX");
    ofEnableSmoothing();
    

    
    playButton.setup(300, 5, "PLAY");
    playButton.setPosition(300, 5);
    playButton.setPressedColor(ofColor(255,0,0));
    playButton.setReleasedColor(ofColor(255,255,255));
    playButton.setToggle(false, false);
    ofAddListener(playButton.mousePressEvent, this, &testApp::playButtonEventHandler);
    ofAddListener(playButton.midiTriggerEvent, this, &testApp::playButtonEventHandler);
    
    stopAllButton.setup(300 + playButton.getButtonRect().width + 5, 5, "STOP ALL");
    stopAllButton.setPosition(300+ playButton.getButtonRect().width + 5, 5);
//stopAllButton.setPosition(300+ playButton.getButtonRect().width + 5, -playButton.getButtonRect().height/2 + 60/2+5);
    stopAllButton.setPressedColor(ofColor(255,0,0));
    stopAllButton.setReleasedColor(ofColor(255,255,255));
    stopAllButton.setToggle(false, false);
    ofAddListener(stopAllButton.mousePressEvent, this, &testApp::stopAllButtonEventHandler);
    ofAddListener(stopAllButton.midiTriggerEvent, this, &testApp::stopAllButtonEventHandler);

    
    playNumSlider.setup(300 + stopAllButton.getButtonRect().width + playButton.getButtonRect().width + 5 + 30, 5, "MANY: ");
    playNumSlider.setSize(200);
    playNumSlider.setSliderColor(ofColor(255,255,255));
    playNumSlider.setBarColor(ofColor(255,0,0));
    ofAddListener(playNumSlider.knobValueEvent, this, &testApp::playNumEventHandler);
    
    
    delaySlider.setup(300 + stopAllButton.getButtonRect().width + playButton.getButtonRect().width + 5 + 30,
                      playNumSlider.getRect().y+playNumSlider.getRect().height+ 5, "DELAY: ");
    delaySlider.setSize(200);
    delaySlider.setSliderColor(ofColor(255,255,255));
    delaySlider.setBarColor(ofColor(255,0,0));
    ofAddListener(delaySlider.knobValueEvent, this, &testApp::delayValueEventHandler);
    
    
    swingOnButton.setup(300 + stopAllButton.getButtonRect().width + playButton.getButtonRect().width + 5 + 30 +30 + delaySlider.getRect().width
                        , playNumSlider.getRect().y+playNumSlider.getRect().height+ 5, "SWING");
    swingOnButton.setPressedColor(ofColor(255,0,0));
    swingOnButton.setReleasedColor(ofColor(255,255,255));
    swingOnButton.setToggle(true, false);
    ofAddListener(swingOnButton.mousePressEvent, this, &testApp::swingOnButtonEventHandler);
    ofAddListener(swingOnButton.midiTriggerEvent, this, &testApp::swingOnButtonEventHandler);
    
    

    midiController.setup(10,5,&midiIn);
    midiIn.addListener(this);
    
    callMyNameController.setup("names/","wav");
    callMyNameController.setPlayerRectSize();
    
    ofSetVerticalSync(true);
    
    playMany = 1;
    playDelay = 70;

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
    
    stopAllButton.setMidiMode(midiMode);
    stopAllButton.draw();
    
    delaySlider.setMidiMode(midiMode);
    delaySlider.draw();
    
    swingOnButton.setMidiMode(midiMode);
    swingOnButton.draw();
    
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
        if (stopAllButton.isSetMidiPressed()) {
            stopAllButton.setMidiMessage(midiMessage);
        }
        
        if (swingOnButton.isSetMidiPressed()) {
            swingOnButton.setMidiMessage(midiMessage);
        }
        
        if (delaySlider.isSetMidiPressed()) {
            delaySlider.setMidiMessage(midiMessage);
        }

        if (playNumSlider.isSetMidiPressed()) {
            playNumSlider.setMidiMessage(midiMessage);
        }
    }
    else{
        playButton.triggerMidiEvent(midiMessage);
        stopAllButton.triggerMidiEvent(midiMessage);
        swingOnButton.triggerMidiEvent(midiMessage);
        delaySlider.triggerMidiEvent(midiMessage);
        playNumSlider.triggerMidiEvent(midiMessage);

    }

}


void testApp::playButtonEventHandler(bool &bPress){
    if(bPress){
        cout << "play" << endl;
        callMyNameController.play();
    }
    else{

    }
}
void testApp::stopAllButtonEventHandler(bool &bPress){
    if(bPress){
        callMyNameController.stopAll();
    }
}

void testApp::delayValueEventHandler(int &val){

    cout << "delay val: " << val << endl;
    playDelay = (int)ofMap(val,0,127,70,2000);
    delaySlider.setTitle("DELAY: "+ofToString(playDelay)+" ms");
    cout << "play delay: " << playDelay << endl;
    callMyNameController.setPlayDelay(playDelay);
}

void testApp::playNumEventHandler(int &val){
    cout << "play num: " << val << endl;
    playMany = (int)ofMap(val, 0, 127, 1, callMyNameController.getFileCount());
    playNumSlider.setTitle("MANY: " + ofToString(playMany) );
    cout << "play Count: " << playMany << endl;
    callMyNameController.setPlayMany(playMany);
}

void testApp::swingOnButtonEventHandler(bool &bPress){
    if (bPress) {
        callMyNameController.setSwingOn(true);
    }
    else{
        callMyNameController.setSwingOn(false);
    }
}
