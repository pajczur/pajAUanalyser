/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"



//==============================================================================
//== C O N S T R U C T O R S ===================================================
//==============================================================================
PajAuanalyserAudioProcessorEditor::PajAuanalyserAudioProcessorEditor (PajAuanalyserAudioProcessor& p) :
                                AudioProcessorEditor (&p),
                                waitForSettings(p.waitForSettings),
                                clickedFFTsizeID(p.clickedFFTsizeID),
                                blockButtons(p.blockButtons),
                                showPhaseBool(p.showPhaseBool),
                                isUnWrapToggled(p.isUnWrapToggled),
                                processor (p),
                                drawingThread(p.drawingThread),
                                notifyFromDThread(p.drawingThread.notifyEditor),
                                dataIsInUse(p.dataIsInUse),
                                playBack(false),
                                wWidth(p.wWidth),
                                wHeight(p.wHeight)
{
    pajMessageReceived=false;
    setResizable(true, true);
    setSize (wWidth, wHeight);
    setResizeLimits(565, 300, 10000, 10000);
    resizableCorner->addMouseListener(this, true);
    
    
    // == H I N T == B U B B L E ==
    pajHint.setAlpha(1.0f);
    addAndMakeVisible(&pajHint);
    pajHint.setAlwaysOnTop(true);
    pajHintText.setText("1) pajAUanalyser - gen myst be lounched and ON\n2) Be sure to hit play\n3) Be sure there is any audio source on measured track");
    pajHintText.setWordWrap(AttributedString::WordWrap::none);
    pajHintText.setColour(Colours::yellow);
    
    pajDrawAllComponents();
    
    memoryMessage.setSize(1);
    
    settingsTimerUnlocked = false;
    
    startTimer(bypassTimer, processor.bypassTime);
}


PajAuanalyserAudioProcessorEditor::~PajAuanalyserAudioProcessorEditor()
{
    if(drawingThread.isThreadRunning())
        drawingThread.stopThread (3000);
    
    if(connectToSocket("127.0.0.1", 52425, 1000))
    {
        sendFFTsizeToGenerator(muteImpulseID);
        
        processor.startTimer(100);
    }
}


void PajAuanalyserAudioProcessorEditor::showBubbleHint(bool shouldShowHint)
{
    if(shouldShowHint)
    {
        hintPos.setBounds((getWidth()/2)-170, (getHeight()/2)-5, 1, 1);
        pajHint.showAt(hintPos, pajHintText, 4500, true, false);
    }
    showHint = true;
    return;
}


//==============================================================================
//== D R A W I N G =============================================================
//==============================================================================
void PajAuanalyserAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(Colours::indigo);

    g.setColour (Colours::lightblue);

//    g.drawRoundedRectangle(logoSpace, 10.f, 1.0f);
    g.drawImage(pajLogo, logoSpace);
    g.drawRoundedRectangle(buttonsSpace, 10.f, 1.0f);
}

void PajAuanalyserAudioProcessorEditor::resized()
{
    if(processor.settingsToApprove)
    {
        processor.settingsToApprove = false;
    }
    
    pajUnwrap.setBounds(getWidth()-51, 60, 19, 17);
    pajUnwrapLabel.setBounds(getWidth()-90, 61.5, 45, 12);
 
    drawingThread.wSetBounds(getWidth(), getHeight(), showPhaseBool);
    
    processor.setSize(getWidth(), getHeight());
    
    drawingThread.notify();
}



//==============================================================================
//== R E M O T E ===============================================================
//==============================================================================
void PajAuanalyserAudioProcessorEditor::updateToggleState(Button* button, uint8 buttonID)
{
    
    switch (buttonID)
    {
        default: break;
        case pajOffButtonID:   clickOFF();           return;
        case pajPhaseButtonID: clickShowPhase();     return;
        case latencyID:        clickDetectLatency(); return;
        case unWrapID:         clickUnWrap();        return;
    }
    
    if( button->getRadioGroupId() == bufferButtonRadioGroup )
        fftSizeClicked(buttonID);

}


