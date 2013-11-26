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
    
    void randomizePlayOrder();

private:
    vector<CallMyNamePlayer> callMyNamePlayer;
    vector<int> playOrder;
    int fileCount;
    ofDirectory fileDirectory;
//    int counter;
};
