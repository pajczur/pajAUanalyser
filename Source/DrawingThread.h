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
    void wSetBounds(int wWidth, int wHeight, int isShowPhase);
    
    bool pajSettings(int numberOfChannels, float fftSize, float sampRate);
    
    void drawFFTgraph();
    void drawSTATICgraph();
    void resetAnalGraph();
    void rememberGraphBounds();
    
    void setVisibleGraph(int showPhase, int showMagn);
    
    void run() override;
    
    std::vector<float> wInput[2];
    std::vector<std::vector<std::vector<float>>> wOutput;
    
    bool isSystemReady;
    bool sourceIsReady[2];
    
    
    inline void makeFFT()
    {
        if(isSystemReady)
        {
            if(sourceIsReady[W_LEFT])
                radix2_FFT.makeFFT(wInput[W_LEFT],  wOutput[W_LEFT],  W_LEFT);
            
            if(sourceIsReady[W_RIGHT])
                radix2_FFT.makeFFT(wInput[W_RIGHT], wOutput[W_RIGHT], W_RIGHT);
        }
    }
    
    
    Display_Logarithmic display_magni;
    Display_Logarithmic display_phase;
    
    GraphAnalyser magAnal[2];
    GraphAnalyser phaAnal[2];

    PajFFT_Radix2     radix2_FFT;
    int numChannels=1;
    std::atomic<bool> isResizing;
    std::atomic<bool> isHold;
    std::atomic<bool> notifyEditor;
    
private:
    int testPaj = 0;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DrawingThread)
};
