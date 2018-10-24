/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "PajButtonsLookAndFeel.h"


//==============================================================================
class PajAuanalyserAudioProcessorEditor  : public AudioProcessorEditor, public MultiTimer, public InterprocessConnection
{
public:
    PajAuanalyserAudioProcessorEditor (PajAuanalyserAudioProcessor&);
    ~PajAuanalyserAudioProcessorEditor();

    
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
    void clickReset();
    void fftSizeClicked(uint8 buttonID);
    void clickDetectLatency();
    void clickUnWrap();
    std::atomic<bool> &waitForSettings;
    std::atomic<bool> waitForGenerator;
    std::atomic<bool> buttonWasClicked;
    ToggleButton* getPajButton(uint8 buttonID);
    
    
    //==============================================================================
    void timerCallback(int timerID) override;
    void settingsTimerCallback();
    void bypassTimerCallback();
    void waitForPrepToPlayTimerCallback();
    void hintTimerCallback();
    void msgReceivedTimerCallback();
    
    
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
    const Font wFontSize=12.0f;
    
    
    //==============================================================================
    Rectangle<float> logoSpace;
    Image pajLogo = ImageCache::getFromMemory(pajAUanalyser::pajLogoYellow_png, pajAUanalyser::pajLogoYellow_pngSize);
    
    PajButtonsLookAndFeel buffButtonsLook[NUM_OF_RADIO_BUTTONS];
    
    ToggleButton buffBut[NUM_OF_RADIO_BUTTONS];
    uint8 &clickedFFTsizeID;
    
    uint8 fftSizeID = MUTE_IMPULSE_ID;
    
    OffButtonLookAndFeel   offButtonLookAndFeel;
    ResetButtonLookAndFeel resetButtonLookAndFeel;
    PhaseButtonLookAndFeel phaseButtonLookAndFeel;
    
    //===================
    TextButton pajOFFButton;
    TextButton pajResetButton;
    TextButton pajPhaseButton;
    int  showMagniBool=1;
    int &showPhaseBool;
    std::atomic<bool> offWasClicked;
    
    
    //===================
    TextButton latencyDetect; Label latencyDetectLabel;
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
    
    bool shouldSaveGraphBounds = true;
    
    Label hintWallpaper;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PajAuanalyserAudioProcessorEditor)
};
