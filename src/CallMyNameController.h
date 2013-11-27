//
//  CallMyNameController.h
//  CallMyName
//
//  Created by hojun on 11/26/13.
//
//

#pragma once

#include "ofMain.h"
#include "CallMyNamePlayer.h"
#include "ACRandomizer.h"

class CallMyNameController {
    
public:
    CallMyNameController();
    ~CallMyNameController();
    
    void setup(string folderPath, string allowableExt);
    void addPlayer(string filePath);
    void draw();
    void setPlayerRectSize();
    
    void playAll();
    void play();
    void stopAll();
    void shufflePlayOrder();
    int getFileCount();
    
    void setPlayMany(int num);
    
    void setPlayDelay(int ms);
    void setSwingOn(bool bSet);

private:
    vector<CallMyNamePlayer> callMyNamePlayer;
    int playDelay;
    int playMany;
    int playCount;
    bool bSwingOn;
    vector<int> playOrder;
    int fileCount;
    ofDirectory fileDirectory;
//    int counter;
};
