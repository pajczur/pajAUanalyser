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
GraphAnalyser::GraphAnalyser() : pajUnwrapping(true)
{
    staticPath.resize(10000);
}


GraphAnalyser::~GraphAnalyser()
{
}


void GraphAnalyser::wSettings(std::vector<float> &fftSourceData, float buffSizz)
{
    dataSource = &fftSourceData;
    dataSize = buffSizz/2.0f;
    
//    if(xResize > 400)
//    {
//        resetPath();
//    }
}


void GraphAnalyser::setWindScaleSettings(float &sampRat, float &wBuffSiz)
{
    logScaleWidth = sampRat/wBuffSiz;
    
    if(log10(topEnd) - log10(lowEnd) != 0.0)
        dispLogScale = ( (double)getWidth() ) / ( log10(topEnd) - log10(lowEnd));
    else
        dispLogScale = 0.0f;
    
    lowEndIndex  = ceil((20.0f/sampRat) * wBuffSiz);
    fLowEndIndex =      (20.0f/sampRat) * wBuffSiz ;
    
    yCordScale = 20.0f*((zero_dB/2.0)/(20.0*log10(4)));
}


void GraphAnalyser::paint (Graphics& g)
{
    if(chan==W_LEFT)
    {
        g.setColour (PAJ_YELLOW);
    }
    
    if (chan==W_RIGHT)
    {
        g.setColour(PAJ_RED);
    }
    

    if(isStaticGraph)
        g.strokePath(fftStaticPath.createPathWithRoundedCorners(16), PathStrokeType(1.2));
    else
        g.strokePath(fftGraphPath.createPathWithRoundedCorners(16), PathStrokeType(1.2));

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
    isStaticGraph = false;
    xResize = getWidth();
    yResize = getHeight();
    fftGraphPath.clear();
    
    if(outType == W_MAGN)
        drawMagPath();
    else if (outType == W_PHAS)
        drawPhaPath();
        
    repaint();
}


void GraphAnalyser::drawGraphSTATIC()
{
    if(xResize > 400 && yResize > 150)
    {
        isStaticGraph = true;
        fftStaticPath = fftGraphPath;

        fftStaticPath.applyTransform(AffineTransform::scale((float)getWidth()/xResize, (float)getHeight()/yResize));
    }
}


void GraphAnalyser::resetPath()
{
    fftStaticPath.clear();
    fftStaticPath.startNewSubPath(0, (float)getHeight()/2.0f);
    fftStaticPath.lineTo(getWidth(), (float)getHeight()/2.0f);
    fftGraphPath.clear();
    fftGraphPath.startNewSubPath(0, (float)getHeight()/2.0f);
    fftGraphPath.lineTo(getWidth(), (float)getHeight()/2.0f);
    
    repaint();
}


void GraphAnalyser::drawMagPath()
{
    float beffPointX = 0.0f;
    float currPointX = dispLogScale * (log10(fLowEndIndex*logScaleWidth) - log10(lowEnd));
    
    float beffAVDataSrc = dataSource->at(lowEndIndex-1) != 0.0f ? dataSource->at(lowEndIndex) : 0.00001f;
    float currAVDataSrc = dataSource->at(lowEndIndex  ) != 0.0f ? dataSource->at(lowEndIndex) : 0.00001f;
    float beffPointY = zero_dB - ( log10(abs(beffAVDataSrc)) * yCordScale );
    float currPointY = zero_dB - ( log10(abs(currAVDataSrc)) * yCordScale );
    
    fftGraphPath.startNewSubPath(beffPointX, beffPointY);
    
    float wDivider=0.0f;
    
    currAVDataSrc = 0.0f;
    beffPointX = currPointX;
    
    for(int i=lowEndIndex+1; i<dataSize; i++)
    {
        currAVDataSrc += dataSource->at(i);
        wDivider += 1.0f;

//        currAVDataSrc = dataSource->at(i) > currAVDataSrc ? dataSource->at(i) : currAVDataSrc;
        
        currPointX = dispLogScale * (log10((float)i*logScaleWidth) - log10(lowEnd));
        
        if(currPointX-beffPointX >= 2.0f)
        {
            currPointY = zero_dB - ( log10(abs(currAVDataSrc/wDivider)) * yCordScale );
            
            fftGraphPath.lineTo(currPointX, currPointY);
        
            beffAVDataSrc = currAVDataSrc;
            currAVDataSrc = 0.0f;
            wDivider = 0.0f;
            beffPointX = currPointX;
        }
    }
}


