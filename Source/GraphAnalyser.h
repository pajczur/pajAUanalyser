/*
  ==============================================================================

    GraphAnalyser.h
    Created: 9 May 2018 5:56:23pm
    Author:  Wojtek Pilwinski

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/*
*/
class GraphAnalyser    : public Component
{
public:
    GraphAnalyser();
    ~GraphAnalyser();
    
    void wSettings(std::vector<float> &fftSourceData, float buffSizz);
    void setChannel(int channel, int outputType) {chan=channel; outType=outputType;}
    void setWindScaleSettings(double &sampRat, double &wBuffSiz);

    

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
    
    enum outputType
    {
        wMag = 0,
        wPha = 1
    };
    
    enum channels
    {
        left = 0,
        right = 1
    };
    
    float yCordScale;
    
    std::vector<double> xScale;
    
    std::vector<float> pomiarFazy;
    
public:
    std::atomic<bool> pajUnwrapping;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GraphAnalyser)
};
