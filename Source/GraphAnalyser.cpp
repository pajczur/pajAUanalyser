/*
  ==============================================================================

    GraphAnalyser.cpp
    Created: 9 May 2018 5:56:23pm
    Author:  Wojtek Pilwinski

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "GraphAnalyser.h"

//==============================================================================
GraphAnalyser::GraphAnalyser() : pajUnwrapping(false)
{
}

GraphAnalyser::~GraphAnalyser()
{
}

void GraphAnalyser::wSettings(std::vector<float> &fftSourceData, float buffSizz)
{
    dataSource = &fftSourceData;
    dataSize = buffSizz/2.0f;
    
//    512 1024 1280 1407 1469 1497 1506
//    512 768  896  960  992  1008 1016
    if(dataSize==2048)
    {
        dataSize = 1280;
        //        dataSize = 896;
    }
    else if(dataSize==4096)
    {
        dataSize=1407;
        //        dataSize=960;
    }
    else if(dataSize==8192)
    {
        dataSize=1469;
        //        dataSize=992;
    }
    else if(dataSize==16384)
    {
        dataSize=1497;
        //        dataSize=1008;
    }
    else if (dataSize==32768)
    {
        dataSize=1506;
        //        dataSize=1016;
    }

    xScale.resize((int)dataSize);
    int tempIndex=0;
    for(int i=0; i<buffSizz/2.0f; i++)
    {
        if(i<=512)
        {
            xScale[i] = (double)i;
            tempIndex++;
        }
        else if(i>512 && i<=32768)
        {
            if(i%((((int)buffSizz)/2)/1024) == 0)
            {
                xScale[tempIndex] = (double)i;
                tempIndex++;
            }
        }
    }
    
    if(outType == wMag)
        drawStaticY.resize((int)dataSize, 1.0f);
    else if(outType == wPha)
        drawStaticY.resize((int)dataSize, 0.0f);
}

void GraphAnalyser::setWindScaleSettings(float &sampRat, float &wBuffSiz)
{
    wNyquist = sampRat/2.0f;
    
    logScaleWidth = wNyquist/(wBuffSiz/2.0);
    
//    float wZoomMin = 10.0f;
    float wZoomMax = wNyquist;

    lowEnd = 20.0f;
    topEnd = pow(10.0, wZoomMax*log10(wNyquist)/wNyquist);
    
    if(log10(topEnd) - log10(lowEnd) != 0.0)
        dispLogScale = ( (double)getWidth() ) / ( log10(topEnd) - log10(lowEnd));
    else
        dispLogScale = 0.0f;
    
    lowEndIndex = ceil((20.0f/sampRat) * wBuffSiz);
    
    yCordScale = 20.0f*((zero_dB/2.0)/(20.0*log10(4)));
}





void GraphAnalyser::paint (Graphics& g)
{
    if(chan==wLeft)
    {
        g.setColour (Colours::yellow);
    }
    
    if (chan==wRight)
    {
        g.setColour (Colours::red);
    }

//    g.strokePath(fftGraphL.createPathWithRoundedCorners(10.0f), PathStrokeType(2));
//    g.strokePath(fftGraphPath.createPathWithRoundedCorners(10.0f), PathStrokeType(1.0));
    
    if(outType==wMag)
        g.strokePath(fftGraphPath, PathStrokeType(1.0));
    else if(outType==wPha && *drawPhase)
        g.strokePath(fftGraphPath, PathStrokeType(1.0));
}




void GraphAnalyser::resized()
{
    zero_dB = (float)getHeight()/2.0f;
    winWidth = getWidth();
    
    if(log10(topEnd) - log10(lowEnd) != 0.0)
        dispLogScale = ( (double)winWidth ) / ( log10(topEnd) - log10(lowEnd));
    else
        dispLogScale = 0.0f;
    
    yCordScale = 20.0f*((zero_dB/2.0)/(20.0*log10(4)));
}









void GraphAnalyser::drawGraph()
{
    fftGraphPath.clear();
    
    if(outType == wMag)
        drawMagPath();
    else if (outType == wPha)
        drawPhaPath();
        
    repaint();
}


void GraphAnalyser::drawGraphSTATIC()
{
    fftGraphPath.clear();
    
    if(outType == wMag)
        drawMagPathSTATIC();
    else if (outType == wPha)
        drawPhaPathSTATIC();
    
//    repaint();
}



void GraphAnalyser::setZoomLogar(double lowE, double topE)
{

}

void GraphAnalyser::setZoomLinear(/*double startTime,*/ double endTime)
{

}




void GraphAnalyser::clearDisplay()
{

}

