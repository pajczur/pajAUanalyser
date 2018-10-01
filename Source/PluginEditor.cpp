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
    : AudioProcessorEditor (&p), processor (p), waitForSettings(false), wBufferButtonID(0), pajIsOn(true), showPhaseBool(0)
{
    setResizable(true, true);
    setResizeLimits(565, 300, 10000, 10000);
    setSize (565, 300);
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
    
    pajOFFButton.setButtonText("Off");
    pajOFFButton.onClick = [this] { updateToggleState(&pajOFFButton, pajOffButtonID); };
    addAndMakeVisible(&pajOFFButton);
    pajResetButton.setButtonText("RESET");
    pajResetButton.onClick = [this] { updateToggleState(&pajResetButton, pajResetButtonID); };
    addAndMakeVisible(&pajResetButton);
    pajPhaseButton.setButtonText("PHASE");
    pajPhaseButton.onClick = [this] { updateToggleState(&pajPhaseButton, pajPhaseButtonID); };
    addAndMakeVisible(&pajPhaseButton);
    
    addAndMakeVisible(&pajUnwrap);
    pajUnwrap.setAlwaysOnTop(true);
    pajUnwrap.onClick = [this] { updateToggleState(&pajUnwrap, unWrapID); };
    addAndMakeVisible(&pajUnwrapLabel);
    pajUnwrapLabel.setJustificationType(Justification::right);
    pajUnwrapLabel.setText("unwrap", dontSendNotification);
    pajUnwrapLabel.setFont(wFontSize);
    pajUnwrapLabel.setAlwaysOnTop(true);
    
    pajOFFButton.setAlwaysOnTop(true);
    pajResetButton.setAlwaysOnTop(true);
    pajPhaseButton.setAlwaysOnTop(true);
    
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
    
    processor.dThread.drawPhase = false;
    processor.dThread.display_phase.setVisible(false);
    processor.dThread.graphAnalyserPhaL.setVisible(false);
    processor.dThread.graphAnalyserPhaR.setVisible(false);
    pajUnwrap.setVisible(false);
    pajUnwrapLabel.setVisible(false);
    latencyDetect.setVisible(false);
    latencyDetectLabel.setVisible(false);
    
    impulseMessage.setSize(1);
    
    resizableCorner->addMouseListener(this, true);
    
    drawButtons();
    startTimer(drawingTimer, 40);
    
    bypassTime = 0;
    
    startTimer(bypassTimer, 1000);
    
    pajHint.setAlpha(1.0f);
    addAndMakeVisible(&pajHint);
    pajHint.setAlwaysOnTop(true);
    
    if(processor.bufferID != 0)
    {
        toggleButtonByID(processor.bufferID);
    }
}



PajAuanalyserAudioProcessorEditor::~PajAuanalyserAudioProcessorEditor()
{
    if(!isConnected())
    {
        connectToSocket("127.0.0.1", 52425, 1000);
    }
    
    impulseMessage.fillWith(muteImpulseID);
    sendMessage(impulseMessage);
    sendBypassMessage = false;
    processor.isBypassed = true;
    
    processor.dThread.stopThread(1000);
    disconnect();
}

//==============================================================================
void PajAuanalyserAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(Colours::indigo);

    g.setColour (Colours::lightblue);

    g.drawRoundedRectangle(logoSpace, 10.f, 1.0f);
    g.drawImage(pajLogo, logoSpace);
    g.drawRoundedRectangle(buttonsSpace, 10.f, 1.0f);
}

void PajAuanalyserAudioProcessorEditor::resized()
{
    latencyDetect.setBounds      ( 75, 32+getHeight()/2, 19, 17);
    latencyDetectLabel.setBounds ( 50, 35+getHeight()/2, 30, 12);
    pajUnwrap.setBounds(140, 32+getHeight()/2, 19, 17);
    pajUnwrapLabel.setBounds(100, 33+getHeight()/2, 45, 12);
    
    pajIsOn=false; // Don't remember for what I used it, probably can be removed
    if(processor.settingsToApprove)
    {
        processor.settingsToApprove = false;
        sampRate = processor.getSampleRate();
        buffSize = processor.wBuffSize;
    }
 
    setGraphBounds(showPhaseBool);

    processor.dThread.notify();
    repaint();
}

