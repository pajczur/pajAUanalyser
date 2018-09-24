/*
  ==============================================================================

    DrawingThread.cpp
    Created: 16 Sep 2018 1:50:19pm
    Author:  Wojtek Pilwinski

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "DrawingThread.h"

//==============================================================================
DrawingThread::DrawingThread()  : Thread("Drawing thread"), isSystemReady(false)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
}

DrawingThread::~DrawingThread()
{
}

void DrawingThread::run()
{
    while(! threadShouldExit())
    {
        wait (1000);
        if (threadShouldExit()) return;
        
        makeFFT();
        
        const MessageManagerLock mml (Thread::getCurrentThread());
        if (mml.lockWasGained())
            calcAndDraw();
        
        
    }
}

void DrawingThread::calcAndDraw()
{
    if(isSystemReady)
    {
        if(sourceIsReady[left])
        {
//            makeFFT(wInput[left], wOutput[left], left);
            
            graphAnalyserMagL.preparePath();
            
            graphAnalyserPhaL.preparePath();
            
            sourceIsReady[left]=false;
        }
        
        if(sourceIsReady[right])
        {
//            makeFFT(wInput[right], wOutput[right], right);
            
            graphAnalyserMagR.preparePath();
            
            graphAnalyserPhaR.preparePath();
            
            sourceIsReady[right]=false;
        }
    }
}
