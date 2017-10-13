#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    
    void audioOut(float * output, int bufferSize, int nChannels);
    
    unsigned bufferSize, sampleRate;
    double sample, freq, modIndex, modFrequencyX, modFrequencyY;
    double outputs[2];
    
    maxiOsc osc, mod;
    maxiOsc osc2, osc3,osc4, osc5;
    maxiMix mix;
    maxiEnv env;
    
    
    maxiOsc myOsc, myOsc2, myOsc3, myOsc4, myOsc5;
    
    ofxPanel gui;
    ofParameter<float> freqs1;
    ofParameter<float> freqs2;
    ofParameter<float> multi;
     ofParameter<float> ampMulti;
    
};
