/*
  ==============================================================================

    GraphAnalyser.h
    Created: 9 May 2018 5:56:23pm
    Author:  Wojtek Pilwinski

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DefinitionMacros.h"


//==============================================================================

class GraphAnalyser    : public Component
{
public:
    GraphAnalyser();
    ~GraphAnalyser();
    
    void wSettings(std::vector<float> &fftSourceData, float buffSizz);
    inline void setChannel(int channel, int outputType) {chan=channel; outType=outputType;}
    void setWindScaleSettings(float &sampRat, float &wBuffSiz);



    void paint (Graphics&) override;
    void resized() override;
    
    void drawGraph();
    void drawMagPath();
    void drawMagPath2();
    void drawPhaPath();
    void drawGraphSTATIC();
    void resetPath();
    void staticWrapToggle();
    
    void rememberBounds();
    
    Path fftGraphPath;
    Path fftStaticPath;
    bool isStaticGraph = true;

public:
    std::vector<Path> timeGraph;
    float dataSize;
private:
    std::vector<float> *dataSource;
    int chan;
    int    lowEndIndex;
    float fLowEndIndex;
    float zero_dB;
    float winWidth;
    int outType;
    float dispLogScale;
    float logScaleWidth;
    
    float lowEnd = LOW_END_IN_HERTZ;
    float topEnd = TOP_END_IN_HERTZ;
    
    float yCordScale;
    
//    std::vector<double> xScale;
    
    std::vector<float> pomiarFazy;
    
    std::atomic<float> yResize;
    std::atomic<float> xResize;
    int staticGraphSize;
    
public:
    std::atomic<bool> pajUnwrapping;
    
    std::vector<Point<float>> staticPath;
    int stPathIndex=0;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GraphAnalyser)
};
