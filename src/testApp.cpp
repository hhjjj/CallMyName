#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetDataPathRoot("../Resources/data/");
    ofSetWindowTitle("ANTICLIMAX - Call My Name");
    ofEnableSmoothing();
    
    midiController.setup();

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

//void testApp::newMidiMessage(ofxMidiMessage& msg) {
//    
//	// make a copy of the latest message
//	midiMessage = msg;
//}