void GraphAnalyser::drawPhaPath()
{
    stPathIndex = 0;
    float staticPathY=0.0f;
    float beffPointX = 0.0f;
    float currPointX = dispLogScale * (log10(fLowEndIndex*logScaleWidth) - log10(lowEnd));

    float beffAVDataSrc = dataSource->at(lowEndIndex-1);
    float currAVDataSrc = dataSource->at(lowEndIndex);
    float beffPointY = zero_dB + beffAVDataSrc * zero_dB;
    float currPointY = zero_dB + currAVDataSrc * zero_dB;

    fftGraphPath.startNewSubPath(beffPointX, beffPointY);
    staticPath[0].setXY(beffPointX, beffPointY);

    float wDivider=0.0f;
    float fPIshift=0.0f;

    currAVDataSrc = 0.0f;

    for(int i=lowEndIndex+1; i<dataSize; i++)
    {
        if(pajUnwrapping)
        {
            float tempp = dataSource->at(i) - dataSource->at(i-1);

            if(tempp >= 1.0f)
                fPIshift -= 2;
            else if(tempp <= -1.0f)
                fPIshift += 2;
        }
        currAVDataSrc += dataSource->at(i) + fPIshift;
        staticPathY += dataSource->at(i);

        wDivider += 1.0f;
        currPointX = dispLogScale * (log10((float)i*logScaleWidth) - log10(lowEnd));

        if(currPointX-beffPointX >= 2.0f)
        {
            currPointY = zero_dB + (zero_dB * currAVDataSrc/wDivider);

            fftGraphPath.lineTo(currPointX, currPointY);
            staticPath[++stPathIndex].setXY(currPointX, zero_dB + (zero_dB * staticPathY /wDivider ));

            staticPathY = 0.0f;
            currAVDataSrc = 0.0f;
            wDivider = 0.0f;
            beffPointX = currPointX;
        }
    }

    if(pajUnwrapping)
        fftGraphPath.applyTransform(AffineTransform::translation(0, -fPIshift*zero_dB));
}


void GraphAnalyser::rememberBounds()
{
    xResize = (float)getWidth();
    yResize = (float)getHeight();
}


void GraphAnalyser::staticWrapToggle()
{
    fftStaticPath.clear();
    fftStaticPath.startNewSubPath(staticPath[0]);
    
    float fPIshift=0;
    
    for(int i=1; i<stPathIndex; i++)
    {
        if(pajUnwrapping)
        {
            float tempp = (staticPath[i].getY()-zero_dB) - (staticPath[i-1].getY()-zero_dB);
            
            if(tempp >= zero_dB)
                fPIshift -= 2 * zero_dB;
            else if(tempp <= -zero_dB)
                fPIshift += 2 * zero_dB;
        }
        
        fftStaticPath.lineTo(staticPath[i].getX(), staticPath[i].getY() + fPIshift);
        
    }
    
    if(pajUnwrapping)
        fftStaticPath.applyTransform(AffineTransform::translation(0, -fPIshift));
    
    isStaticGraph = true;
    repaint();
}




