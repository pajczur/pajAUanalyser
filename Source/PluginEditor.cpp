/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PajAuanalyserAudioProcessorEditor::PajAuanalyserAudioProcessorEditor (PajAuanalyserAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    setResizable(true, true);
    setResizeLimits(520, 300, 10000, 10000);
    setSize (520, 400);
    isResized = false; // For ensure that window is update (see in timerCallback)
    
    logoSpace.setSize(40.0f, 40.0f);
    
    addAndMakeVisible(&setBuffSizLabel);
    
    setBuffSizLabel.setJustificationType(Justification::centredBottom);
    setBuffSizLabel.setText("BUFFER SIZE:", dontSendNotification);
    setBuffSizLabel.setFont(wFontSize2);
    setBuffSizLabel.setAlwaysOnTop(true);
    
    addAndMakeVisible(&setResolutLabel);
    setResolutLabel.setJustificationType(Justification::centredBottom);
    setResolutLabel.setText("(resolution):", dontSendNotification);
    setResolutLabel.setFont(wFontSize);
    setResolutLabel.setAlwaysOnTop(true);
    
    
    addAndMakeVisible(&buff_1024);
    buff_1024.setRadioGroupId(bufferButtonRadioGroup);
    buff_1024.onClick = [this] { updateToggleState(&buff_1024, b1024ID); };
    buff_1024.setAlwaysOnTop(true);
    addAndMakeVisible(&buff_1024_Label);
    buff_1024_Label.setJustificationType(Justification::centredBottom);
    buff_1024_Label.setText("1024", dontSendNotification);
    buff_1024_Label.setFont(wFontSize);
    buff_1024_Label.setAlwaysOnTop(true);
    
    addAndMakeVisible(&buff_2048);
    buff_2048.setRadioGroupId(bufferButtonRadioGroup);
    buff_2048.onClick = [this] { updateToggleState(&buff_2048, b2048ID); };
    buff_2048.setAlwaysOnTop(true);
    addAndMakeVisible(&buff_2048_Label);
    buff_2048_Label.setJustificationType(Justification::centredBottom);
    buff_2048_Label.setText("2048", dontSendNotification);
    buff_2048_Label.setFont(wFontSize);
    buff_2048_Label.setAlwaysOnTop(true);
    
    addAndMakeVisible(&buff_4096);
    buff_4096.setRadioGroupId(bufferButtonRadioGroup);
    buff_4096.onClick = [this] { updateToggleState(&buff_4096, b4096ID); };
    buff_4096.setAlwaysOnTop(true);
    addAndMakeVisible(&buff_4096_Label);
    buff_4096_Label.setJustificationType(Justification::centredBottom);
    buff_4096_Label.setText("4096", dontSendNotification);
    buff_4096_Label.setFont(wFontSize);
    buff_4096_Label.setAlwaysOnTop(true);
    
    addAndMakeVisible(&buff_8192);
    buff_8192.setRadioGroupId(bufferButtonRadioGroup);
    buff_8192.onClick = [this] { updateToggleState(&buff_8192, b8192ID); };
    buff_8192.setAlwaysOnTop(true);
    addAndMakeVisible(&buff_8192_Label);
    buff_8192_Label.setJustificationType(Justification::centredBottom);
    buff_8192_Label.setText("8192", dontSendNotification);
    buff_8192_Label.setFont(wFontSize);
    buff_8192_Label.setAlwaysOnTop(true);
    
    addAndMakeVisible(&buff_16384);
    buff_16384.setRadioGroupId(bufferButtonRadioGroup);
    buff_16384.onClick = [this] { updateToggleState(&buff_16384, b16384ID); };
    buff_16384.setAlwaysOnTop(true);
    addAndMakeVisible(&buff_16384_Label);
    buff_16384_Label.setJustificationType(Justification::centredBottom);
    buff_16384_Label.setText("16384", dontSendNotification);
    buff_16384_Label.setFont(wFontSize);
    buff_16384_Label.setAlwaysOnTop(true);
    
    addAndMakeVisible(&buff_32768);
    buff_32768.setRadioGroupId(bufferButtonRadioGroup);
    buff_32768.onClick = [this] { updateToggleState(&buff_32768, b32768ID); };
    buff_32768.setAlwaysOnTop(true);
    addAndMakeVisible(&buff_32768_Label);
    buff_32768_Label.setJustificationType(Justification::centredBottom);
    buff_32768_Label.setText("32768", dontSendNotification);
    buff_32768_Label.setFont(wFontSize);
    buff_32768_Label.setAlwaysOnTop(true);
    
    addAndMakeVisible(&buff_65536);
    buff_65536.setRadioGroupId(bufferButtonRadioGroup);
    buff_65536.onClick = [this] { updateToggleState(&buff_65536, b65536ID); };
    buff_65536.setAlwaysOnTop(true);
    addAndMakeVisible(&buff_65536_Label);
    buff_65536_Label.setJustificationType(Justification::centredBottom);
    buff_65536_Label.setText("65536", dontSendNotification);
    buff_65536_Label.setFont(wFontSize);
    buff_65536_Label.setAlwaysOnTop(true);
    
    addAndMakeVisible(&latencyDetect);
    latencyDetect.onClick = [this] { updateToggleState(&latencyDetect, latencyID); };
    latencyDetect.setAlwaysOnTop(true);
    addAndMakeVisible(&latencyDetectLabel);
    latencyDetectLabel.setJustificationType(Justification::centredBottom);
    latencyDetectLabel.setText("LAT.", dontSendNotification);
    latencyDetectLabel.setFont(wFontSize);
    latencyDetectLabel.setAlwaysOnTop(true);
    
    pajOff.setButtonText("OFF");
    pajOff.onClick = [this] { updateToggleState(&pajOff, pajOffID); };
    addAndMakeVisible(&pajOff);
    pajReset.setButtonText("RESET");
    pajReset.onClick = [this] { updateToggleState(&pajReset, pajResetID); };
    addAndMakeVisible(&pajReset);
    
    addAndMakeVisible(&pajUnwrap);
    pajUnwrap.setAlwaysOnTop(true);
    pajUnwrap.onClick = [this] { updateToggleState(&pajUnwrap, unWrapID); };
    addAndMakeVisible(&pajUnwrapLabel);
    pajUnwrapLabel.setJustificationType(Justification::right);
    pajUnwrapLabel.setText("unwrap", dontSendNotification);
    pajUnwrapLabel.setFont(wFontSize);
    pajUnwrapLabel.setAlwaysOnTop(true);
    
    pajOff.setAlwaysOnTop(true);
    pajReset.setAlwaysOnTop(true);
    
    processor.dThread.display_magni.graphTitle = "Magnitude";
    processor.dThread.display_phase.graphTitle  = "Phase shift";
    
    addAndMakeVisible(&processor.dThread.display_magni);
    addAndMakeVisible(&processor.dThread.display_phase);

    channelQuantity = processor.getTotalNumInputChannels();
    sampRate = processor.getSampleRate();
    buffSize = processor.wBuffSize;
    
    addAndMakeVisible(&processor.dThread.graphAnalyserMagL);
    addAndMakeVisible(&processor.dThread.graphAnalyserPhaL);
    
    if(channelQuantity>1)
    {
        addAndMakeVisible(&processor.dThread.graphAnalyserMagR);
        addAndMakeVisible(&processor.dThread.graphAnalyserPhaR);
    }
    
    impulseMessage.setSize(1);
    
    wBufferButtonID=0;
    
    pajIsOn = true;
    
    drawButtons();
    startTimer(drawingTimer, 40);
}



