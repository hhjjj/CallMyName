#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxMidi.h"
#include "ofxFontStash.h"
#include "ofxOsc.h"

#include "CallMyNamePlayer.h"
#include "CallMyNameController.h"
#include "ACMidiController.h"


//class testApp : public ofBaseApp , public ofxMidiListener{
class testApp : public ofBaseApp {

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    CallMyNameController callMyNameController;
    ACMidiController midiController;
    MidiModeType midiMode;
    
//    ofxMidiIn midiIn;
//	ofxMidiMessage midiMessage;

};
