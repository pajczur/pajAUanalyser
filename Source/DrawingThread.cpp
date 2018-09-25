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
        if(!isResizing)
        {
            wait (1000);
            if (threadShouldExit()) return;
            
            makeFFT();
            
            const MessageManagerLock mml (Thread::getCurrentThread());
            if (mml.lockWasGained())
                drawFFTgraph();
        }
        else
        {
            wait (1000);
            if (threadShouldExit()) return;
            
            const MessageManagerLock mml (Thread::getCurrentThread());
            if (mml.lockWasGained())
                drawSTATICgraph();
        }
    }
}

void DrawingThread::drawFFTgraph()
{
    if(isSystemReady)
    {
        if(sourceIsReady[left])
        {
            graphAnalyserMagL.drawGraph();
            graphAnalyserPhaL.drawGraph();
            sourceIsReady[left]=false;
        }
        
        if(totalNumInputChannels==2)
        {
            if(sourceIsReady[right])
            {
                graphAnalyserMagR.drawGraph();
                graphAnalyserPhaR.drawGraph();
                sourceIsReady[right]=false;
            }
        }
    }
}


void DrawingThread::drawSTATICgraph()
{
    graphAnalyserMagL.drawGraphSTATIC();
    graphAnalyserPhaL.drawGraphSTATIC();
    if(totalNumInputChannels==2)
    {
        graphAnalyserMagR.drawGraphSTATIC();
        graphAnalyserPhaR.drawGraphSTATIC();
    }
}