PajAuanalyserAudioProcessorEditor::~PajAuanalyserAudioProcessorEditor()
{
    processor.dThread.stopThread(1000);
    disconnect();
}

//==============================================================================
void PajAuanalyserAudioProcessorEditor::paint (Graphics& g)
{
//    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    
    g.fillAll(Colours::indigo);

    g.setColour (Colours::lightblue);
    
//    g.drawRect(margX, 5, 600, 40);
    g.drawRoundedRectangle(logoSpace, 10.f, 1.0f);
    g.drawImage(pajLogo, logoSpace);
    g.drawRoundedRectangle(buttonsSpace, 10.f, 1.0f);
}

void PajAuanalyserAudioProcessorEditor::resized()
{
    pajUnwrap.setBounds(getWidth()-51, 32+getHeight()/2, 19, 17);
    pajUnwrapLabel.setBounds(getWidth()-95, 34+getHeight()/2, 50, 12);
    
    pajIsOn=false; // Don't remember for what I used it, probably can be emoved
    if(processor.settingsToApprove)
    {
        processor.settingsToApprove = false;
        sampRate = processor.getSampleRate();
        buffSize = processor.wBuffSize;
    }
    
    int topMarg=55;
    int graphOffsetY = (getHeight()/2.0)+(topMarg/2);
    int displayWidth = getWidth()-20;
    int displayHeight= (getHeight()/2.0)-3-(topMarg/2)-5;
    
    processor.dThread.display_magni.setBounds (0, topMarg,      displayWidth, displayHeight);
    processor.dThread.display_phase.setBounds (0, graphOffsetY, displayWidth, displayHeight);

    if(!pajIsOn && processor.dThread.isSystemReady)
    {
        processor.dThread.graphAnalyserMagL.prepareStaticPath();
        processor.dThread.graphAnalyserPhaL.prepareStaticPath();
        if(processor.getTotalNumInputChannels()>1)
        {
            processor.dThread.graphAnalyserMagR.prepareStaticPath();
            processor.dThread.graphAnalyserPhaR.prepareStaticPath();
        }
    }
    
//    int graphMargX = processor.dThread.display_magni.getDisplayMargXLeft();
//    int graphMargY = processor.dThread.display_magni.getDisplayMargYTop();
    int graphWidth = processor.dThread.display_magni.getDisplayWidth();
    int graphHeight= processor.dThread.display_magni.getDisplayHeight();
    
    processor.dThread.graphAnalyserMagL.setBounds(/*graphMargX*/ 50, /*graphMargY*/ 23+topMarg, graphWidth, graphHeight);
    processor.dThread.graphAnalyserPhaL.setBounds(/*graphMargX*/ 50, /*graphMargY*/ 23+graphOffsetY, graphWidth, graphHeight);
    
    if(processor.getTotalNumInputChannels()>1)
    {
        processor.dThread.graphAnalyserMagR.setBounds(/*graphMargX*/ 50, /*graphMargY*/ 23+topMarg, graphWidth, graphHeight);
        processor.dThread.graphAnalyserPhaR.setBounds(/*graphMargX*/ 50, /*graphMargY*/ 23+graphOffsetY, graphWidth, graphHeight);
    }

    repaint();
}