void GraphAnalyser::drawMagPath()
{
    float wMagnitude;
    
    if(abs(dataSource->at(lowEndIndex)) != 0)
        fftGraphPath.startNewSubPath(0.0f, (zero_dB - ( log10(abs(dataSource->at(lowEndIndex))) * yCordScale)));
    else
        fftGraphPath.startNewSubPath(0.0f, (zero_dB+2*zero_dB));
    
    drawStaticY[lowEndIndex] = dataSource->at(lowEndIndex);
    
    for(int i=lowEndIndex+1; i<dataSize; i++)
    {
        if(abs(dataSource->at(i)) != 0)
            wMagnitude = zero_dB - ( log10(dataSource->at(i)) * yCordScale );
        else
            wMagnitude = 10000.0f;
        
        double wCurrent   = dispLogScale * (log10(xScale[i]*logScaleWidth) - log10(lowEnd));
        
        if(i<=512)
        {
            fftGraphPath.lineTo(wCurrent, wMagnitude);
        }
        else
        {
            double wBefore    = dispLogScale * (log10(xScale[i-1]*logScaleWidth) - log10(lowEnd));
            fftGraphPath.lineTo((wBefore+((wCurrent-wBefore)/2)), wMagnitude);
//            fftGraphPath.lineTo(wCurrent, wMagnitude);
        }
        
        drawStaticY[i] = dataSource->at(i);
    }
}

void GraphAnalyser::drawPhaPath()
{
    float wPhaShift;
    float tempp;
    
    fPIshift=0;

    fftGraphPath.startNewSubPath(0.0f, zero_dB + dataSource->at(lowEndIndex) * zero_dB);
    
    drawStaticY[lowEndIndex] = dataSource->at(lowEndIndex);
    
    for(int i=lowEndIndex+1; i<dataSize; i++)
    {
        
        tempp = dataSource->at(i) - dataSource->at(i-1);
        
        if(pajUnwrapping)
        {
            if(tempp > 1.1f)
                fPIshift -= 2;
            else if(tempp < -1.1f)
                fPIshift += 2;
        }
        
        wPhaShift = zero_dB + (dataSource->at(i)+fPIshift) * (zero_dB);
        
        double wCurrent   = dispLogScale * (log10(xScale[i]*logScaleWidth) - log10(lowEnd));
        
        if(i<=512)
        {
            fftGraphPath.lineTo(wCurrent, wPhaShift);
        }
        else
        {
            double wBefore    = dispLogScale * (log10(xScale[i-1]*logScaleWidth) - log10(lowEnd));
            fftGraphPath.lineTo((wBefore+((wCurrent-wBefore)/2)), wPhaShift);
        }
        
        drawStaticY[i] = dataSource->at(i)+fPIshift;
    }
    
    if(pajUnwrapping)
        fftGraphPath.applyTransform(AffineTransform::translation(0, -fPIshift * zero_dB));
}


void GraphAnalyser::drawMagPathSTATIC()
{
    float wMagnitude;
    
    if(abs(drawStaticY[lowEndIndex]) != 0)
        fftGraphPath.startNewSubPath(0.0f, (zero_dB - ( log10(abs(drawStaticY[lowEndIndex])) * yCordScale)));
    else
        fftGraphPath.startNewSubPath(0.0f, (zero_dB+2*zero_dB));
    
    for(int i=lowEndIndex+1; i<dataSize; i++)
    {
        if(abs(drawStaticY[i]) != 0)
            wMagnitude = zero_dB - ( log10(drawStaticY[i]) * yCordScale );
        else
            wMagnitude = 10000.0f;
        
        double wCurrent   = dispLogScale * (log10(xScale[i]*logScaleWidth) - log10(lowEnd));
        
        if(i<=512)
        {
            fftGraphPath.lineTo(wCurrent, wMagnitude);
        }
        else
        {
            double wBefore    = dispLogScale * (log10(xScale[i-1]*logScaleWidth) - log10(lowEnd));
            fftGraphPath.lineTo((wBefore+((wCurrent-wBefore)/2)), wMagnitude);
        }
    }
}

void GraphAnalyser::drawPhaPathSTATIC()
{
    float wMagnitude;
    
//    fPIshift=0;

    fftGraphPath.startNewSubPath(0.0f, zero_dB + drawStaticY[lowEndIndex] * zero_dB);

    for(int i=lowEndIndex+1; i<dataSize; i++)
    {
        wMagnitude = zero_dB + drawStaticY[i] * (zero_dB);

        double wCurrent   = dispLogScale * (log10(xScale[i]*logScaleWidth) - log10(lowEnd));

        if(i<=512)
        {
            fftGraphPath.lineTo(wCurrent, wMagnitude);
        }
        else
        {
            double wBefore    = dispLogScale * (log10(xScale[i-1]*logScaleWidth) - log10(lowEnd));
            fftGraphPath.lineTo((wBefore+((wCurrent-wBefore)/2)), wMagnitude);
        }
    }
    
    if(pajUnwrapping)
        fftGraphPath.applyTransform(AffineTransform::translation(0, -fPIshift * zero_dB));
}
