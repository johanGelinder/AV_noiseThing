#include "ofApp.h"

void ofApp::setup(){
    
    sampleRate = 44100;
    bufferSize = 512;
    ofBackground(0);
    
    gui.setup();
    freqs1.set("freq1", 40, 1, 200);
    freqs2.set("freq2", 20, 1, 200);
    multi.set("multipiler", 440, 10, 1000);
    ampMulti.set("amp multiplier", 0.5, 0.0, 2.0);
    
    gui.add(freqs1);
    gui.add(freqs2);
    gui.add(multi);
    gui.add(ampMulti);
    
    
 /*
    freq = 220;
    modFrequency = 0;
    modIndex = 100;
    
    env.setAttack(2000);
    env.setDecay(1);
    env.setSustain(1);
    env.setRelease(3000);
  */
    
    ofSoundStreamSetup(2,0,this, sampleRate, bufferSize, 4);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
}

//--------------------------------------------------------------

void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    
    for (int i = 0; i < bufferSize; i++) {
        
    double sum1= myOsc.sinewave(myOsc4.sinewave(myOsc5.sinewave(40)*440)*myOsc2.sinewave(myOsc3.sinewave(20)*160)*150);
        
     double sum =  osc.sinewave(osc2.sinewave(osc3.sinewave(freqs1) * multi)
                                * osc4.sinewave(osc5.sinewave(freqs2) * modFrequencyY) * modFrequencyX);
        sum+=sum1;
        
        output[i * nChannels] = sum * ampMulti;
        output[i * nChannels + 1] = output[ i * nChannels];
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    gui.draw();
    
    modFrequencyX = ofMap(mouseX, 0, ofGetWidth(), 0, 300);
    modFrequencyY = ofMap(mouseY, 0, ofGetWidth(), 0, 200);
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    env.trigger = 1;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    env.trigger = 0;
}