void PajAuanalyserAudioProcessorEditor::updateToggleState(Button* button, int buttonID)
{
    if(button->getRadioGroupId() == bufferButtonRadioGroup)
    {
        if(button->getToggleState())
        {
            processor.dThread.stopThread(1000);
            processor.wStop = true;
            wBufferButtonID = buttonID;
            impulseMessage.fillWith(muteImpulseID);
            
            if(connectToSocket("127.0.0.1", 52425, 1000))
            {
                sendMessage(impulseMessage);
                startTimer(settingsTimer, 1000);
            }
            else
            {
                return;
            }
        }
    }
    
    if(buttonID == latencyID)
    {
        if(latencyDetect.getToggleState())
        {
            processor.wDetectLatency = true;
        }
        else
        {
            processor.wDetectLatency = false;
        }
    }
    
    if(buttonID == pajOffID)
    {
        processor.dThread.stopThread(1000);
        turnOffAnal();
        impulseMessage.fillWith(muteImpulseID);
        sendMessage(impulseMessage);
        disconnect();
    }
    
    if(buttonID == pajResetID)
    {
        if(!pajIsOn)
            resetAnalGraph();
    }
    
    if(buttonID == unWrapID)
    {
        if(pajUnwrap.getToggleState())
        {
            processor.dThread.graphAnalyserPhaL.pajUnwrapping = true;
            processor.dThread.graphAnalyserPhaR.pajUnwrapping = true;
        }
        else
        {
            processor.dThread.graphAnalyserPhaL.pajUnwrapping = false;
            processor.dThread.graphAnalyserPhaR.pajUnwrapping = false;
        }
    }
}


void PajAuanalyserAudioProcessorEditor::timerCallback(int timerID)
{
    if(!isResized)
    {
        resized();
        isResized=true;
    }

    
    if(timerID == settingsTimer)
    {
        stopTimer(settingsTimer);
        setBufferSize(wBufferButtonID);
        wBufferButtonID = 0;
    }
}


void PajAuanalyserAudioProcessorEditor::setBufferSize(int bufSizeID)
{
    int tempBuffsize=0;
    
    switch (bufSizeID)
    {
        case b1024ID:
            tempBuffsize = 1024;
            break;
            
        case b2048ID:
            tempBuffsize = 2048;
            break;
            
        case b4096ID:
            tempBuffsize = 4096;
            break;
            
        case b8192ID:
            tempBuffsize = 8192;
            break;
            
        case b16384ID:
            tempBuffsize = 16384;
            break;
            
        case b32768ID:
            tempBuffsize = 32768;
            break;
            
        case b65536ID:
            tempBuffsize = 65536;
            break;
            
        default:
            break;
    }
    
    if(tempBuffsize>0)
    {
        processor.wSettings(processor.wSampleRate, tempBuffsize);
        impulseMessage.fillWith(bufSizeID);
        sendMessage(impulseMessage);
        
        processor.wStop = false;
        processor.dThread.startThread(0);
        
        processor.settingsToApprove = true;
    }
    
    
}