void PajAuanalyserAudioProcessorEditor::fftSizeClicked(uint8 buttonID)
{
    if(waitForSettings)
    {
        buffBut[buttonID].setToggleState(wButtonOFF, dontSendNotification);
        updateButtons(clickedFFTsizeID, wButtonON, wDontClick);
    }
    else
    {
        if( !buffBut[buttonID].getToggleState() ) { return; }
        else
        {
            if( connectToSocket("127.0.0.1", 52425, 1) && processor.bypassTreshold>=0 && !blockButtons && setPajFFTsize(buttonID))
            {
                waitForSettings=true;
                clickedFFTsizeID = buttonID;
                fftSizeID = buttonID;
                processor.isBypassed = false;
                
                if(!processor.wIsPaused)
                    settingsTimerUnlocked = true;
                
                processor.wIsPaused = true;
                drawingThread.isHold = true;
                
                startTimer(settingsTimer, processor.bypassTime);
            }
            else
            {
                updateButtons(clickedFFTsizeID, wButtonON, wDontClick);
                showBubbleHint(showHint);
            }
        }
    }
}


void PajAuanalyserAudioProcessorEditor::clickOFF()
{
    if(waitForSettings) return;
    else
    {
        waitForSettings = true;
        drawingThread.isHold=true;
        
        sendFFTsizeToGenerator(muteImpulseID);
        
        clickedFFTsizeID = muteImpulseID;
        
        updateButtons(muteImpulseID, wButtonOFF, wDontClick);
        processor.startTimer(2*processor.bypassTime);
    }
}


void PajAuanalyserAudioProcessorEditor::clickShowPhase()
{
    if(waitForSettings) return;
    else
    {
        waitForSettings=true;
        showPhaseBool = (++showPhaseBool)%2;
        
        drawingThread.wSetBounds(getWidth(), getHeight(), showPhaseBool);
        
        pajUnwrap.setVisible(showPhaseBool);
        pajUnwrapLabel.setVisible(showPhaseBool);
        latencyDetect.setVisible(showPhaseBool);
        latencyDetectLabel.setVisible(showPhaseBool);
        
        if(!showPhaseBool)
        {
            drawingThread.display_magni.setVisible(true);
            drawingThread.display_phase.setVisible(false);
            drawingThread.drawPhase = false;
        }
        else
        {
            drawingThread.display_magni.setVisible(false);
            drawingThread.display_phase.setVisible(true);
            drawingThread.drawPhase = true;
        }
        
        for(int channel=0; channel<processor.wNumInputChannel; ++channel)
        {
            if(!showPhaseBool)
            {
                drawingThread.magAnal[channel].setVisible(true);
                drawingThread.phaAnal[channel].setVisible(false);
                
                if(processor.isBypassed)
                    drawingThread.magAnal[channel].resized();
            }
            else
            {
                drawingThread.magAnal[channel].setVisible(false);
                drawingThread.phaAnal[channel].setVisible(true);
                
                if(processor.isBypassed)
                    drawingThread.phaAnal[channel].resized();
            }
            
        }
        
        waitForSettings = false;
        
        if(drawingThread.isWaiting)
            drawingThread.notify();
    }
}


void PajAuanalyserAudioProcessorEditor::clickDetectLatency()
{
//    if( latencyDetect.getToggleState() )
    processor.waitForLatDetect = 5*(int)processor.pajFFTsize;
        processor.wDetectLatency = true;
//    else
//        processor.wDetectLatency = false;
}


void PajAuanalyserAudioProcessorEditor::clickUnWrap()
{
    if(pajUnwrap.getToggleState())
    {
        isUnWrapToggled = true;
        drawingThread.phaAnal[wLeft].pajUnwrapping = true;
        drawingThread.phaAnal[wRight].pajUnwrapping = true;
    }
    else
    {
        isUnWrapToggled = false;
        drawingThread.phaAnal[wLeft].pajUnwrapping = false;
        drawingThread.phaAnal[wRight].pajUnwrapping = false;
    }
}


void PajAuanalyserAudioProcessorEditor::updateButtons(uint8 buttonID, bool toggleState, bool clickOrNot)
{
    if(buttonID>=0 && buttonID<numOfRadioButton)
    {
        buffBut[buttonID].setToggleState(toggleState, dontSendNotification);
        if(clickOrNot)
            updateToggleState(&buffBut[buttonID], buttonID);
    }
    else if(buttonID == muteImpulseID)
    {
        for(int i=0; i<numOfRadioButton; ++i)
        {
            buffBut[i].setToggleState(wButtonOFF, dontSendNotification);
        }
    }
}


