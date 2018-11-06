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

    void paint (Graphics &g) override;
    void resized() override;
    void drawFreqLines(Graphics &g);
    void drawFreqText(Graphics &g);
    void drawHorizontalLines(Graphics &g);
    void drawDBtext(Graphics &g);
    void drawDegreeText(Graphics &g);
    void drawTitleBar(Graphics &g);
    int getDisplayHeight();
    int getDisplayWidth();
    int getDisplayMargXLeft();
    int getDisplayMargYTop();
    void setNyquist(/*float nyquistFreq*/);
    void whatToDisplay(GraphAnalyser &graph);
    
    String graphTitle;

private:
    float mainLineThickness = 0.9f;
    float altLineThickness = 0.3f;
    float edgeThickness = 1.0f;
    float linesOpacity = 0.55f;
//    float wNyquist = 1.0f;
    float lowEnd = LOW_END_IN_HERTZ;
    float topEnd = TOP_END_IN_HERTZ;
    float nyqFr;
    float sampRat;
    float sampRatMark;
    
//    float scale10Hz   ;
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

    GraphAnalyser *graphAnalyser;
    
    float _winX;
    float _winY;
public:
    int channelQuantity=0;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Display_Logarithmic)
};
