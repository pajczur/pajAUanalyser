/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
//#include "DefinitionMacros.h"


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
    Rectangle<float> buttonsSpace;
    const Font wFontSize=12.0f;
    const Font wFontSize2=15.0f;
    
    
    //==============================================================================
    Rectangle<float> logoSpace;
    Image pajLogo = ImageCache::getFromMemory(pajAUanalyser::pajLogoYellow_png, pajAUanalyser::pajLogoYellow_pngSize);
    
    Rectangle<float> buffIconSpace[7];
    
//    Image icon1024  = ImageCache::getFromMemory(pajAUanalyser::buff_Icon_alt1_1024_png,  pajAUanalyser::buff_Icon_alt1_1024_pngSize);
//    Image icon2048  = ImageCache::getFromMemory(pajAUanalyser::buff_Icon_alt1_2048_png,  pajAUanalyser::buff_Icon_alt1_2048_pngSize);
//    Image icon4096  = ImageCache::getFromMemory(pajAUanalyser::buff_Icon_alt1_4096_png,  pajAUanalyser::buff_Icon_alt1_4096_pngSize);
//    Image icon8192  = ImageCache::getFromMemory(pajAUanalyser::buff_Icon_alt1_8192_png,  pajAUanalyser::buff_Icon_alt1_8192_pngSize);
//    Image icon16384 = ImageCache::getFromMemory(pajAUanalyser::buff_Icon_alt1_16384_png, pajAUanalyser::buff_Icon_alt1_16384_pngSize);
//    Image icon32768 = ImageCache::getFromMemory(pajAUanalyser::buff_Icon_alt1_32768_png, pajAUanalyser::buff_Icon_alt1_32768_pngSize);
//    Image icon65536 = ImageCache::getFromMemory(pajAUanalyser::buff_Icon_alt1_65536_png, pajAUanalyser::buff_Icon_alt1_65536_pngSize);

    
    //===================
    Label setBuffSizLabel;
    Label setResolutLabel;
    
    ToggleButton buffBut[7];
    uint8 &clickedFFTsizeID;
    
    uint8 fftSizeID = MUTE_IMPULSE_ID;
    
    
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
    
    Label hintWall;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PajAuanalyserAudioProcessorEditor)
};