ToggleButton* PajAuanalyserAudioProcessorEditor::getPajButton(uint8 buttonID)
{
    switch (fftSizeID) {
        case b1024ID:
            return &buffBut[0];
            
        case b2048ID:
            return &buffBut[1];
            
        case b4096ID:
            return &buffBut[2];
            
        case b8192ID:
            return &buffBut[3];
            
        case b16384ID:
            return &buffBut[4];
            
        case b32768ID:
            return &buffBut[5];
            
        case b65536ID:
            return &buffBut[6];
            
        default:
            return &buffBut[0];;
    }
}




//==============================================================================
//== T I M E R S ===============================================================
//==============================================================================
void PajAuanalyserAudioProcessorEditor::timerCallback(int timerID)
{
    switch(timerID)
    {
        case bypassTimer:       bypassTimerCallback();            return;
        case settingsTimer:     settingsTimerCallback();          return;
        case waitForPrepToPlay: waitForPrepToPlayTimerCallback(); return;
        case refreshMessageReceivedBool:
            stopTimer(refreshMessageReceivedBool);
            pajMessageReceived = false;
            return;
        default: return;
    }
}


void PajAuanalyserAudioProcessorEditor::settingsTimerCallback()
{
    if(settingsTimerUnlocked || !dataIsInUse.test_and_set())
    {
        settingsTimerUnlocked = true;
        
        if(notifyFromDThread)
        {
            stopTimer(settingsTimer);
            if(processor.updateFFTSize())
            {
                settingsTimerUnlocked = false;
                processor.wIsPaused = false;
                dataIsInUse.clear();

                sendFFTsizeToGenerator(fftSizeID);
                
                if(!drawingThread.isThreadRunning())
                    drawingThread.startThread(1);
                
                drawingThread.isSystemReady = true;
                drawingThread.isHold = false;
                processor.waitForLatDetect = 5*(int)processor.pajFFTsize;
                processor.wDetectLatency = true;
            }
            
            waitForSettings=false;
        }
    }
}



void PajAuanalyserAudioProcessorEditor::bypassTimerCallback()
{
    if(processor.bypassTreshold<0)
    {
        if(sendBypassMessage)
        {
            if(!pajMessageReceived)
            {
                sendBypassMessage = false;
                playBack = false;
                sendFFTsizeToGenerator(muteImpulseID);
                processor.startTimer(1);
            }
            pajMessageReceived=false;
        }
    }
    else
    {
        processor.bypassTreshold--;
        
        if(!playBack)
        {
            if(!pajMessageReceived)
            {
                playBack = true;
                sendBypassMessage = true;
                showHint = false;
                updateButtons(clickedFFTsizeID, wButtonON, wClick);
                
                if(blockButtons)
                    sendFFTsizeToGenerator(clickedFFTsizeID);
            }
            pajMessageReceived=false;
        }
    }
}


void PajAuanalyserAudioProcessorEditor::waitForPrepToPlayTimerCallback()
{
    if(processor.wasProcessorInit)
    {
        stopTimer(waitForPrepToPlay);
        drawProcComponents();
    }
}




//==============================================================================
//== M O U S E =================================================================
//==============================================================================
void PajAuanalyserAudioProcessorEditor::mouseDown( const MouseEvent & event )
{
    if( event.originalComponent == resizableCorner.get() )
    {
        processor.drawingThread.isResizing = true;
    }
}

void PajAuanalyserAudioProcessorEditor::mouseUp( const MouseEvent & event )
{
    if( event.originalComponent == resizableCorner.get() )
    {
        processor.drawingThread.isResizing = false;
    }
}



