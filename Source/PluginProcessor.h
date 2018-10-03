/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DrawingThread.h"

//==============================================================================
/**
*/
class PajAuanalyserAudioProcessor  : public AudioProcessor, public InterprocessConnection
{
public:
    //==============================================================================
    PajAuanalyserAudioProcessor();
    ~PajAuanalyserAudioProcessor();
    
    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    void wSettings(double sampleRate, int samplesPerBlock);
    
    void connectionMade() override;
    void connectionLost() override;
    void messageReceived( const MemoryBlock & message) override;
    std::atomic<bool> isMessageReceived;

    float wBuffSize;
    
    int inputChannelsQuantity;

    int realBuffSize;
    double wSampleRate;

    std::vector<float> tempInput[2];
    int sampleCount[2];
    bool isAnySignal[2];
    
    
private:
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
    
public:
    bool pluginWasOpen;
    bool isGlobalBuffer;
    bool wDetectLatency;
    std::atomic<bool> wStop;
    
    int bufferID = 0;
    
    Thread *stopMessage = nullptr;
    
    bool isConnectionSuccesful;
    
    DrawingThread dThread;
    
    bool settingsToApprove = true;
    int tempppp=0;
    std::atomic<int> bypassTreshold;
    
    std::atomic<int> bypassTmier;
    
    std::atomic<bool> isBypassed;
    std::atomic<bool> isMute;
    
    std::atomic<bool> isGenON;
    
    std::atomic<int> buttonID;
    
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
        pajOffButtonID      = 110,
        pajResetButtonID    = 901,
        pajPhaseButtonID    = 902,
        bufferButtonRadioGroup = 1000
    };
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PajAuanalyserAudioProcessor)
};
