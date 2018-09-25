/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DrawingThread.h"
#include <complex>

//==============================================================================
/**
*/
class PajAuanalyserAudioProcessor  : public AudioProcessor
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
    
    Thread *stopMessage = nullptr;
    
    bool isConnectionSuccesful;
    
    DrawingThread dThread;
    
    bool settingsToApprove = true;
    int tempppp=0;
    std::atomic<int> isProcBlockRun;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PajAuanalyserAudioProcessor)
};