void PajAuanalyserAudioProcessorEditor::drawButtons()
{
//    int margX = (getWidth()/2)-215.0f;
    float margX = 49;
    float labX=10;
    float bufLabX=87-5;
    float bufButX=100-5;
    
    float spaceX=38.5;
    logoSpace.setBounds(4.5, 5, 40, 40);
    buttonsSpace.setBounds(margX, 5.0f, 445.0f-3, 40.0f);
    setResolutLabel.setBounds( margX + labX,    23, 80, 15);
    setBuffSizLabel.setBounds( margX + labX,    10, 80, 15);
    
    pajOff.setBounds(margX + bufButX + 8*spaceX-3, 7.6f, 40, 17);
    pajReset.setBounds(margX + bufButX + 8*spaceX-3, 25.6f, 40, 17);
    
    buff_1024_Label.setBounds ( margX + bufLabX + 0*spaceX-2, 11, 50, 12);
    buff_1024.setBounds       ( margX + bufButX + 0*spaceX, 23, 19, 17);
    
    buff_2048_Label.setBounds ( margX + bufLabX + 1*spaceX-1, 11, 50, 12);
    buff_2048.setBounds       ( margX + bufButX + 1*spaceX, 23, 19, 17);
    
    buff_4096_Label.setBounds ( margX + bufLabX + 2*spaceX-1, 11, 50, 12);
    buff_4096.setBounds       ( margX + bufButX + 2*spaceX, 23, 19, 17);
    
    buff_8192_Label.setBounds ( margX + bufLabX + 3*spaceX-2, 11, 50, 12);
    buff_8192.setBounds       ( margX + bufButX + 3*spaceX, 23, 19, 17);
    
    buff_16384_Label.setBounds( margX + bufLabX + 4*spaceX-2, 11, 50, 12);
    buff_16384.setBounds      ( margX + bufButX + 4*spaceX, 23, 19, 17);
    
    buff_32768_Label.setBounds( margX + bufLabX + 5*spaceX-2, 11, 50, 12);
    buff_32768.setBounds      ( margX + bufButX + 5*spaceX, 23, 19, 17);
    
    buff_65536_Label.setBounds( margX + bufLabX + 6*spaceX-1, 11, 50, 12);
    buff_65536.setBounds      ( margX + bufButX + 6*spaceX, 23, 19, 17);
    
    latencyDetectLabel.setColour(Label::textColourId, Colours::red);
    latencyDetect.setColour(ToggleButton::tickColourId, Colours::red);
    latencyDetectLabel.setBounds ( margX + bufLabX + 7*spaceX-35, 11, 120, 12);
    latencyDetect.setBounds      ( margX + bufButX + 7*spaceX, 23, 19, 17);
}


void PajAuanalyserAudioProcessorEditor::connectionMade()
{
//    DBG("POLACZYLO SIE AU");
}

void PajAuanalyserAudioProcessorEditor::connectionLost()
{
//    DBG("ROZLACZYLO SIE AU");
}

void PajAuanalyserAudioProcessorEditor::messageReceived( const MemoryBlock & message)
{
    if(message[0] == 10)
    {
        turnOffAnal();
    }
}


void PajAuanalyserAudioProcessorEditor::turnOffAnal()
{
    pajIsOn = false;
    processor.wStop = true;
    
    buff_1024.setToggleState(false, dontSendNotification);
    buff_2048.setToggleState(false, dontSendNotification);
    buff_4096.setToggleState(false, dontSendNotification);
    buff_8192.setToggleState(false, dontSendNotification);
    buff_16384.setToggleState(false, dontSendNotification);
    buff_32768.setToggleState(false, dontSendNotification);
    buff_65536.setToggleState(false, dontSendNotification);
}

void PajAuanalyserAudioProcessorEditor::resetAnalGraph()
{
    int dataSize = (int)processor.dThread.graphAnalyserMagL.dataSize;
    
    for(int i=0; i<dataSize; i++)
    {
        processor.dThread.graphAnalyserMagL.drawStaticY[i] = 1.0f;
        processor.dThread.graphAnalyserPhaL.drawStaticY[i] = 0.0f;
        processor.dThread.graphAnalyserMagR.drawStaticY[i] = 1.0f;
        processor.dThread.graphAnalyserPhaR.drawStaticY[i] = 0.0f;
    }
    
    processor.dThread.graphAnalyserMagL.fftGraphPath.clear();
    processor.dThread.graphAnalyserPhaL.fftGraphPath.clear();
    processor.dThread.graphAnalyserMagR.fftGraphPath.clear();
    processor.dThread.graphAnalyserPhaR.fftGraphPath.clear();
    
    processor.dThread.graphAnalyserMagL.prepareStaticPath();
    processor.dThread.graphAnalyserPhaL.prepareStaticPath();
    processor.dThread.graphAnalyserMagR.prepareStaticPath();
    processor.dThread.graphAnalyserPhaR.prepareStaticPath();
    
    processor.dThread.graphAnalyserMagL.repaint();
    processor.dThread.graphAnalyserPhaL.repaint();
    processor.dThread.graphAnalyserMagR.repaint();
    processor.dThread.graphAnalyserPhaR.repaint();
}
