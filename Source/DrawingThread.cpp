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
                                 notifyEditor(true)
{
    display_magni.graphTitle = MAGNITUDE;
    display_phase.graphTitle = PHASE_SHIFT;
    
    sourceIsReady[W_LEFT] = false;
    sourceIsReady[W_RIGHT] = false;
    
    isSystemReady = false;
}

DrawingThread::~DrawingThread()
{
}


void DrawingThread::wSetBounds(int wWidth, int wHeight, int isShowPhase)
{
    int displayWidth = wWidth-20;
    
//    if(!isShowPhase)
//    {
        int displayHeight= wHeight-64;
        display_magni.setBounds(0, 55, displayWidth, displayHeight);
        
        int graphWidth = display_magni.getDisplayWidth();
        int graphHeight= display_magni.getDisplayHeight();
        
        for(int channel=0; channel<numChannels; ++channel)
        {
            magAnal[channel].setBounds(50, 78, graphWidth, graphHeight);
        }
//    }
//    else
//    {
//        int displayHeight= wHeight-64;
        display_phase.setBounds(0, 55, displayWidth, displayHeight);
        
//        int graphWidth = display_phase.getDisplayWidth();
//        int graphHeight= display_phase.getDisplayHeight();
        
        for(int channel=0; channel<numChannels; ++channel)
        {
            phaAnal[channel].setBounds(50, 78, graphWidth, graphHeight);
        }
//    }
}

bool DrawingThread::pajSettings(int numberOfChannels, float fftSize, float sampRate)
{
    isSystemReady = false;
    
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
        wOutput[channel][W_MAGN].resize((size_t)fftSize, 1.0f);
        wOutput[channel][W_PHAS].resize((size_t)fftSize, 0.0f);
        wInput[channel].resize(fftSize, 0.0f);
        
        magAnal[channel].setChannel(channel, W_MAGN);
        magAnal[channel].wSettings(wOutput[channel][W_MAGN], fftSize);
        magAnal[channel].setWindScaleSettings(sampRate, fftSize);
        phaAnal[channel].setChannel(channel, W_PHAS);
        phaAnal[channel].wSettings(wOutput[channel][W_PHAS], fftSize);
        phaAnal[channel].setWindScaleSettings(sampRate, fftSize);
    }
    
    if(radix2_FFT.wSettings(sampRate, fftSize))
        return SETTINGS_READY;
    else
        return false;
}

void DrawingThread::run()
{
    while(! threadShouldExit())
    {

        wait (-1);
        notifyEditor = false;

        if (threadShouldExit()) return;

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
            sourceIsReady[channel] = false;
            
            magAnal[channel].drawGraph();
            phaAnal[channel].drawGraph();

        }
    }
}


void DrawingThread::drawSTATICgraph()
{
    for(int channel=0; channel<numChannels; ++channel)
    {
        magAnal[channel].drawGraphSTATIC();
        phaAnal[channel].drawGraphSTATIC();
    }
}


void DrawingThread::resetAnalGraph() {
    
    for(int channel=0; channel<numChannels; ++channel)
    {
        magAnal[channel].resetPath();
        phaAnal[channel].resetPath();
    }
}

void DrawingThread::rememberGraphBounds()
{
    for(int channel=0; channel<numChannels; ++channel)
    {
        magAnal[channel].rememberBounds();
        phaAnal[channel].rememberBounds();
    }
}



void DrawingThread::setVisibleGraph(int showPhase, int showMagn)
{
    for(int channel=0; channel<numChannels; ++channel)
    {
        magAnal[channel].setVisible(showMagn);
        phaAnal[channel].setVisible(showPhase);
    }
}
