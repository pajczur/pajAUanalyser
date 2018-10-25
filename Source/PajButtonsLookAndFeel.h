/*
  ==============================================================================

    PajButtonsLookAndFeel.h
    Created: 24 Oct 2018 8:43:06pm
    Author:  Wojtek Pilwinski

  ==============================================================================
*/

#pragma once
#include "DefinitionMacros.h"

class PajButtonsLookAndFeel : public LookAndFeel_V4
{
public:
    PajButtonsLookAndFeel()
    {
        resolButtonIcons[B_1024ID]  = ImageCache::getFromMemory(pajAUanalyser::buffToggleButton_1024_false_png,  pajAUanalyser::buffToggleButton_1024_false_pngSize);
        resolButtonIcons[B_2048ID]  = ImageCache::getFromMemory(pajAUanalyser::buffToggleButton_2048_false_png,  pajAUanalyser::buffToggleButton_2048_false_pngSize);
        resolButtonIcons[B_4096ID]  = ImageCache::getFromMemory(pajAUanalyser::buffToggleButton_4096_false_png,  pajAUanalyser::buffToggleButton_4096_false_pngSize);
        resolButtonIcons[B_8192ID]  = ImageCache::getFromMemory(pajAUanalyser::buffToggleButton_8192_false_png,  pajAUanalyser::buffToggleButton_8192_false_pngSize);
        resolButtonIcons[B_16384ID] = ImageCache::getFromMemory(pajAUanalyser::buffToggleButton_16384_false_png, pajAUanalyser::buffToggleButton_16384_false_pngSize);
        resolButtonIcons[B_32768ID] = ImageCache::getFromMemory(pajAUanalyser::buffToggleButton_32768_false_png, pajAUanalyser::buffToggleButton_32768_false_pngSize);
        resolButtonIcons[B_65536ID] = ImageCache::getFromMemory(pajAUanalyser::buffToggleButton_65536_false_png, pajAUanalyser::buffToggleButton_65536_false_pngSize);
        w_ButtonSize.setBounds(0, 0, 30, 30);
    }
    
    void drawToggleButton(Graphics &g, ToggleButton &toggleButton, bool isMouseOverButton, bool isButtonDown) override
    {
        g.drawImage(*resolButtonIcon, w_ButtonSize);
        
        if(toggleButton.getToggleState() || isMouseOverButton)
            g.drawImage(toggleButton_True, w_ButtonSize);
    }
    
    void setResolutionIcon(int buffSizeID)
    {
        if(buffSizeID >= 0 && buffSizeID < NUM_OF_RADIO_BUTTONS)
            resolButtonIcon = &resolButtonIcons[buffSizeID];
        else
            resolButtonIcon = &resolButtonIcons[B_1024ID];
    }
    
private:
    Image resolButtonIcons[NUM_OF_RADIO_BUTTONS];
    Image *resolButtonIcon;
    Image toggleButton_True = ImageCache::getFromMemory(pajAUanalyser::buffToggleButton_true_png,  pajAUanalyser::buffToggleButton_true_pngSize);
    Rectangle<float> w_ButtonSize;
    
};


class OffButtonLookAndFeel : public LookAndFeel_V4
{
public:
    OffButtonLookAndFeel()
    {
        buttonSize.setBounds(0,0,46,15);
    }
    
    void drawButtonBackground (Graphics &g, Button &button, const Colour &backgroundColour, bool isMouseOverButton, bool isButtonDown) override
    {
        if(isMouseOverButton || isButtonDown)
        {
            g.setColour(Colours::white);
            
            if(isButtonDown)
                g.setColour(Colours::ghostwhite);
            
            g.fillRect(buttonSize);
            g.drawImage(offIcon_true, buttonSize);
        }
        else
            g.drawImage(offIcon_false, buttonSize);
    }
    
private:
    Rectangle<float> buttonSize;
    Image offIcon_false = ImageCache::getFromMemory(pajAUanalyser::offButton_false_png,  pajAUanalyser::offButton_false_pngSize);
    Image offIcon_true = ImageCache::getFromMemory(pajAUanalyser::offButton_true_png,  pajAUanalyser::offButton_true_pngSize);
};


class ResetButtonLookAndFeel : public LookAndFeel_V4
{
public:
    ResetButtonLookAndFeel()
    {
        buttonSize.setBounds(0,0,46,15);
    }
    
    void drawButtonBackground (Graphics &g, Button &button, const Colour &backgroundColour, bool isMouseOverButton, bool isButtonDown) override
    {
        if(isMouseOverButton || isButtonDown)
        {
            g.setColour(Colours::white);
            
            if(isButtonDown)
                g.setColour(Colours::ghostwhite);
            
            g.fillRect(buttonSize);
            g.drawImage(resetIcon_true, buttonSize);
        }
        else
            g.drawImage(resetIcon_false, buttonSize);
    }
    
private:
    Rectangle<float> buttonSize;
    Image resetIcon_false = ImageCache::getFromMemory(pajAUanalyser::resetButton_false_png, pajAUanalyser::resetButton_false_pngSize);
    Image resetIcon_true  = ImageCache::getFromMemory(pajAUanalyser::resetButton_true_png,  pajAUanalyser::resetButton_true_pngSize);
};


