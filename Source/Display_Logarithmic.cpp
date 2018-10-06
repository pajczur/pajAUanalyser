/*
  ==============================================================================

    DisplayWindow.cpp
    Created: 18 Apr 2018 10:20:17pm
    Author:  Wojtek Pilwinski

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Display_Logarithmic.h"

//==============================================================================
Display_Logarithmic::Display_Logarithmic()
{

//    wZoom.setSliderStyle(Slider::SliderStyle::ThreeValueHorizontal);
//    addAndMakeVisible(&wZoom);
//    wZoom.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
//    wZoom.addListener(this);
}

Display_Logarithmic::~Display_Logarithmic()
{
}

void Display_Logarithmic::paint (Graphics& g)
{
    float lineThickness = 0.7f;
    float altLineThickness = 0.1f;
    
    g.setFont (12.0f);
    

    if(wNyquist>1)
    {
        _winX = getWidth() - margXLeft - margXRight;
        _winY = getHeight() - margYBot - margYTop;

        
//        scaleNyquist = (log10(nyqFr)    - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
//        scaleSampRat = (log10(sampRat)  - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
        
        g.setColour(Colours::lightblue);
  
        
//        g.drawLine((scale10Hz * _winX)+margXLeft, margYTop, (scale10Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, lineThickness);
        g.drawLine((scale20Hz * _winX)+margXLeft, margYTop, (scale20Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, lineThickness);
        g.drawLine((scale30Hz * _winX)+margXLeft, margYTop, (scale30Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, altLineThickness);
        g.drawLine((scale40Hz * _winX)+margXLeft, margYTop, (scale40Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, altLineThickness);
        g.drawLine((scale50Hz * _winX)+margXLeft, margYTop, (scale50Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, altLineThickness);
        g.drawLine((scale60Hz * _winX)+margXLeft, margYTop, (scale60Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, altLineThickness);
        g.drawLine((scale70Hz * _winX)+margXLeft, margYTop, (scale70Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, altLineThickness);
        g.drawLine((scale80Hz * _winX)+margXLeft, margYTop, (scale80Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, altLineThickness);
        g.drawLine((scale90Hz * _winX)+margXLeft, margYTop, (scale90Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, altLineThickness);
        g.drawLine((scale100Hz * _winX)+margXLeft, margYTop, (scale100Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, lineThickness);
        g.drawLine((scale200Hz * _winX)+margXLeft, margYTop, (scale200Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, altLineThickness);
        g.drawLine((scale300Hz * _winX)+margXLeft, margYTop, (scale300Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, altLineThickness);
        g.drawLine((scale400Hz * _winX)+margXLeft, margYTop, (scale400Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, altLineThickness);
        g.drawLine((scale500Hz * _winX)+margXLeft, margYTop, (scale500Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, altLineThickness);
        g.drawLine((scale600Hz * _winX)+margXLeft, margYTop, (scale600Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, altLineThickness);
        g.drawLine((scale700Hz * _winX)+margXLeft, margYTop, (scale700Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, altLineThickness);
        g.drawLine((scale800Hz * _winX)+margXLeft, margYTop, (scale800Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, altLineThickness);
        g.drawLine((scale900Hz * _winX)+margXLeft, margYTop, (scale900Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, altLineThickness);
        g.drawLine((scale1000Hz * _winX)+margXLeft, margYTop, (scale1000Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, lineThickness);
        g.drawLine((scale2000Hz * _winX)+margXLeft, margYTop, (scale2000Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, altLineThickness);
        g.drawLine((scale3000Hz * _winX)+margXLeft, margYTop, (scale3000Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, altLineThickness);
        g.drawLine((scale4000Hz * _winX)+margXLeft, margYTop, (scale4000Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, altLineThickness);
        g.drawLine((scale5000Hz * _winX)+margXLeft, margYTop, (scale5000Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, altLineThickness);
        g.drawLine((scale6000Hz * _winX)+margXLeft, margYTop, (scale6000Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, altLineThickness);
        g.drawLine((scale7000Hz * _winX)+margXLeft, margYTop, (scale7000Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, altLineThickness);
        g.drawLine((scale8000Hz * _winX)+margXLeft, margYTop, (scale8000Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, altLineThickness);
        g.drawLine((scale9000Hz * _winX)+margXLeft, margYTop, (scale9000Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, altLineThickness);
        g.drawLine((scale10000Hz * _winX)+margXLeft, margYTop, (scale10000Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, lineThickness);
        g.drawLine((scale11000Hz * _winX)+margXLeft, margYTop, (scale11000Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, altLineThickness);
        g.drawLine((scale12000Hz * _winX)+margXLeft, margYTop, (scale12000Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, altLineThickness);
        g.drawLine((scale13000Hz * _winX)+margXLeft, margYTop, (scale13000Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, altLineThickness);
        g.drawLine((scale14000Hz * _winX)+margXLeft, margYTop, (scale14000Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, altLineThickness);
        g.drawLine((scale15000Hz * _winX)+margXLeft, margYTop, (scale15000Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, altLineThickness);
        g.drawLine((scale16000Hz * _winX)+margXLeft, margYTop, (scale16000Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, altLineThickness);
        g.drawLine((scale17000Hz * _winX)+margXLeft, margYTop, (scale17000Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, altLineThickness);
        g.drawLine((scale18000Hz * _winX)+margXLeft, margYTop, (scale18000Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, altLineThickness);
        g.drawLine((scale19000Hz * _winX)+margXLeft, margYTop, (scale19000Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, altLineThickness);
        g.drawLine((scale20000Hz * _winX)+margXLeft, margYTop, (scale20000Hz * _winX)+margXLeft, margYTop+ _winY+4.0f, lineThickness);
        
//        g.drawText("10",    margXLeft-31.0f + (scale10Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);

        g.drawText("20",    margXLeft-31.0f + (scale20Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);

        if(_winX>550)
                g.drawText("30",    margXLeft-31.0f + (scale30Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);
        
        if(_winX>650)
            g.drawText("40",    margXLeft-31.0f + (scale40Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);
    
        if(_winX>1000)
            g.drawText("50",    margXLeft-31.0f + (scale50Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);

        if(_winX>1200)
            g.drawText("60",    margXLeft-31.0f + (scale60Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);
    
        if(_winX>1400)
            g.drawText("70",    margXLeft-31.0f + (scale70Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);
    
        if(_winX>1500)
            g.drawText("80",    margXLeft-31.0f + (scale80Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);
    
        if(_winX>1500)
            g.drawText("90",    margXLeft-31.0f + (scale90Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);

        g.drawText("100",   margXLeft-30.0f + (scale100Hz*_winX),   getHeight()-margYBot, 60, 20, Justification::centred);

        if(_winX>500)
            g.drawText("200",   margXLeft-30.0f + (scale200Hz*_winX),  getHeight()-margYBot, 60, 20, Justification::centred);
        
        if(_winX>550)
            g.drawText("300",   margXLeft-30.0f + (scale300Hz*_winX),  getHeight()-margYBot, 60, 20, Justification::centred);
    
        if(_winX>650)
            g.drawText(".4k",   margXLeft-30.0f + (scale400Hz*_winX),  getHeight()-margYBot, 60, 20, Justification::centred);
    
        if(_winX>1000)
            g.drawText(".5k",   margXLeft-30.0f + (scale500Hz*_winX),  getHeight()-margYBot, 60, 20, Justification::centred);
    
        if(_winX>1200)
            g.drawText(".6k",   margXLeft-30.0f + (scale600Hz*_winX),  getHeight()-margYBot, 60, 20, Justification::centred);
    
        if(_winX>1400)
            g.drawText(".7k",   margXLeft-30.0f + (scale700Hz*_winX),  getHeight()-margYBot, 60, 20, Justification::centred);
    
        if(_winX>1500)
            g.drawText(".8k",   margXLeft-30.0f + (scale800Hz*_winX),  getHeight()-margYBot, 60, 20, Justification::centred);
        
        if(_winX>1500)
            g.drawText(".9k",   margXLeft-30.0f + (scale900Hz*_winX),  getHeight()-margYBot, 60, 20, Justification::centred);

        g.drawText("1k",    margXLeft-30.0f + (scale1000Hz*_winX),   getHeight()-margYBot, 60, 20, Justification::centred);
    
        if(_winX>500)
            g.drawText("2k",    margXLeft-30.0f + (scale2000Hz*_winX),   getHeight()-margYBot, 60, 20, Justification::centred);
    
        if(_winX>550)
            g.drawText("3k",    margXLeft-30.0f + (scale3000Hz*_winX),   getHeight()-margYBot, 60, 20, Justification::centred);
        
        if(_winX>650)
            g.drawText("4k",    margXLeft-30.0f + (scale4000Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);
    
        if(_winX>1000)
            g.drawText("5k",    margXLeft-30.0f + (scale5000Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);
    
        if(_winX>1200)
            g.drawText("6k",    margXLeft-30.0f + (scale6000Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);
    
        if(_winX>1400)
            g.drawText("7k",    margXLeft-30.0f + (scale7000Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);
    
        if(_winX>1500)
            g.drawText("8k",    margXLeft-30.0f + (scale8000Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);
        
        if(_winX>1500)
            g.drawText("9k",    margXLeft-30.0f + (scale9000Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);

        g.drawText("10k",    margXLeft-30.0f + (scale10000Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);
        
        if(_winX>1500)
            g.drawText("12k",    margXLeft-30.0f + (scale12000Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);
        
        if(_winX>1100)
            g.drawText("15k",    margXLeft-30.0f + (scale15000Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);
        
        g.drawText("20k",   margXLeft-30.0f + (scale20000Hz*_winX),   getHeight()-margYBot, 60, 20, Justification::centred);

        g.setColour(Colours::lightblue);
        g.drawLine(margXLeft+_winX, margYTop, margXLeft+_winX, margYTop+ _winY);
        g.drawRect((float)(margXLeft-0.5f), 3.0f, (float)(_winX+1.0f), (float)(margYTop-2.5));
//        g.fillRect((float)(margXLeft-1), 0.0f, (float)(_winX+2), (float)margYTop);
        
        if (graphTitle == "Magnitude")
        {
            //Horizontal lines
            for (int i=0; i<5; i++) {
                g.drawLine(margXLeft-4, ((float)i*_winY/4.0f)+margYTop, margXLeft+_winX, ((float)i*_winY/4.0f)+margYTop, (i==0||i==4)?1.0f:0.6f);
            }
            for (int i=0; i<4; i++) {
                g.drawLine(margXLeft-4, ((float)i*_winY/4.0f)+margYTop+(_winY/8.0f), margXLeft+_winX, ((float)i*_winY/4.0f)+margYTop+(_winY/8.0f), 0.2f);
            }
            
            g.drawText( " 24dB",   margXLeft-47, (0*_winY/4.0f)+margYTop-9,  40, 20, Justification::right);
            g.drawText( " 12dB",   margXLeft-47, (1*_winY/4.0f)+margYTop-9,  40, 20, Justification::right);
            g.drawText( "  0dB",   margXLeft-47, (2*_winY/4.0f)+margYTop-9,  40, 20, Justification::right);
            g.drawText( "-12dB",   margXLeft-47, (3*_winY/4.0f)+margYTop-9,  40, 20, Justification::right);
            g.drawText( "-24dB",   margXLeft-47, (4*_winY/4.0f)+margYTop-9,  40, 20, Justification::right);
        }
        else
        {
            //Horizontal lines
            for (int i=0; i<5; i++) {
                g.drawLine(margXLeft-4, ((float)i*_winY/4.0f)+margYTop, margXLeft+_winX, ((float)i*_winY/4.0f)+margYTop, (i==0||i==4)?1.0f:0.6f);
            }
            for (int i=0; i<4; i++) {
                g.drawLine(margXLeft-4, ((float)i*_winY/4.0f)+margYTop+(_winY/8.0f), margXLeft+_winX, ((float)i*_winY/4.0f)+margYTop+(_winY/8.0f), 0.2f);
            }
            
            String degreesymbol = String::fromUTF8("\u00B0");
            g.drawText( " 180"+degreesymbol,   margXLeft-47, (0*_winY/4.0f)+margYTop-9,  40, 20, Justification::right);
            g.drawText( "  90"+degreesymbol,   margXLeft-47, (1*_winY/4.0f)+margYTop-9,  40, 20, Justification::right);
            g.drawText( "   0"+degreesymbol,   margXLeft-47, (2*_winY/4.0f)+margYTop-9,  40, 20, Justification::right);
            g.drawText( " -90"+degreesymbol,   margXLeft-47, (3*_winY/4.0f)+margYTop-9,  40, 20, Justification::right);
            g.drawText( "-180"+degreesymbol,   margXLeft-47, (4*_winY/4.0f)+margYTop-9,  40, 20, Justification::right);
        }
        

    }
 
    
    
    g.setColour (Colours::white);
    g.setFont (12.0f);
    g.drawFittedText(" - " + graphTitle + " - ", ((getWidth()-margXLeft-margXLeft)/2.0)-50.0+margXLeft, 8.5, 100, 10, Justification::centred, 1);
    
    if(channelQuantity>1) {
        g.setColour(Colours::white);
        g.drawFittedText("LEFT", ((getWidth()-margXLeft-margXLeft)/2.0)-50.0+margXLeft -35, 8.5, 50, 10, Justification::centred, 1);
        g.setColour(Colours::red);
        g.drawFittedText("RIGHT", ((getWidth()-margXLeft-margXLeft)/2.0)-50.0+margXLeft + 90, 8.5, 50, 10, Justification::centred, 1);
    }
}

void Display_Logarithmic::resized()
{
//    wZoom.setBounds(10, 10, getWidth()-10, 30);
}

int Display_Logarithmic::getDisplayHeight()
{
    return getHeight()-margYBot-margYTop;
}

int Display_Logarithmic::getDisplayWidth()
{
    return getWidth()-margXLeft-margXRight;
}

int Display_Logarithmic::getDisplayMargXLeft()
{
    return margXLeft;
}

int Display_Logarithmic::getDisplayMargYTop()
{
    return margYTop;
}

void Display_Logarithmic::setNyquist(float nyquistFreq)
{
    wNyquist = nyquistFreq;
    topEnd = wNyquist;
    
    scale10Hz    = (log10(10.0f)    - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    scale20Hz    = (log10(20.0f)    - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    scale30Hz    = (log10(30.0f)    - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    scale40Hz    = (log10(40.0f)    - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    scale50Hz    = (log10(50.0f)    - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    scale60Hz    = (log10(60.0f)    - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    scale70Hz    = (log10(70.0f)    - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    scale80Hz    = (log10(80.0f)    - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    scale90Hz    = (log10(90.0f)    - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    scale100Hz   = (log10(100.0f)   - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    scale200Hz   = (log10(200.0f)   - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    scale300Hz   = (log10(300.0f)   - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    scale400Hz   = (log10(400.0f)   - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    scale500Hz   = (log10(500.0f)   - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    scale600Hz   = (log10(600.0f)   - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    scale700Hz   = (log10(700.0f)   - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    scale800Hz   = (log10(800.0f)   - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    scale900Hz   = (log10(900.0f)   - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    scale1000Hz  = (log10(1000.0f)  - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    scale2000Hz  = (log10(2000.0f)  - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    scale3000Hz  = (log10(3000.0f)  - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    scale4000Hz  = (log10(4000.0f)  - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    scale5000Hz  = (log10(5000.0f)  - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    scale6000Hz  = (log10(6000.0f)  - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    scale7000Hz  = (log10(7000.0f)  - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    scale8000Hz  = (log10(8000.0f)  - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    scale9000Hz  = (log10(9000.0f)  - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    scale10000Hz = (log10(10000.0f) - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    scale11000Hz = (log10(11000.0f) - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    scale12000Hz = (log10(12000.0f) - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    scale13000Hz = (log10(13000.0f) - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    scale14000Hz = (log10(14000.0f) - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    scale15000Hz = (log10(15000.0f) - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    scale16000Hz = (log10(16000.0f) - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    scale17000Hz = (log10(17000.0f) - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    scale18000Hz = (log10(18000.0f) - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    scale19000Hz = (log10(19000.0f) - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    scale20000Hz = (log10(20000.0f) - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
    
    
//    wZoom.setRange(-0.0001, wNyquist, 0.01);
//        wZoom.setSkewFactorFromMidPoint(440.0);
    
//    wZoom.setMinAndMaxValues(200.0, wNyquist, dontSendNotification);
//    aPlusMinus = (wZoom.getMaxValue() - wZoom.getMinValue()) / 2.0f;
//    wZoom.setValue( ((wZoom.getMaxValue()-wZoom.getMinValue())/2.0) + wZoom.getMinValue(), dontSendNotification );
//    middlThumb = wZoom.getValue();
//
//    sliderValueChanged(&wZoom);
}

/*
void Display_Logarithmic::sliderValueChanged (Slider *slider)
{
    if(slider == &wZoom)
    {
        aPlusMinus = (wZoom.getMaxValue() - wZoom.getMinValue()) / 2.0f;

        if (wZoom.getThumbBeingDragged() == 1 || wZoom.getThumbBeingDragged() == 2) {
            wZoom.setValue(((wZoom.getMaxValue() - wZoom.getMinValue()) / 2.0) + wZoom.getMinValue(), dontSendNotification);
        }
        else
        {
            if      (wZoom.getMinValue() <= wZoom.getMinimum() && wZoom.getValue()<middlThumb) {
                wZoom.setValue(middlThumb, dontSendNotification);
                return;
            }
            else if (wZoom.getMaxValue() >= wZoom.getMaximum()-0.01 && wZoom.getValue()>middlThumb) {
                wZoom.setValue(middlThumb, dontSendNotification);
                return;
            }
            else {
                wZoom.setMinAndMaxValues(wZoom.getValue() - aPlusMinus, wZoom.getValue() + aPlusMinus, dontSendNotification);
            }
        }

        middlThumb = wZoom.getValue();

        lowEnd = pow(10.0, wZoom.getMinValue()*log10(22050.0)/22050.0);
        topEnd = pow(10.0, wZoom.getMaxValue()*log10(22050.0)/22050.0);

        repaint();
        graphAnalyser->setZoomLogar(lowEnd, topEnd);

    }
}
*/
void Display_Logarithmic::whatToDisplay(GraphAnalyser &graph)
{
    graphAnalyser = &graph;
}
