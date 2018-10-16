/*
  ==============================================================================

    GraphAnalyser.h
    Created: 9 May 2018 5:56:23pm
    Author:  Wojtek Pilwinski

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#define b1024ID       0
#define b2048ID       1
#define b4096ID       2
#define b8192ID       3
#define b16384ID      4
#define b32768ID      5
#define b65536ID      6

#define muteImpulseID 7

#define numOfRadioButton 7

#define unWrapID      10
#define latencyID     11

#define pajPlay       19

#define pajOffButtonID   20
#define pajResetButtonID 21
#define pajPhaseButtonID 22

#define refreshMessageReceivedBool 50

#define bufferButtonRadioGroup 100

#define wMag 0
#define wPha 1

#define wLeft  0
#define wRight 1

#define SETTINGS_READY true

//==============================================================================
/*
*/
class GraphAnalyser    : public Component
{
public:
    GraphAnalyser();
    ~GraphAnalyser();
    
    void wSettings(std::vector<float> &fftSourceData, float buffSizz);
    inline void setChannel(int channel, int outputType) {chan=channel; outType=outputType;}
    void setWindScaleSettings(float &sampRat, float &wBuffSiz);

    

    void setZoomLogar(double lowE, double topE);
    void setZoomLinear(double endTime);


    void paint (Graphics&) override;
    void resized() override;
    
    void drawGraph();
    void drawMagPath();
    void drawPhaPath();
    void drawGraphSTATIC();
    void drawMagPathSTATIC();
    void drawPhaPathSTATIC();
    void clearDisplay();
    
    Path fftGraphPath;
    Path fftGraphH;
private:
public:
    Path wavGraph;
    std::vector<Path> timeGraph;
    std::vector<float> drawStaticY;
    float dataSize;
private:
    std::vector<float> *dataSource;
    float fPIshift;
    int chan;
    int lowEndIndex=1;
    float zero_dB;
    float winWidth;
    float wNyquist;
    int outType;
    float dispLogScale;
    float logScaleWidth;
    
    float lowEnd;
    float topEnd;
    
    float yCordScale;
    
    std::vector<double> xScale;
    
    std::vector<float> pomiarFazy;
    
public:
    std::atomic<bool> pajUnwrapping;
    std::atomic<bool> *drawPhase;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GraphAnalyser)
};