//==============================================================================
//== S E T T I N G S  ==========================================================
//==============================================================================
bool PajAuanalyserAudioProcessorEditor::setPajFFTsize(int fftSizeID)
{
    switch (fftSizeID) {
        case b1024ID:
            processor.pajFFTsize = 1024.0f;
            return true;
            
        case b2048ID:
            processor.pajFFTsize = 2048.0f;
            return true;
            
        case b4096ID:
            processor.pajFFTsize = 4096.0f;
            return true;
            
        case b8192ID:
            processor.pajFFTsize = 8192.0f;
            return true;
            
        case b16384ID:
            processor.pajFFTsize = 16384.0f;
            return true;
            
        case b32768ID:
            processor.pajFFTsize = 32768.0f;
            return true;
            
        case b65536ID:
            processor.pajFFTsize = 65536.0f;
            return true;
            
        default:
            return false;
    }
}



//==============================================================================
//== S O C K E T == C O N N E C T I O N ========================================
//==============================================================================
void PajAuanalyserAudioProcessorEditor::sendFFTsizeToGenerator(uint8 fftSizeID)
{
    if(isConnected())
    {
        memoryMessage.fillWith(fftSizeID);
        sendMessage(memoryMessage);
    }
}

void PajAuanalyserAudioProcessorEditor::connectionMade()
{
    //    DBG("CONNECTED");
}

void PajAuanalyserAudioProcessorEditor::connectionLost()
{
    //    DBG("DISCONNECTED");
}

void PajAuanalyserAudioProcessorEditor::messageReceived( const MemoryBlock & message)
{
    pajMessageReceived=true;
    
    if(message[0] == muteImpulseID)
    {
        blockButtons = true;
        waitForSettings=true;
        drawingThread.isHold=true;
        drawingThread.resetAnalGraph();
        drawingThread.notify();
        processor.startTimer(2*processor.bypassTime);
    }
    else if(message[0] == pajPlay)
    {
        blockButtons = false;
        if(clickedFFTsizeID != muteImpulseID)
        {
            processor.isBypassed = false;
            processor.wIsPaused = false;
            
            if(!getPajButton(clickedFFTsizeID)->getToggleState())
            {
                updateButtons(clickedFFTsizeID, wButtonON, wClick);
            }
        }
    }
    
    startTimer(refreshMessageReceivedBool, 200);
    if(!isConnected())
        connectToSocket("127.0.0.1", 52425, 1000);
}



