/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

#define margX   94
#define labX    10
#define bufLabX 82
#define bufButX 95
#define spaceX  38.5
#define settingsTimer 0
#define bypassTimer   1
#define waitForPrepToPlay 2
#define refreshMessageReceivedBool 50

#define wClick true
#define wDontClick false
#define wButtonON  true
#define wButtonOFF false

//==============================================================================
class PajAuanalyserAudioProcessorEditor  : public AudioProcessorEditor, public MultiTimer, public InterprocessConnection
{
public:
    PajAuanalyserAudioProcessorEditor (PajAuanalyserAudioProcessor&);
    ~PajAuanalyserAudioProcessorEditor();

    BubbleMessageComponent pajHint;
    Rectangle<int> hintPos;
    AttributedString pajHintText;
    bool showHint = true;
    void showBubbleHint(bool shouldShowHint);


    
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void pajDrawAllComponents();
    void drawProcComponents();
    
    
    //==============================================================================
    void updateToggleState(Button* button, uint8 buttonID);
    void updateButtons(uint8 buttonID, bool toggleState, bool clickOrNot);
    void clickOFF();
    void clickShowPhase();
    void fftSizeClicked(uint8 buttonID);
    void clickDetectLatency();
    void clickUnWrap();
    std::atomic<bool> &waitForSettings;
    ToggleButton* getPajButton(uint8 buttonID);
    
    
    //==============================================================================
    void timerCallback(int timerID) override;
    void settingsTimerCallback();
    void bypassTimerCallback();
    void waitForPrepToPlayTimerCallback();
    
    
    //==============================================================================
    void mouseDown( const MouseEvent & event ) override;
    void mouseUp( const MouseEvent & event ) override;
    
    
    //==============================================================================
    bool setPajFFTsize(int fftSizeID);
    void sendFFTsizeToGenerator(uint8 fftSizeID);
    
    
    //==============================================================================
    void connectionMade() override;
    void connectionLost() override;
    void messageReceived( const MemoryBlock & message) override;
    
    
    //==============================================================================
private:
    Rectangle<float> buttonsSpace;
    const Font wFontSize=12.0f;
    const Font wFontSize2=15.0f;
    
    
    //==============================================================================
    Rectangle<float> logoSpace;
    Image pajLogo = ImageCache::getFromMemory(pajAUanalyser::pajLogoYellow_png, pajAUanalyser::pajLogoYellow_pngSize);
    
    
    //===================
    Label setBuffSizLabel;
    Label setResolutLabel;
    
    ToggleButton buffBut[7];
    Label        buffButL[7];
    uint8 &clickedFFTsizeID;
    
    uint8 fftSizeID;
    bool &blockButtons;
    
    //===================
    TextButton pajOFFButton;
    TextButton pajResetButton;
    TextButton pajPhaseButton;
    int &showPhaseBool;
    
    
    //===================
    TextButton latencyDetect; Label latencyDetectLabel;
//    ToggleButton latencyDetect; Label latencyDetectLabel;
    ToggleButton pajUnwrap;     Label pajUnwrapLabel;
    
    bool &isUnWrapToggled;
    
    
    //==============================================================================
    PajAuanalyserAudioProcessor& processor;
    DrawingThread &drawingThread;
    
    MemoryBlock memoryMessage;
    bool wIsConnected;
    std::atomic<bool> &notifyFromDThread;
    std::atomic_flag &dataIsInUse;
    std::atomic<bool> settingsTimerUnlocked;
    bool sendBypassMessage = false;
    std::atomic<bool> playBack;
    
    int &wWidth;
    int &wHeight;
    
    std::atomic<bool> pajMessageReceived;
    
    std::atomic<bool> isGenActive;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PajAuanalyserAudioProcessorEditor)
};
