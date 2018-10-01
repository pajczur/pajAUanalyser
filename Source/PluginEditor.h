/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class PajAuanalyserAudioProcessorEditor  : public AudioProcessorEditor, public MultiTimer, public InterprocessConnection
{
public:
    PajAuanalyserAudioProcessorEditor (PajAuanalyserAudioProcessor&);
    ~PajAuanalyserAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void updateToggleState(Button* button, int buttonID);
    
    void drawButtons();
    
    void timerCallback(int timerID) override;
    
    void mouseDown( const MouseEvent & event ) override;
    void mouseUp( const MouseEvent & event ) override;
    
    
    void connectionMade() override;
    void connectionLost() override;
    void messageReceived( const MemoryBlock & message) override;
    
    void setBufferSize(int bufSizeID);
    
    void turnOffAnal();
    void resetAnalGraph();
    
    void setGraphBounds(int isShowPhase);
    
    void toggleButtonByID(int buttonID);
    
private:
    PajAuanalyserAudioProcessor& processor;
    
    int channelQuantity;

    double sampRate = processor.getSampleRate();;
    double buffSize = processor.wBuffSize;
    
    enum outputType
    {
        wMag = 0,
        wPha = 1
    };
    enum channels
    {
        left  = 0,
        right = 1
    };

    bool isResized;
    
    Font wFontSize=12.0f;
    Font wFontSize2=15.0f;
    
    Label setBuffSizLabel;
    Label setResolutLabel;
    
    ToggleButton buff_1024;
    Label buff_1024_Label;
    
    ToggleButton buff_2048;
    Label buff_2048_Label;
    
    ToggleButton buff_4096;
    Label buff_4096_Label;
    
    ToggleButton buff_8192;
    Label buff_8192_Label;
    
    ToggleButton buff_16384;
    Label buff_16384_Label;
    
    ToggleButton buff_32768;
    Label buff_32768_Label;
    
    ToggleButton buff_65536;
    Label buff_65536_Label;
    
    ToggleButton latencyDetect;
    Label latencyDetectLabel;
    
    ToggleButton pajUnwrap;
    Label pajUnwrapLabel;
    
    TextButton pajOFFButton;
    TextButton pajResetButton;
    TextButton pajPhaseButton;
    
    int rememberWhichButtonIsToggled;
    std::atomic<bool> waitForSettings;
    
    enum buttonsID {
        muteImpulseID = 0,
        b1024ID       = 1,
        b2048ID       = 2,
        b4096ID       = 3,
        b8192ID       = 4,
        b16384ID      = 5,
        b32768ID      = 6,
        b65536ID      = 7,
        unWrapID      = 8,
        latencyID     = 100,
        pajOffButtonID      = 900,
        pajResetButtonID    = 901,
        pajPhaseButtonID    = 902,
        bufferButtonRadioGroup = 1000
    };
    
    void leaveButtonsUntouched(int onButtonID);
    
    MemoryBlock impulseMessage;
    
    Rectangle<float> buttonsSpace;
    Rectangle<float> logoSpace;
    
    const String pathToLogo = "/Users/wojtekpilwinski/Development/PublicRepositories/pajAUanalyser/Source/pajczurLogo.png";

    File pajLogoFile = pathToLogo ;
    
    Image pajLogo = ImageFileFormat::loadFrom(pajLogoFile);
//    const Image pajLogo;
    
    enum wTimersID
    {
        drawingTimer = 0,
        settingsTimer = 1,
        bypassTimer = 2
    };
    
    int bypassTime;
    
    int wBufferButtonID;
    
    bool pajIsOn=true;
    int showPhaseBool=0;
    
//    DrawingThread drawingThread;
    bool sendBypassMessage;
    
    BubbleMessageComponent pajHint;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PajAuanalyserAudioProcessorEditor)
};