//==============================================================================
//== D R A W == C O M P O N E N T S ============================================
//==============================================================================
void PajAuanalyserAudioProcessorEditor::pajDrawAllComponents()
{
    setResolutLabel.setBounds( margX + labX,    23, 80, 15);
    setBuffSizLabel.setBounds( margX + labX,    10, 80, 15);
    
    pajOFFButton.setBounds        (margX + bufButX + 8*spaceX+2, 7.6f, 35, 35);
    pajResetButton.setBounds      (margX + bufButX + 8*spaceX-37, 7.6f, 38, 17);
    pajPhaseButton.setBounds(margX + bufButX + 8*spaceX-37, 25.6f, 38, 17);
    
    
    for(int i=0; i < 7; ++i)
    {
        addAndMakeVisible(&buffBut[i]);
        buffBut[i].setRadioGroupId(bufferButtonRadioGroup);
        buffBut[i].setAlwaysOnTop(true);
        buffBut[i].setBounds       ( margX + bufButX + i*spaceX, 23, 19, 17);
        
        addAndMakeVisible(&buffButL[i]);
        buffButL[i].setJustificationType(Justification::centredBottom);
        buffButL[i].setText(std::to_string( (int)pow(2, (i+10)) ), dontSendNotification);
        buffButL[i].setFont(wFontSize);
        buffButL[i].setAlwaysOnTop(true);
        buffButL[i].setBounds( margX + bufLabX + i*spaceX -2, 11, 50, 12);
        
        switch(i)
        {
            case b1024ID: buffBut[i].onClick = [this] { updateToggleState(&buffBut[b1024ID], b1024ID); }; break;
            case b2048ID: buffBut[i].onClick = [this] { updateToggleState(&buffBut[b2048ID], b2048ID); }; break;
            case b4096ID: buffBut[i].onClick = [this] { updateToggleState(&buffBut[b4096ID], b4096ID); }; break;
            case b8192ID: buffBut[i].onClick = [this] { updateToggleState(&buffBut[b8192ID], b8192ID); }; break;
            case b16384ID: buffBut[i].onClick = [this] { updateToggleState(&buffBut[b16384ID], b16384ID); }; break;
            case b32768ID: buffBut[i].onClick = [this] { updateToggleState(&buffBut[b32768ID], b32768ID); }; break;
            case b65536ID: buffBut[i].onClick = [this] { updateToggleState(&buffBut[b65536ID], b65536ID); }; break;
            default: break;
        }
    }
    
    //===================
    logoSpace.setBounds(margX-45, 5, 40, 40);
    buttonsSpace.setBounds(margX, 5.0f, 445.0f-3, 40.0f);
    
    
    //===================
    addAndMakeVisible(&setResolutLabel);
    setResolutLabel.setJustificationType(Justification::centredBottom);
    setResolutLabel.setText("(resolution)", dontSendNotification);
    setResolutLabel.setFont(wFontSize);
    setResolutLabel.setAlwaysOnTop(true);
    
    addAndMakeVisible(&setBuffSizLabel);
    setBuffSizLabel.setJustificationType(Justification::centredBottom);
    setBuffSizLabel.setText("START HERE:", dontSendNotification);
    setBuffSizLabel.setFont(wFontSize2);
    setBuffSizLabel.setAlwaysOnTop(true);
    
    
    //===================
    addAndMakeVisible(&pajOFFButton);
    pajOFFButton.setButtonText("Off");
    pajOFFButton.onClick = [this] { updateToggleState(&pajOFFButton, pajOffButtonID); };
    pajOFFButton.setAlwaysOnTop(true);
    
    addAndMakeVisible(&pajResetButton);
    pajResetButton.setButtonText("RESET");
    pajResetButton.onClick = [this] { updateToggleState(&pajResetButton, pajResetButtonID); };
    pajResetButton.setAlwaysOnTop(true);
    
    addAndMakeVisible(&pajPhaseButton);
    pajPhaseButton.setButtonText("PHASE");
    pajPhaseButton.onClick = [this] { updateToggleState(&pajPhaseButton, pajPhaseButtonID); };
    pajPhaseButton.setAlwaysOnTop(true);
    
    
    
    //===================
    addAndMakeVisible(&latencyDetect);
    latencyDetect.onClick = [this] { updateToggleState(&latencyDetect, latencyID); };
    latencyDetect.setAlwaysOnTop(true);
    latencyDetect.setButtonText("LATENCY");
    
    addAndMakeVisible(&pajUnwrap);
    pajUnwrap.setAlwaysOnTop(true);
    pajUnwrap.onClick = [this] { updateToggleState(&pajUnwrap, unWrapID); };
    addAndMakeVisible(&pajUnwrapLabel);
    pajUnwrapLabel.setJustificationType(Justification::right);
    pajUnwrapLabel.setText("unwrap", dontSendNotification);
    pajUnwrapLabel.setFont(wFontSize);
    pajUnwrapLabel.setAlwaysOnTop(true);
    
    
    latencyDetect.setVisible(showPhaseBool);
    latencyDetect.setBounds      ( 51, 60, 55, 17);
    latencyDetect.setColour(TextButton::textColourOnId, Colours::yellow);
    latencyDetect.setColour(TextButton::textColourOffId, Colours::yellow);
    
    pajUnwrap.setVisible(showPhaseBool);
    pajUnwrapLabel.setVisible(showPhaseBool);

    
    startTimer(waitForPrepToPlay, 100);
}


void PajAuanalyserAudioProcessorEditor::drawProcComponents()
{
    //== P R O C E S S O R == D E F A U L T ==
    addAndMakeVisible(&drawingThread.display_magni);
    addAndMakeVisible(&drawingThread.display_phase);
    drawingThread.display_phase.setVisible(showPhaseBool);
    drawingThread.drawPhase = showPhaseBool;
    
    for(int channel=0; channel<processor.wNumInputChannel; ++channel)
    {
        addAndMakeVisible(&drawingThread.magAnal[channel]);
        addAndMakeVisible(&drawingThread.phaAnal[channel]);
        drawingThread.phaAnal[channel].setVisible(showPhaseBool);
    }
    
    if(!drawingThread.isThreadRunning())
        drawingThread.startThread(1);
    
    pajUnwrap.setToggleState(isUnWrapToggled, dontSendNotification);
    resized();
}
