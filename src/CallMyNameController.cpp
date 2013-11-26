//
//  CallMyNameController.cpp
//  CallMyName
//
//  Created by hojun on 11/26/13.
//
//

#include "CallMyNameController.h"

CallMyNameController::CallMyNameController(){
    
}

CallMyNameController::~CallMyNameController(){
    
}

void CallMyNameController::setup(string folderPath, string allowableExt){

    fileCount = 0;
    
    fileDirectory.allowExt(allowableExt);
    fileDirectory.listDir(folderPath);
    fileDirectory.sort();
    
    fileCount = fileDirectory.numFiles();
    
    ofLogNotice("fileCount");
    ofLogNotice(ofToString(fileCount));
    
    callMyNamePlayer.reserve(fileCount);
    callMyNamePlayer.clear();
    


    
    for (int i = 0 ; i < fileCount ; i++){
        CallMyNamePlayer player;
        callMyNamePlayer.push_back(player);
        callMyNamePlayer[i].setup(ofFilePath::getAbsolutePath(fileDirectory.getPath(i)));
//        ofLogNotice(ofFilePath::getAbsolutePath(fileDirectory.getPath(i)));
//        addPlayer(ofFilePath::getAbsolutePath(fileDirectory.getPath(i)));
    }
    
    playOrder.reserve(callMyNamePlayer.size());
    playOrder.clear();
    
    for (int i = 0; i < callMyNamePlayer.size(); i++){
        playOrder.push_back(i);
    }
    shufflePlayOrder();
    
    ofLogNotice("stop");
}

// this is not working i think it's because you ofSoundPlayer and Vector copy is not working
//void CallMyNameController::addPlayer(string filePath){
//    CallMyNamePlayer player;
//    player.setup(filePath);
//    callMyNamePlayer.push_back(player);
//}

void CallMyNameController::draw(){
    for (int i = 0 ; i < callMyNamePlayer.size() ; i++){
        callMyNamePlayer[i].draw();
    }
}

void CallMyNameController::setPlayerRectSize(){
    int numOfCol = 10;
    int numOfRow = (int)ceil((float)callMyNamePlayer.size() / (float)numOfCol);
    ofLogNotice("real row");
    ofLogNotice(ofToString(numOfRow));
    // check remainder is left
    
    float hMargin = 10;
    float vMargin = 10;
    float w = (ofGetWidth()- (numOfCol + 2) * hMargin) / (numOfCol);
    float h = (ofGetHeight()- (numOfRow + 2) * vMargin) / (numOfRow);

    
    
    //int remainder =((numOfCol * numOfRow) % callMyNamePlayer.size());
    
    int remainder = (callMyNamePlayer.size() % numOfCol);
    
    if ( remainder != 0) {
        numOfRow = numOfRow - 1;
        ofLogNotice("remainder");
        ofLogNotice(ofToString(remainder));
        ofLogNotice("row");
        ofLogNotice(ofToString(numOfRow));
    }
    
    
    
    for (int i  = 0; i < numOfRow; i++) {
        for ( int j = 0; j < numOfCol; j++){
            
            callMyNamePlayer[i *numOfCol + j].setRect(hMargin*(j+1) + j*w, vMargin*(i+1) + i*h, w, h, ofColor(255, 0 , 0));
            
        }
    }
    
    // set remainder rect
    for ( int j = 0; j < remainder; j++){
        ofLogNotice("remainder draw");
        ofLogNotice(ofToString(numOfRow *numOfCol + remainder));
        callMyNamePlayer[numOfRow *numOfCol + j].setRect(hMargin*(j+1) + j*w, vMargin*(numOfRow+1) + (numOfRow)*h, w, h, ofColor(255, 0 , 0));
        
    }
}


void CallMyNameController::playAll(){
    shufflePlayOrder();

    for (int i = 0; i < callMyNamePlayer.size(); i++) {
        callMyNamePlayer[playOrder[i]].playAfterMs(i*70);
    }
}

void CallMyNameController::shufflePlayOrder(){
    std::random_shuffle(playOrder.begin(), playOrder.end());
    ofRandomize(playOrder);
//    for (int i = 0; i < playOrder.size(); i++) {
//        ofLogNotice(ofToString(playOrder[i]));
//    }

}

