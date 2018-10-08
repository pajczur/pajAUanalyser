/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "SendRemote.h"
#include "ReceiveRemote.h"

#define margX   94
#define labX    10
#define bufLabX 82
#define bufButX 95
#define spaceX  38.5
#define settingsTimer 0
#define bypassTimer   1

#define wClickButton true
#define wDontClickButton false

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
    
    
    //==============================================================================
    void updateToggleState(Button* button, uint8 buttonID);
    void updateButtons(uint8 buttonID, bool toggleState, bool clickOrNot);
    void clickOFF();
    void clickShowPhase();
    void fftSizeClicked(uint8 buttonID);
    void clickDetectLatency();
    std::atomic<bool> &waitForSettings;
    
    
    //==============================================================================
    void timerCallback(int timerID) override;
    void settingsTimerCallback();
    void bypassTimerCallback();
    
    
    //==============================================================================
    void mouseDown( const MouseEvent & event ) override;
    void mouseUp( const MouseEvent & event ) override;
    
    
    //==============================================================================
    void setPajFFTsize(int fftSizeID);
    void sendFFTsizeToGenerator(uint8 fftSizeID);
    
    
    //==============================================================================
    void connectionMade() override;
    void connectionLost() override;
    void messageReceived( const MemoryBlock & message) override;
    
    
    //==============================================================================
private:
    Rectangle<float> logoSpace;
    Rectangle<float> buttonsSpace;
    const Font wFontSize=12.0f;
    const Font wFontSize2=15.0f;
    
    
    //==============================================================================
    const File pajLogoFile = String("/Users/wojtekpilwinski/Development/PublicRepositories/pajAUanalyser/Source/pajczurLogo.png");
    const Image pajLogo = ImageFileFormat::loadFrom(pajLogoFile);
    
    
    //===================
    Label setBuffSizLabel;
    Label setResolutLabel;
    
    ToggleButton buffBut[7];
    Label        buffButL[7];
    uint8 &clickedButtonID;

    
    /*
    //===================
    ToggleButton buff_1024;     Label buff_1024_Label;
    ToggleButton buff_2048;     Label buff_2048_Label;
    ToggleButton buff_4096;     Label buff_4096_Label;
    ToggleButton buff_8192;     Label buff_8192_Label;
    ToggleButton buff_16384;    Label buff_16384_Label;
    ToggleButton buff_32768;    Label buff_32768_Label;
    ToggleButton buff_65536;    Label buff_65536_Label;
     */
    uint8 fftSizeID;
    
    //===================
    TextButton pajOFFButton;
    TextButton pajResetButton;
    TextButton pajPhaseButton;
    int &showPhaseBool;
    
    
    //===================
    ToggleButton latencyDetect; Label latencyDetectLabel;
    ToggleButton pajUnwrap;     Label pajUnwrapLabel;
    
    bool isUnWrapToggled = false;
    bool isLatencyToggled = false;
   
    
    //==============================================================================
    SendRemote sendRemote;
    ReceiveRemote receiveRemote;
    
    
    
    //==============================================================================
    PajAuanalyserAudioProcessor& processor;
    float  &sampRate;
    float  &pajFFTsize;
    int    &wNumChannel;
    DrawingThread &drawingThread;
    
    MemoryBlock memoryMessage;
    bool wIsConnected;
    std::atomic<bool> &notifyFromDThread;
    std::atomic<bool> &holdDThread;
    std::atomic<bool> &pauseProc;
    std::atomic<bool> &isBypassed;
    std::atomic_flag &dataIsInUse;
    std::atomic<bool> settingsTimerUnlocked;
    std::atomic<int> &bypassTime;
    std::atomic<int> &bypassTreshold;
    bool sendBypassMessage = false;
    bool playBack=false;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PajAuanalyserAudioProcessorEditor)
};
