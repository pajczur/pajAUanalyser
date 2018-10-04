/*
  ==============================================================================

    DrawingThread.h
    Created: 16 Sep 2018 1:50:19pm
    Author:  Wojtek Pilwinski

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DrawingThread.h"
#include "Display_Logarithmic.h"
#include "PajFFT/PajFFT_Radix2.h"

//==============================================================================
/*
*/
class DrawingThread    : public Thread
{
public:
    DrawingThread();
    ~DrawingThread();
    
    void drawFFTgraph();
    void drawSTATICgraph();
    
    void run() override;
    
    std::vector<float> wInput[2];
    std::vector<std::vector<std::vector<float>>> wOutput;
    
    bool isSystemReady;
    bool sourceIsReady[2];
    
    
    inline void makeFFT()
    {
        if(isSystemReady)
        {
            if(sourceIsReady[left])
                radix2_FFT.makeFFT(wInput[left], wOutput[left], left);
            
            if(sourceIsReady[right])
                radix2_FFT.makeFFT(wInput[right], wOutput[right], right);
        }
    }
    
    
    Display_Logarithmic display_magni;
    Display_Logarithmic display_phase;
    
    GraphAnalyser graphAnalyserMagL;
    GraphAnalyser graphAnalyserPhaL;
    GraphAnalyser graphAnalyserMagR;
    GraphAnalyser graphAnalyserPhaR;

    PajFFT_Radix2     radix2_FFT;
    int totalNumInputChannels=1;
    std::atomic<bool> isResizing;
    std::atomic<bool> isAnalOff;
    std::atomic<bool> drawPhase;
private:
    
    enum outputType
    {
        wMag = 0,
        wPha = 1
    };
    enum channels
    {
        left  = 0,
        right = 1
    };
    
    int testPaj = 0;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DrawingThread)
};
