#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetWindowTitle("ANTICLIMAX - Call My Name");
    fileCount = 0;
    string path = "";
    dir.allowExt("wav");
    dir.listDir("names/");
    dir.sort();
    fileCount = dir.numFiles();
    ofLogNotice("fileCount: "+ofToString(fileCount));
    
    
    callMyNamePlayer.reserve(fileCount);
    callMyNamePlayer.clear();
    
    for (int i = 0 ; i < fileCount ; i++){
//        ofLogNotice(dir.getName(i));
//        CallMyNamePlayer player;
//        player.setup("names/"+ofToString(i+1)+".wav");
//        callMyNamePlayer.push_back(player);
        
        CallMyNamePlayer player;
        callMyNamePlayer.push_back(player);
        callMyNamePlayer[i].setup(ofFilePath::getAbsolutePath("names/"+ofToString(i+1)+".wav"));


    }
    
    int numOfCol = 10;
    int numOfRow = (int)ceil(fileCount / 10);
    ofLogNotice(ofToString(numOfRow));
    float hMargin = 10;
    float vMargin = 10;
    float w = (ofGetWidth()- (numOfCol + 2) * hMargin) / (numOfCol);
    float h = (ofGetHeight()- (numOfRow + 2) * vMargin) / (numOfRow);
    ofLogNotice("h");
    ofLogNotice(ofToString(h));
    
    //for (int i = 0 ; i < callMyNamePlayer.size() ; i++){

    for (int i  = 0; i < numOfRow; i++) {
        for ( int j = 0; j < numOfCol; j++){
            
            callMyNamePlayer[i *numOfCol + j].setRect(hMargin*(j+1) + j*w, vMargin*(i+1) + i*h, w, h, ofColor(255, 0 , 0));

        }
    }
    
        
    //}
    
    counter = 0;
    ofSetVerticalSync(true);
//    ofLogNotice("setup");
}

//--------------------------------------------------------------
void testApp::update(){

    ofSoundUpdate();
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0);


//    ofLogNotice("draw");
    for (int i = 0 ; i < callMyNamePlayer.size() ; i++){
        callMyNamePlayer[i].draw();
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    if (key == ' '){
        for (int i = 0; i < callMyNamePlayer.size(); i++) {
//            callMyNamePlayer[i].play();
            callMyNamePlayer[i].playAfterMs(i*70);
        }
    }
    else if (key == 'a'){

        callMyNamePlayer[0].play();
    }
    else if (key =='d'){

        callMyNamePlayer[counter].play();
        ofLogNotice(ofToString(counter));
        counter++;
    }
    else if (key == 's'){
        callMyNamePlayer[0].playAfterMs(1000);
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
    ofLogNotice(ofToString(ofGetWidth()));
    int numOfCol = 10;
    int numOfRow = (int)ceil(fileCount / 10);
    ofLogNotice(ofToString(numOfRow));
    float hMargin = 10;
    float vMargin = 10;
    float _w = (ofGetWidth()- (numOfCol + 2) * hMargin) / (numOfCol);
    float _h = (ofGetHeight()- (numOfRow + 2) * vMargin) / (numOfRow);
    ofLogNotice("h");
    ofLogNotice(ofToString(h));
    
    //for (int i = 0 ; i < callMyNamePlayer.size() ; i++){
    
    for (int i  = 0; i < numOfRow; i++) {
        for ( int j = 0; j < numOfCol; j++){
            
            callMyNamePlayer[i *numOfCol + j].setRect(hMargin*(j+1) + j*_w, vMargin*(i+1) + i*_h, _w, _h, ofColor(255, 0 , 0));
            
        }
    }

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