// For quadratic graph
/*
void GraphAnalyser::drawMagPath2()
{
    float beffCTRLPointX = dispLogScale * (log10((fLowEndIndex>1.001f?(fLowEndIndex-1):0.001f)*logScaleWidth) - log10(lowEnd));
    float currCTRLPointX = dispLogScale * (log10(fLowEndIndex*logScaleWidth) - log10(lowEnd));
    
    float beffAVDataSrc = abs(dataSource->at(lowEndIndex-1)) > 0.0001f ? dataSource->at(lowEndIndex) : 0.0001f;
    float currAVDataSrc = abs(dataSource->at(lowEndIndex  )) > 0.0001f ? dataSource->at(lowEndIndex) : 0.0001f;
    float beffCTRLPointY = zero_dB - ( log10(abs(beffAVDataSrc)) * yCordScale );
    float currCTRLPointY = zero_dB - ( log10(abs(currAVDataSrc)) * yCordScale );
    
    float currPointX = beffCTRLPointX + ((currCTRLPointX - beffCTRLPointX) / 2.0f);
    float currPointY = beffCTRLPointY + ((currCTRLPointY - beffCTRLPointY) / 2.0f);
    
    fftGraphPath.startNewSubPath(beffCTRLPointX, beffCTRLPointY);
    fftGraphPath.lineTo(currPointX, currPointY);
    
    float wDivider=0.0f;
    
    currAVDataSrc = 0.0f;
    beffCTRLPointY = currCTRLPointY;
    beffCTRLPointX = currCTRLPointX;
    
    for(int i=lowEndIndex+1; i<dataSize; i++)
    {
        currAVDataSrc += dataSource->at(i);
        wDivider += 1.0f;
        currCTRLPointX = dispLogScale * (log10((float)i*logScaleWidth) - log10(lowEnd));
        
        if(currCTRLPointX-beffCTRLPointX >= 3.0f)
        {
            currAVDataSrc = (currAVDataSrc/wDivider) > 0.0001f ? currAVDataSrc/wDivider : 0.0001f;
            currCTRLPointY = zero_dB - ( log10(abs(currAVDataSrc)) * yCordScale );
            
            currPointX = beffCTRLPointX + ((currCTRLPointX - beffCTRLPointX) / 2.0f);
            currPointY = beffCTRLPointY + ((currCTRLPointY - beffCTRLPointY) / 2.0f);
            
            float xCorrection = (wDivider >= 2.0f) ? 1.5f : 0.0f;
            
            fftGraphPath.quadraticTo(beffCTRLPointX-xCorrection, beffCTRLPointY, currPointX-xCorrection, currPointY);
            
            beffAVDataSrc = currAVDataSrc;
            currAVDataSrc = 0.0f;
            wDivider = 0.0f;
            beffCTRLPointY = currCTRLPointY;
            beffCTRLPointX = currCTRLPointX;
        }
    }
}



void GraphAnalyser::drawPhaPath()
{
    float beffCTRLPointX = dispLogScale * (log10((fLowEndIndex>1.001f?(fLowEndIndex-1):0.001f)*logScaleWidth) - log10(lowEnd));
    float currCTRLPointX = dispLogScale * (log10(fLowEndIndex*logScaleWidth) - log10(lowEnd));
 
    float beffAVDataSrc = dataSource->at(lowEndIndex-1);
    float currAVDataSrc = dataSource->at(lowEndIndex);
    float beffCTRLPointY = zero_dB + beffAVDataSrc * zero_dB;
    float currCTRLPointY = zero_dB + currAVDataSrc * zero_dB;
    
    float currPointX = beffCTRLPointX + ((currCTRLPointX - beffCTRLPointX) / 2.0f);
    float currPointY = beffCTRLPointY + ((currCTRLPointY - beffCTRLPointY) / 2.0f);

    fftGraphPath.startNewSubPath(beffCTRLPointX, beffCTRLPointY);
    fftGraphPath.lineTo(currPointX, currPointY);

    float wDivider=0.0f;
    float fPIshift=0;
 
    currAVDataSrc = 0.0f;
    beffCTRLPointY = currCTRLPointY;
    beffCTRLPointX = currCTRLPointX;

    for(int i=lowEndIndex+1; i<dataSize; i++)
    {
        if(pajUnwrapping)
        {
            float tempp = dataSource->at(i) - dataSource->at(i-1);

            if(tempp >= 1.0f)
                fPIshift -= 2;
            else if(tempp <= -1.0f)
                fPIshift += 2;
        }
        currAVDataSrc += dataSource->at(i) + fPIshift;
        
        wDivider += 1.0f;
        currCTRLPointX = dispLogScale * (log10((float)i*logScaleWidth) - log10(lowEnd));
        

        if(currCTRLPointX-beffCTRLPointX >= 3.0f)
        {
            currAVDataSrc = (currAVDataSrc/wDivider);
            
            currCTRLPointY = zero_dB + (currAVDataSrc * zero_dB);
            
            currPointX = beffCTRLPointX + ((currCTRLPointX - beffCTRLPointX) / 2.0f);
            currPointY = beffCTRLPointY + ((currCTRLPointY - beffCTRLPointY) / 2.0f);
 
            float xCorrection = (wDivider >= 2.0f) ? 1.5f : 0.0f;

            fftGraphPath.quadraticTo(beffCTRLPointX-xCorrection, beffCTRLPointY, currPointX-xCorrection, currPointY);
 
            beffAVDataSrc = currAVDataSrc;
            currAVDataSrc = 0.0f;
            wDivider = 0.0f;
            beffCTRLPointY = currCTRLPointY;
            beffCTRLPointX = currCTRLPointX;
        }
    }

    if(pajUnwrapping)
        fftGraphPath.applyTransform(AffineTransform::translation(0, -fPIshift*zero_dB));
}
*/
