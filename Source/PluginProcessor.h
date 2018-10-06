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
class PajAuanalyserAudioProcessor  : public AudioProcessor, public InterprocessConnection, public Timer
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
    
    void updateFFTSize();
    void resetAnalGraph();
    
    void connectionMade() override;
    void connectionLost() override;
    void messageReceived( const MemoryBlock & message) override;
    
    void timerCallback() override;
    
    
    //==============================================================================
    float pajFFTsize;
    float wSampleRate;
    
    int wNumInputChannel;

    float realBuffSize;

    std::vector<float> tempInput[2];
    int sampleCount[2];
    bool isAnySignal[2];
    
public:
    bool isGlobalBuffer;
    bool wDetectLatency;
    std::atomic<bool> wIsPaused;
    std::atomic_flag dataIsInUse;
    
    int bufferID = 0;
    
    bool isConnectionSuccesful;
    
    DrawingThread dThread;
    
    bool settingsToApprove = true;
    int tempppp=0;
    std::atomic<int> bypassTreshold;
    
    std::atomic<int> bypassTime;
    
    std::atomic<bool> isBypassed;
    
    std::atomic<int> buttonID;

    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PajAuanalyserAudioProcessor)
};
