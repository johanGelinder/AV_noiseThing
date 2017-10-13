#include "ofApp.h"

void ofApp::setup(){
    
    sampleRate = 44100;
    bufferSize = 512;
    ofBackground(0);
    
    //----------------------------------------------------------
    // GUI setup
    //----------------------------------------------------------
    gui.setup();
    freqs1.set("freq1", 40, 1, 200);
    freqs2.set("freq2", 20, 1, 200);
    multi.set("multipiler", 440, 10, 1000);
    ampMulti.set("amp multiplier", 0.5, 0.0, 2.0);
    threshold.set("threshold", 0.16, 0.0, 2.0);
    distOn.set("Distortion", false);
    
    gui.add(freqs1);
    gui.add(freqs2);
    gui.add(multi);
    gui.add(ampMulti);
    gui.add(threshold);
    gui.add(distOn);
    
    
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
        
        //------------------------------------------------------
        // background pan
        //------------------------------------------------------
        double sum1 = myOsc.sinewave(myOsc4.sinewave(myOsc5.sinewave(40)*440)*myOsc2.sinewave(myOsc3.sinewave(20)*160)*150);
        
        //------------------------------------------------------
        // main signal, 5 oscillators mixed together using FM
        //------------------------------------------------------
        double sum =  osc.sinewave(osc2.sinewave(osc3.sinewave(freqs1) * multi)
                                   * osc4.sinewave(osc5.sinewave(freqs2) * modFrequencyY) * modFrequencyX);
        
        //------------------------------------------------------
        // deviding sum1 so it won't take over our main signal
        //------------------------------------------------------
        sum += sum1/4.0;
        
        double distortion = foldBack(sum, threshold);
        
        //------------------------------------------------------
        // turn distortion on/off
        //------------------------------------------------------
        if(distOn){
            output[i * nChannels] = distortion * ampMulti;
        }else{
            output[i * nChannels] = sum * ampMulti;
        };
        output[i * nChannels + 1] = output[ i * nChannels];
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //---------------------------------------------------------
    // display the gui
    //---------------------------------------------------------
    gui.draw();
    
    //---------------------------------------------------------
    // use the mouse to modulate the signal
    //---------------------------------------------------------
    modFrequencyX = ofMap(mouseX, 0, ofGetWidth(), 0, 300);
    modFrequencyY = ofMap(mouseY, 0, ofGetWidth(), 0, 200);
}


//--------------------------------------------------------------
double ofApp::foldBack(double in, double threshold) {
    
    //----------------------------------------------------------
    // fold back distortion filter, flips the waveform
    // depending on the threshold
    //----------------------------------------------------------
    
    /// fabs returns the absolute value
    // fmod returns the floating-point reminder
    if( in > thres || in < - threshold ) {
        in = fabs(fabs(fmod(in - threshold, threshold * 6 )) - threshold * 4) - threshold;
    }
    return in;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
  //  env.trigger = 1;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
   // env.trigger = 0;
}
