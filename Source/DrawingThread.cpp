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
DrawingThread::DrawingThread() : Thread("Drawing thread"),
                                 isSystemReady(false),
                                 isResizing(false),
                                 drawPhase(false),
                                 notifyEditor(true)
{
    display_magni.graphTitle = "Magnitude";
    display_phase.graphTitle = "Phase shift";
}

DrawingThread::~DrawingThread()
{
}


void DrawingThread::wSetBounds(int wWidth, int wHeight, int isShowPhase)
{
    int displayWidth = wWidth-20;
    
    if(isShowPhase==0)
    {
        int displayHeight= wHeight-64;
        
        display_magni.setBounds (0, 55,      displayWidth, displayHeight);
        
        int graphWidth = display_magni.getDisplayWidth();
        int graphHeight= display_magni.getDisplayHeight();
        
        for(int channel=0; channel<numChannels; ++channel)
        {
            magAnal[channel].setBounds(50, 78, graphWidth, graphHeight);
        }
    }
    else
    {
        int graphOffsetY = (wHeight/2.0)+27.5;
        int displayHeight= (wHeight/2.0)-35.5;
        
        display_magni.setBounds (0, 55,      displayWidth, displayHeight);
        display_phase.setBounds (0, graphOffsetY, displayWidth, displayHeight);
        
        int graphWidth = display_magni.getDisplayWidth();
        int graphHeight= display_magni.getDisplayHeight();
        
        for(int channel=0; channel<numChannels; ++channel)
        {
            magAnal[channel].setBounds(50, 78, graphWidth, graphHeight);
            phaAnal[channel].setBounds(50, 23+graphOffsetY, graphWidth, graphHeight);
        }
    }
}

void DrawingThread::pajSettings(int numberOfChannels, float fftSize, float sampRate)
{
    isSystemReady = false;
    radix2_FFT.wSettings(sampRate, fftSize);
    
    numChannels = (numberOfChannels>1)?2:1;
    
    display_magni.channelQuantity = numChannels;
    display_phase.channelQuantity = numChannels;
    display_magni.setNyquist(sampRate/2.0f);
    display_phase.setNyquist(sampRate/2.0f);

    wOutput.resize(numChannels);
    
    for(int channel=0; channel<numChannels; ++channel)
    {
        sourceIsReady[channel] = false;
        
        wOutput[channel].resize(2);
        wOutput[channel][wMag].resize((size_t)fftSize, 1.0f);
        wOutput[channel][wPha].resize((size_t)fftSize, 0.0f);
        wInput[channel].resize(fftSize, 0.0f);
        
        magAnal[channel].setChannel(channel, wMag);
        magAnal[channel].wSettings(wOutput[channel][wMag], fftSize);
        magAnal[channel].setWindScaleSettings(sampRate, fftSize);
        phaAnal[channel].setChannel(channel, wPha);
        phaAnal[channel].wSettings(wOutput[channel][wPha], fftSize);
        phaAnal[channel].setWindScaleSettings(sampRate, fftSize);
    }
}

void DrawingThread::run()
{
    while(! threadShouldExit())
    {
        wait (-1);
        if (threadShouldExit()) return;
        notifyEditor = false;
        
        if(!isResizing && !isHold)
        {
            makeFFT();
            
            const MessageManagerLock mml (Thread::getCurrentThread());
            if (mml.lockWasGained())
            {
                drawFFTgraph();
//                DBG("FFT GRAPH " << (testPaj++)%100);
            }
        }
        else
        {
            const MessageManagerLock mml (Thread::getCurrentThread());
            if (mml.lockWasGained())
            {
                drawSTATICgraph();
//                DBG("STATIC GRAPH " << (testPaj++)%100);
            }
        }
        
        notifyEditor = true;
    }
}

void DrawingThread::drawFFTgraph()
{
    if(isSystemReady)
    {
        for(int channel=0; channel<numChannels; ++channel)
        {
            magAnal[channel].drawGraph();
            if(drawPhase)
                phaAnal[channel].drawGraph();

            sourceIsReady[channel] = false;
        }
    }
}


void DrawingThread::drawSTATICgraph()
{
    for(int channel=0; channel<numChannels; ++channel)
    {
        magAnal[channel].drawGraphSTATIC();

        if(drawPhase)
            phaAnal[channel].drawGraphSTATIC();
    }
}
