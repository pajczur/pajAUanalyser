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
                       )
#endif
{
    dThread.isSystemReady = false;
    pluginWasOpen = false;
    isGlobalBuffer = true;
    wDetectLatency = false;
    wStop=true;
    isMute = true;
}

PajAuanalyserAudioProcessor::~PajAuanalyserAudioProcessor()
{
    dThread.stopThread(1000);
    bypassTreshold=-1;
}

//==============================================================================
const String PajAuanalyserAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PajAuanalyserAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PajAuanalyserAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PajAuanalyserAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PajAuanalyserAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PajAuanalyserAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PajAuanalyserAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PajAuanalyserAudioProcessor::setCurrentProgram (int index)
{
}

const String PajAuanalyserAudioProcessor::getProgramName (int index)
{
    return {};
}

void PajAuanalyserAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void PajAuanalyserAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    realBuffSize = samplesPerBlock;
    wSampleRate = sampleRate;
    
    inputChannelsQuantity  = 1;
    if(getTotalNumInputChannels()>1)
        inputChannelsQuantity=2;
    
    if(!pluginWasOpen)
    {
        pluginWasOpen = true;
        wSettings(wSampleRate, 1024);
    }
    else
    {
        wSettings(wSampleRate, (int)wBuffSize);
    }
    
    
    settingsToApprove = true;
}

void PajAuanalyserAudioProcessor::releaseResources()
{
    
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PajAuanalyserAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif


void PajAuanalyserAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    bypassTreshold=1;
    if(!isBypassed && !isMute)
    {
        auto totalNumOutputChannels = getTotalNumOutputChannels();
        
        for (auto k = inputChannelsQuantity; k < totalNumOutputChannels; ++k)
            buffer.clear (k, 0, buffer.getNumSamples());
        
        
        for (int channel = 0; channel < inputChannelsQuantity; ++channel)
        {
            float* channelData = buffer.getWritePointer (channel);
            
            for(int i=0; i<realBuffSize; ++i)
            {
                tempInput[channel][sampleCount[channel]]  = buffer.getSample(channel, i);
                
                
                channelData[i] = 0.0f; // This make silence
                
                if(!wStop)
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
                    
                    if(sampleCount[channel]>=wBuffSize)
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
                }
            }
        }
    }
}

 
//==============================================================================
bool PajAuanalyserAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* PajAuanalyserAudioProcessor::createEditor()
{
    return new PajAuanalyserAudioProcessorEditor (*this);
}

//==============================================================================
void PajAuanalyserAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void PajAuanalyserAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void PajAuanalyserAudioProcessor::wSettings(double sampleRate, int samplesPerBlock)
{
    dThread.isSystemReady = false;
    dThread.sourceIsReady[left] = false;
    dThread.sourceIsReady[right] = false;
    dThread.totalNumInputChannels = getTotalNumInputChannels();
    
    wBuffSize = (float)samplesPerBlock;

    dThread.radix2_FFT.wSettings((float)wSampleRate, wBuffSize);
    
    
    dThread.wOutput.resize(inputChannelsQuantity);
    
    for(int channel=0; channel<inputChannelsQuantity; ++channel)
    {
        dThread.wOutput[channel].resize(2);
        dThread.wOutput[channel][wMag].resize((int)wBuffSize, 1.0f);
        dThread.wOutput[channel][wPha].resize((int)wBuffSize, 0.0f);
    }
    
    double buuuSiii = wBuffSize;
    
    dThread.display_magni.channelQuantity = getTotalNumInputChannels();
    dThread.display_phase.channelQuantity = getTotalNumInputChannels();
    dThread.display_magni.setNyquist(getSampleRate()/2.0);
    dThread.display_phase.setNyquist(getSampleRate()/2.0);
    
    dThread.graphAnalyserMagL.setChannel(left, wMag);
    dThread.graphAnalyserPhaL.setChannel(left, wPha);
    dThread.graphAnalyserMagL.wSettings(dThread.wOutput[left][wMag], wBuffSize);
    dThread.graphAnalyserPhaL.wSettings(dThread.wOutput[left][wPha], wBuffSize);
    dThread.graphAnalyserMagL.setWindScaleSettings(sampleRate, buuuSiii);
    dThread.graphAnalyserPhaL.setWindScaleSettings(sampleRate, buuuSiii);
    
    if(inputChannelsQuantity>1)
    {
        dThread.graphAnalyserMagR.setChannel(right, wMag);
        dThread.graphAnalyserPhaR.setChannel(right, wPha);
        dThread.graphAnalyserMagR.wSettings(dThread.wOutput[right][wMag], wBuffSize);
        dThread.graphAnalyserPhaR.wSettings(dThread.wOutput[right][wPha], wBuffSize);
        dThread.graphAnalyserMagR.setWindScaleSettings(sampleRate, buuuSiii);
        dThread.graphAnalyserPhaR.setWindScaleSettings(sampleRate, buuuSiii);
    }

    dThread.wInput[left].resize(wBuffSize, 0.0f);
    dThread.wInput[right].resize(wBuffSize, 0.0f);
    tempInput[left].resize(wBuffSize, 0.0f);
    tempInput[right].resize(wBuffSize, 0.0f);
    
    sampleCount[left]  = 0;
    sampleCount[right] = 0;
    
    isAnySignal[left]  = false;
    isAnySignal[right] = false;
    
    bypassTmier = round(((float)realBuffSize * 1000.0f) / wSampleRate);
    
    dThread.isSystemReady = true;
}


//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PajAuanalyserAudioProcessor();
}
