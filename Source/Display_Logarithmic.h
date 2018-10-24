/*
  ==============================================================================

    DisplayWindow.h
    Created: 18 Apr 2018 10:20:17pm
    Author:  Wojtek Pilwinski

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "GraphAnalyser.h"

//==============================================================================

class Display_Logarithmic    : public Component
{
public:
    Display_Logarithmic();
    ~Display_Logarithmic();
//    void sliderValueChanged (Slider *slider) override;

    void paint (Graphics&) override;
    void resized() override;
    int getDisplayHeight();
    int getDisplayWidth();
    int getDisplayMargXLeft();
    int getDisplayMargYTop();
    void setNyquist(float nyquistFreq);
    void whatToDisplay(GraphAnalyser &graph);
    
    String graphTitle;

private:
    float wNyquist = 1.0f;
    float topEnd;
    float lowEnd = 20.0f;
    float nyqFr;
    float sampRat;
    float sampRatMark;
    
    float scale10Hz   ;
    float scale20Hz   ;
    float scale30Hz   ;
    float scale40Hz   ;
    float scale50Hz   ;
    float scale60Hz   ;
    float scale70Hz   ;
    float scale80Hz   ;
    float scale90Hz   ;
    float scale100Hz  ;
    float scale200Hz  ;
    float scale300Hz  ;
    float scale400Hz  ;
    float scale500Hz  ;
    float scale600Hz  ;
    float scale700Hz  ;
    float scale800Hz  ;
    float scale900Hz  ;
    float scale1000Hz ;
    float scale2000Hz ;
    float scale3000Hz ;
    float scale4000Hz ;
    float scale5000Hz ;
    float scale6000Hz ;
    float scale7000Hz ;
    float scale8000Hz ;
    float scale9000Hz ;
    float scale10000Hz;
    float scale11000Hz;
    float scale12000Hz;
    float scale13000Hz;
    float scale14000Hz;
    float scale15000Hz;
    float scale16000Hz;
    float scale17000Hz;
    float scale18000Hz;
    float scale19000Hz;
    float scale20000Hz;
    float scaleNyquist;
    float scaleSampRat;
    
    std::vector<Line<float>> freqLines;
    
//    Slider wZoom;
    GraphAnalyser *graphAnalyser;
//    float aPlusMinus;
//    float middlThumb;
    
    float _winX;
    float _winY;
public:
    int channelQuantity=0;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Display_Logarithmic)
};