void PajAuanalyserAudioProcessorEditor::updateToggleState(Button* button, int buttonID)
{
    if(button->getRadioGroupId() == bufferButtonRadioGroup)
    {
        if(waitForSettings)
        {
            button->setToggleState(false, dontSendNotification);
            leaveButtonsUntouched(rememberWhichButtonIsToggled);
                
        }
        else
        {
            if(buttonID==rememberWhichButtonIsToggled)
            {
                return;
            }
            else
            {
                if(button->getToggleState())
                {
                    waitForSettings = true;
                    processor.dThread.stopThread(1000);
                    processor.wStop = true;
                    wBufferButtonID = buttonID;
                    processor.bufferID = buttonID;
                    impulseMessage.fillWith(muteImpulseID);
                    tempRememberedButton = buttonID;
//                    disconnect();
                    if(connectToSocket("127.0.0.1", 52425, 1000))
                    {
                        rememberWhichButtonIsToggled = buttonID;
                        sendMessage(impulseMessage);
                        startTimer(settingsTimer, 1000);
                    }
                    else
                    {
                        button->setToggleState(false, dontSendNotification);
                        Rectangle<int> hintPos;
                        hintPos.setBounds(getMouseXYRelative().getX(), getMouseXYRelative().getY(), 1, 1);
                        AttributedString pajHintText("First launch pajAUanalyser - gen");
                        pajHintText.setColour(Colours::yellow);
                        pajHint.showAt(hintPos, pajHintText, 3000, true, false);
                        waitForSettings = false;
                        return;
                    }
                }
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
    
    if(buttonID == pajOffButtonID)
    {
        rememberWhichButtonIsToggled=0;
        processor.bufferID = 0;
        processor.dThread.stopThread(1000);
        turnOffAnal();
        processor.isMute = true;
    }
    
    if(buttonID == pajResetButtonID)
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
    
    if(buttonID == pajPhaseButtonID)
    {
        showPhaseBool = (++showPhaseBool) % 2;
        
        if(showPhaseBool==1)
        {
            processor.dThread.drawPhase = true;
            pajUnwrap.setVisible(true);
            pajUnwrapLabel.setVisible(true);
            latencyDetect.setVisible(true);
            latencyDetectLabel.setVisible(true);
            processor.dThread.display_phase.setVisible(true);
            processor.dThread.graphAnalyserPhaL.setVisible(true);
            processor.dThread.graphAnalyserPhaR.setVisible(true);
        }
        else
        {
            processor.dThread.drawPhase = false;
            pajUnwrap.setVisible(false);
            pajUnwrapLabel.setVisible(false);
            latencyDetect.setVisible(false);
            latencyDetectLabel.setVisible(false);
            processor.dThread.display_phase.setVisible(false);
            processor.dThread.graphAnalyserPhaL.setVisible(false);
            processor.dThread.graphAnalyserPhaR.setVisible(false);
        }
        
        setGraphBounds(showPhaseBool);
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
    
    if(timerID == bypassTimer)
    {
        if(bypassTime != processor.bypassTmier)
        {
            stopTimer(bypassTimer);
            bypassTime = processor.bypassTmier;
            startTimer(bypassTimer, bypassTime);
            return;
        }
        else
        {
            if(processor.bypassTreshold < 0)
            {
                if(sendBypassMessage)
                {
                    impulseMessage.fillWith(muteImpulseID);
                    sendMessage(impulseMessage);
                    sendBypassMessage = false;
                    processor.isBypassed = true;
                }
            }
            else
            {
                processor.bypassTreshold--;
                
                if(!sendBypassMessage)
                {
                    processor.isBypassed = false;
                    if(!processor.isMute)
                    {
                        sendBypassMessage = true;
                        impulseMessage.fillWith(rememberWhichButtonIsToggled);
                        sendMessage(impulseMessage);
                    }
                }
            }
        }
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
        
        if(!processor.isBypassed)
        {
            impulseMessage.fillWith(bufSizeID);
            sendMessage(impulseMessage);
        }
        
        processor.wStop = false;
        processor.dThread.startThread(0);
        
        processor.settingsToApprove = true;
        waitForSettings = false;
        processor.isMute = false;
    }
    
    
}


void PajAuanalyserAudioProcessorEditor::drawButtons()
{
//    int margX = (getWidth()/2)-215.0f;
    float margX = 94;
    float labX=10;
    float bufLabX=87-5;
    float bufButX=100-5;
    
    float spaceX=38.5;
    logoSpace.setBounds(margX-45, 5, 40, 40);
    buttonsSpace.setBounds(margX, 5.0f, 445.0f-3, 40.0f);
    setResolutLabel.setBounds( margX + labX,    23, 80, 15);
    setBuffSizLabel.setBounds( margX + labX,    10, 80, 15);
    
    pajOFFButton.setBounds        (margX + bufButX + 8*spaceX+2, 7.6f, 35, 35);
    pajResetButton.setBounds      (margX + bufButX + 8*spaceX-37, 7.6f, 38, 17);
    pajPhaseButton.setBounds(margX + bufButX + 8*spaceX-37, 25.6f, 38, 17);
    
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
    
    latencyDetectLabel.setColour(Label::textColourId, Colours::yellow);
    latencyDetect.setColour(ToggleButton::tickColourId, Colours::yellow);
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
    DBG("OTRZYMALEM WIAD");
    if(message[0] == 10)
    {
        updateToggleState(&pajOFFButton, pajOffButtonID);
//        turnOffAnal();
    }
    else if (message[0] == 2)
    {
        updateToggleState(&pajOFFButton, pajOffButtonID);
//        updateToggleState(&pajResetButton, pajResetButtonID);
    }
    else if (message[0] == 1)
    {
        toggleButtonByID(tempRememberedButton);
    }
    
    if(!isConnected())
        connectToSocket("127.0.0.1", 52425, 1000);
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
    
    impulseMessage.fillWith(muteImpulseID);
    sendMessage(impulseMessage);
//    disconnect();
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
    
    processor.dThread.graphAnalyserMagL.drawGraphSTATIC();
    processor.dThread.graphAnalyserPhaL.drawGraphSTATIC();
    processor.dThread.graphAnalyserMagR.drawGraphSTATIC();
    processor.dThread.graphAnalyserPhaR.drawGraphSTATIC();
    
    processor.dThread.graphAnalyserMagL.repaint();
    processor.dThread.graphAnalyserPhaL.repaint();
    processor.dThread.graphAnalyserMagR.repaint();
    processor.dThread.graphAnalyserPhaR.repaint();
}

void PajAuanalyserAudioProcessorEditor::mouseDown( const MouseEvent & event )
{
    if( event.originalComponent == resizableCorner.get() )
    {
        processor.dThread.isResizing = true;
    }
}

void PajAuanalyserAudioProcessorEditor::mouseUp( const MouseEvent & event )
{
    if( event.originalComponent == resizableCorner.get() )
    {
        processor.dThread.isResizing = false;
    }
}

void PajAuanalyserAudioProcessorEditor::leaveButtonsUntouched(int onButtonID)
{
    switch (onButtonID)
    {
        case b1024ID:
            buff_1024.setToggleState(true, dontSendNotification);
            break;
            
        case b2048ID:
            buff_2048.setToggleState(true, dontSendNotification);
            break;
            
        case b4096ID:
            buff_4096.setToggleState(true, dontSendNotification);
            break;
            
        case b8192ID:
            buff_8192.setToggleState(true, dontSendNotification);
            break;
            
        case b16384ID:
            buff_16384.setToggleState(true, dontSendNotification);
            break;
            
        case b32768ID:
            buff_32768.setToggleState(true, dontSendNotification);
            break;
            
        case b65536ID:
            buff_65536.setToggleState(true, dontSendNotification);
            break;
            
        default:
            return;
    }
}


void PajAuanalyserAudioProcessorEditor::setGraphBounds(int isShowPhase)
{
    int topMarg=55;
    int displayWidth = getWidth()-20;
    
    if(isShowPhase==1)
    {
        int graphOffsetY = (getHeight()/2.0)+(topMarg/2);
        int displayHeight= (getHeight()/2.0)-(topMarg/2)-8;
        
        processor.dThread.display_magni.setBounds (0, topMarg,      displayWidth, displayHeight);
        processor.dThread.display_phase.setBounds (0, graphOffsetY, displayWidth, displayHeight);
        
        int graphWidth = processor.dThread.display_magni.getDisplayWidth();
        int graphHeight= processor.dThread.display_magni.getDisplayHeight();
        
        processor.dThread.graphAnalyserMagL.setBounds(50, 23+topMarg, graphWidth, graphHeight);
        processor.dThread.graphAnalyserPhaL.setBounds(50, 23+graphOffsetY, graphWidth, graphHeight);
        
        if(processor.getTotalNumInputChannels()>1)
        {
            processor.dThread.graphAnalyserMagR.setBounds(/*graphMargX*/ 50, /*graphMargY*/ 23+topMarg, graphWidth, graphHeight);
            processor.dThread.graphAnalyserPhaR.setBounds(/*graphMargX*/ 50, /*graphMargY*/ 23+graphOffsetY, graphWidth, graphHeight);
        }
    }
    else
    {
        int displayHeight= 2*((getHeight()/2)-(topMarg/2))-9;
        
        processor.dThread.display_magni.setBounds (0, topMarg,      displayWidth, displayHeight);
        
        int graphWidth = processor.dThread.display_magni.getDisplayWidth();
        int graphHeight= processor.dThread.display_magni.getDisplayHeight();
        
        processor.dThread.graphAnalyserMagL.setBounds(50, 23+topMarg, graphWidth, graphHeight);
        
        if(processor.getTotalNumInputChannels()>1)
        {
            processor.dThread.graphAnalyserMagR.setBounds(/*graphMargX*/ 50, /*graphMargY*/ 23+topMarg, graphWidth, graphHeight);
        }
    }
}


void PajAuanalyserAudioProcessorEditor::toggleButtonByID(int buttonID)
{
    switch (buttonID)
    {
        case b1024ID:
            buff_1024.setToggleState(true, sendNotification);
            break;
            
        case b2048ID:
            buff_2048.setToggleState(true, sendNotification);
            break;
            
        case b4096ID:
            buff_4096.setToggleState(true, sendNotification);
            break;
            
        case b8192ID:
            buff_8192.setToggleState(true, sendNotification);
            break;
            
        case b16384ID:
            buff_16384.setToggleState(true, sendNotification);
            break;
            
        case b32768ID:
            buff_32768.setToggleState(true, sendNotification);
            break;
            
        case b65536ID:
            buff_65536.setToggleState(true, sendNotification);
            break;
            
        default:
            return;
    }
}
