/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PajAuanalyserAudioProcessor::PajAuanalyserAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), pajFFTsize(1024.0f), isGlobalBuffer(true), wDetectLatency(true), wIsPaused(true), isBypassed(true)
#endif
{
    dataIsInUse.clear();
    dThread.isSystemReady = false;
    dThread.isHold  = true;
}

PajAuanalyserAudioProcessor::~PajAuanalyserAudioProcessor() {
    bypassTreshold=-1;
}

//==============================================================================
const String PajAuanalyserAudioProcessor::getName() const {
    return JucePlugin_Name;
}

bool PajAuanalyserAudioProcessor::acceptsMidi() const {
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PajAuanalyserAudioProcessor::producesMidi() const {
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PajAuanalyserAudioProcessor::isMidiEffect() const {
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PajAuanalyserAudioProcessor::getTailLengthSeconds() const {
    return 0.0;
}

int PajAuanalyserAudioProcessor::getNumPrograms() {
    return 1;
}

int PajAuanalyserAudioProcessor::getCurrentProgram() {
    return 0;
}

void PajAuanalyserAudioProcessor::setCurrentProgram (int index) {
}

const String PajAuanalyserAudioProcessor::getProgramName (int index) {
    return {};
}

void PajAuanalyserAudioProcessor::changeProgramName (int index, const String& newName) {
}

//==============================================================================
void PajAuanalyserAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock) {
    waitForSettings=false;
    realBuffSize = samplesPerBlock;
    wSampleRate = sampleRate;
//    DBG("Buffer SIZE " << samplesPerBlock << " AND " << realBuffSize);
    bypassTime = round(((double)samplesPerBlock * 1000.0f) / wSampleRate);
    
    wNumInputChannel  = (getTotalNumInputChannels()>1)?2:1;
    
    
    updateFFTSize();
//    resetAnalGraph();
    
    settingsToApprove = true;
}

void PajAuanalyserAudioProcessor::releaseResources() {
    
    
    
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PajAuanalyserAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const {
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif


void PajAuanalyserAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages) {
    bypassTreshold=1;

    if(!isBypassed)
    {
        auto totalNumOutputChannels = getTotalNumOutputChannels();
        
        for (auto k = wNumInputChannel; k < totalNumOutputChannels; ++k)
            buffer.clear (k, 0, buffer.getNumSamples());
        
        for (int channel = 0; channel < wNumInputChannel; ++channel)
        {
            float* channelData = buffer.getWritePointer (channel);
            
//            for(int i=0; i<realBuffSize; ++i)
            for(int i=0; i<buffer.getNumSamples(); ++i)
            {
                tempInput[channel][sampleCount[channel]]  = buffer.getSample(channel, i);
                
                channelData[i] = 0.0f; // This make silence
                
                if(!wIsPaused && !dataIsInUse.test_and_set())
                {
                    if(isAnySignal[channel]==false)
                    {
                        if(tempInput[channel][sampleCount[channel]] > 0.000001f)
                            isAnySignal[channel] = true;
                    }
                    
                    if(wDetectLatency)
                    {
                        if(tempInput[channel][sampleCount[channel]] > tempInput[channel][0])
                        {
                            tempInput[channel][0] = tempInput[channel][sampleCount[channel]];
                            sampleCount[channel] = 0;
                        }
                    }

                    sampleCount[channel]++;
                    
                    if(sampleCount[channel]>=pajFFTsize)
                    {
                        sampleCount[channel]=0;
                        
                        if(isAnySignal[channel])
                        {
                            isAnySignal[channel]=false;
                            dThread.wInput[channel] = tempInput[channel];
                            dThread.sourceIsReady[channel] = true;
                            dThread.notify();
                        }
                    }
                    
                    dataIsInUse.clear();
                }
            }
        }
    }
}

 
//==============================================================================
bool PajAuanalyserAudioProcessor::hasEditor() const {
    return true;
}

AudioProcessorEditor* PajAuanalyserAudioProcessor::createEditor() {
    return new PajAuanalyserAudioProcessorEditor (*this);
}

//==============================================================================
void PajAuanalyserAudioProcessor::getStateInformation (MemoryBlock& destData) {
}

void PajAuanalyserAudioProcessor::setStateInformation (const void* data, int sizeInBytes) {
}

void PajAuanalyserAudioProcessor::updateFFTSize() {
    
    dThread.pajSettings(wNumInputChannel, pajFFTsize, wSampleRate);
    
    for(int channel=0; channel<wNumInputChannel; ++channel)
    {
        tempInput[channel].resize(pajFFTsize, 0.0f);
        sampleCount[channel]  = 0;
        isAnySignal[channel]  = false;
    }
    
    dThread.isSystemReady = true;
}



void PajAuanalyserAudioProcessor::timerCallback()
{
    stopTimer();
    isBypassed=true;
    waitForSettings=false;
}

void PajAuanalyserAudioProcessor::setSize(int pajW, int pajH)
{
    wWidth = pajW;
    wHeight = pajH;
}


//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PajAuanalyserAudioProcessor();
}
