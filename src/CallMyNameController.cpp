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
    
    
    playCount = 0;
    bSwingOn = false;

    
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
    
    // Do Not Shuffle in the beginning
    // Fuck it Just Shuffle it
    shufflePlayOrder();
    
    ofLogNotice("stop");
    
    if(fileCount > 0){
        playMany = 1;
        playDelay = 70;
    }
    else{
        playMany = 0;
        playDelay = 70;
    }
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
    float menuMargin = 60;
    int numOfCol = 10;
    int numOfRow = (int)ceil((float)callMyNamePlayer.size() / (float)numOfCol);
    ofLogNotice("real row");
    ofLogNotice(ofToString(numOfRow));
    // check remainder is left
    
    float hMargin = 10;
    float vMargin = 10;
    float w = (ofGetWidth()- (numOfCol + 2) * hMargin) / (numOfCol);
    float h = (ofGetHeight()-menuMargin- (numOfRow + 2) * vMargin) / (numOfRow);

    
    
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
            
            callMyNamePlayer[i *numOfCol + j].setRect(hMargin*(j+1) + j*w, vMargin*(i+1) + i*h + menuMargin, w, h, ofColor(255, 0 , 0));
            
        }
    }
    
    // set remainder rect
    for ( int j = 0; j < remainder; j++){
        ofLogNotice("remainder draw");
        ofLogNotice(ofToString(numOfRow *numOfCol + remainder));
        callMyNamePlayer[numOfRow *numOfCol + j].setRect(hMargin*(j+1) + j*w, vMargin*(numOfRow+1) + (numOfRow)*h, w, h, ofColor(255, 0 , 0));
        
    }
}

void CallMyNameController::play(){

    for (int i = 0; i < playMany; i++) {
        int randomDelay;
        if (bSwingOn) {
            randomDelay = (int)ofRandom(70, playDelay);
            cout << "random delay: " << randomDelay << endl;

        }
        else{
            randomDelay = playDelay;
        }
        
        if (playCount > callMyNamePlayer.size()-1){
            playCount = 0;
            shufflePlayOrder();
        }

        cout<< "playCount: " << playCount << endl;
        callMyNamePlayer[playOrder[playCount]].playAfterMs((i+1)*randomDelay);
        playCount++;
    }
//    playCount += playMany;
    

    

}

void CallMyNameController::playAll(){
    shufflePlayOrder();

    for (int i = 0; i < callMyNamePlayer.size(); i++) {
        int randomDelay;
        if (bSwingOn) {
            randomDelay = (int)ofRandom(70, playDelay);
            cout << "random delay: " << randomDelay << endl;
        }else
        {
            randomDelay = playDelay;
        }
        
        callMyNamePlayer[playOrder[i]].playAfterMs((i+1)*randomDelay);
    }
}

void CallMyNameController::stopAll(){
    for (int i = 0; i < callMyNamePlayer.size(); i++) {
        callMyNamePlayer[i].stop();
    }
}

void CallMyNameController::shufflePlayOrder(){
    std::random_shuffle(playOrder.begin(), playOrder.end());
    ofRandomize(playOrder);
//    for (int i = 0; i < playOrder.size(); i++) {
//        ofLogNotice(ofToString(playOrder[i]));
//    }
    cout<< "Shuffle!!" <<endl;
}

int CallMyNameController::getFileCount(){
    return callMyNamePlayer.size();
}


void CallMyNameController::setPlayMany(int num){
    playMany = num;
    cout << "머야:" << playMany << endl;
}

void CallMyNameController::setPlayDelay(int ms){
    playDelay = ms;
}

void CallMyNameController::setSwingOn(bool bSet){
    bSwingOn = bSet;
}