class PhaseButtonLookAndFeel : public LookAndFeel_V4
{
public:
    PhaseButtonLookAndFeel()
    {
        buttonSize.setBounds(0,0,46,15);
        
        phaseIcon_false[0] = ImageCache::getFromMemory(pajAUanalyser::phaseButton_false_png, pajAUanalyser::phaseButton_false_pngSize);
        phaseIcon_false[1] = ImageCache::getFromMemory(pajAUanalyser::magnitudeButton_false_png, pajAUanalyser::magnitudeButton_false_pngSize);
        phaseIcon_true[0] = ImageCache::getFromMemory(pajAUanalyser::phaseButton_true_png,  pajAUanalyser::phaseButton_true_pngSize);
        phaseIcon_true[1] = ImageCache::getFromMemory(pajAUanalyser::magnitudeButton_true_png,  pajAUanalyser::magnitudeButton_true_pngSize);
    }
    
    void drawButtonBackground (Graphics &g, Button &button, const Colour &backgroundColour, bool isMouseOverButton, bool isButtonDown) override
    {
        if(isMouseOverButton || isButtonDown)
        {
            g.setColour(Colours::white);
            
            if(isButtonDown)
                g.setColour(Colours::ghostwhite);
//                g.setColour(Colours::lightskyblue);
            
            g.fillRect(buttonSize);
            g.drawImage(phaseIcon_true[showPhaseBool], buttonSize);
        }
        else
            g.drawImage(phaseIcon_false[showPhaseBool], buttonSize);
    }
    
    void switchIcon(bool isPhase)
    {
        if (!isPhase)
            showPhaseBool = 0;
        else
            showPhaseBool = 1;
    }
    
private:
    Rectangle<float> buttonSize;
    Image phaseIcon_false[2];
    Image phaseIcon_true[2];

    
    int showPhaseBool = 0;
};



class UnwrapButtonLookAndFeel : public LookAndFeel_V4
{
public:
    UnwrapButtonLookAndFeel()
    {
        buttonSize.setBounds(0,0,54,19);
    }
    
    void drawToggleButton (Graphics &g, ToggleButton &toggleButton, bool isMouseOverButton, bool isButtonDown)
    {
//        g.setColour(Colours::lightblue);
        g.setColour(Colours::white);
        g.drawLine(54, 0, 54, 19, 1);
        
        if(toggleButton.getToggleState())
        {
            g.fillRect(buttonSize);
            g.drawImage(unwrapIcon_true, buttonSize);
        }
        else
            g.drawImage(unwrapIcon_false, buttonSize);
            
        
        if(isMouseOverButton || isButtonDown)
        {
            if(isButtonDown)
            {
                g.setColour(Colours::ghostwhite);
                g.fillRect(buttonSize);
                g.drawImage(unwrapIcon_true, buttonSize);
            }
        }
    }
    
private:
    Rectangle<float> buttonSize;
    Image unwrapIcon_false = ImageCache::getFromMemory(pajAUanalyser::unWrap_false_png, pajAUanalyser::unWrap_false_pngSize);
    Image unwrapIcon_true  = ImageCache::getFromMemory(pajAUanalyser::unWrap_true_png,  pajAUanalyser::unWrap_true_pngSize);
};



class LatencyButtonLookAndFeel : public LookAndFeel_V4
{
public:
    LatencyButtonLookAndFeel()
    {
        buttonSize.setBounds(0,0,54,19);
    }
    

    
    void drawButtonBackground (Graphics &g, Button &button, const Colour &backgroundColour, bool isMouseOverButton, bool isButtonDown) override
    {
//        g.setColour(Colours::lightblue);
        g.setColour(Colours::white);
        g.drawLine(0, 0, 0, 19, 1);
        
        g.drawImage(latencyIcon_false, buttonSize);
        
        if(isMouseOverButton || isButtonDown)
        {
            if(isButtonDown)
            {
                g.setColour(Colours::ghostwhite);
                g.fillRect(buttonSize);
                g.drawImage(latencyIcon_true, buttonSize);
            }
        }
    }
    
private:
    Rectangle<float> buttonSize;
    Image latencyIcon_false = ImageCache::getFromMemory(pajAUanalyser::latencyButton_false_png, pajAUanalyser::latencyButton_false_pngSize);
    Image latencyIcon_true  = ImageCache::getFromMemory(pajAUanalyser::latencyButton_true_png,  pajAUanalyser::latencyButton_true_pngSize);
};
