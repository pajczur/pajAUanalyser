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
                                clickedButtonID(p.clickedButtonID),
                                showPhaseBool(p.showPhaseBool),
                                sendRemote(p),
                                receiveRemote(p),
                                processor (p),
                                sampRate(p.wSampleRate),
                                pajFFTsize(p.pajFFTsize),
                                wNumChannel(p.wNumInputChannel),
                                drawingThread(p.dThread),
                                notifyFromDThread(p.dThread.notifyEditor),
                                holdDThread(p.dThread.isHold),
                                pauseProc(p.wIsPaused),
                                isBypassed(p.isBypassed),
                                dataIsInUse(p.dataIsInUse),
                                bypassTime(p.bypassTime),
                                bypassTreshold(p.bypassTreshold)
{
    setResizable(true, true);
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
    
    startTimer(bypassTimer, bypassTime);
    
    setSize (565, 300);
    
    if(!drawingThread.isThreadRunning())
        drawingThread.startThread(1);
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
    
    if(processor.settingsToApprove)
    {
        processor.settingsToApprove = false;
    }
 
    drawingThread.wSetBounds(getWidth(), getHeight(), showPhaseBool);
    
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
    }
    
    if( button->getRadioGroupId() == bufferButtonRadioGroup )
        fftSizeClicked(buttonID);

}

void PajAuanalyserAudioProcessorEditor::clickOFF()
{
    if(waitForSettings) return;
    else
    {
        waitForSettings=true;
        holdDThread=true;
        sendFFTsizeToGenerator(muteImpulseID);
        clickedButtonID = muteImpulseID;
        updateButtons(muteImpulseID, false, false);
        processor.startTimer(2*bypassTime);
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
        
        drawingThread.display_phase.setVisible(showPhaseBool);
        drawingThread.drawPhase = showPhaseBool;
        
        for(int channel=0; channel<wNumChannel; ++channel)
        {
            drawingThread.phaAnal[channel].setVisible(showPhaseBool);
        }
        
        if(isBypassed)
        {
            drawingThread.notify();
            
            for(int channel=0; channel<wNumChannel; ++channel)
            {
                drawingThread.magAnal[channel].resized();
                drawingThread.phaAnal[channel].resized();
            }
            
        }
        
        waitForSettings = false;
    }
}

void PajAuanalyserAudioProcessorEditor::fftSizeClicked(uint8 buttonID)
{
    if(waitForSettings)
    {
        buffBut[buttonID].setToggleState(false, dontSendNotification);
        updateButtons(clickedButtonID, true, false);
    }
    else
    {
        if( !buffBut[buttonID].getToggleState() ) { return; }
        else
        {
            if( connectToSocket("127.0.0.1", 52425, 1) && bypassTreshold>=0)
            {
                waitForSettings=true;
                clickedButtonID = buttonID;
                fftSizeID = buttonID;
                isBypassed = false;
                if(!pauseProc)
                    settingsTimerUnlocked = true;
                
                pauseProc = true;
                holdDThread = true;
                setPajFFTsize(buttonID);
                startTimer(settingsTimer, bypassTime);
            }
            else
            {
                updateButtons(clickedButtonID, true, wDontClickButton);
                showBubbleHint(showHint);
            }
        }
    }
}

void PajAuanalyserAudioProcessorEditor::clickDetectLatency()
{
    if( latencyDetect.getToggleState() )
        processor.wDetectLatency = true;
    else
        processor.wDetectLatency = false;
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
            buffBut[i].setToggleState(false, dontSendNotification);
        }
    }
}






//==============================================================================
//== T I M E R S ===============================================================
//==============================================================================
void PajAuanalyserAudioProcessorEditor::timerCallback(int timerID)
{
    switch(timerID)
    {
        case bypassTimer:   bypassTimerCallback();   return;
        case settingsTimer: settingsTimerCallback(); return;
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
            processor.updateFFTSize();
            settingsTimerUnlocked = false;
            pauseProc = false;
            dataIsInUse.clear();
            holdDThread = false;
            sendFFTsizeToGenerator(fftSizeID);
            
            if(!drawingThread.isThreadRunning())
                drawingThread.startThread(1);
            
            waitForSettings=false;
        }
    }
}



void PajAuanalyserAudioProcessorEditor::bypassTimerCallback()
{
    if(bypassTreshold<0)
    {
        if(sendBypassMessage)
        {
            sendBypassMessage = false;
            playBack = false;
            sendFFTsizeToGenerator(muteImpulseID);
            processor.startTimer(1);
        }
    }
    else
    {
        bypassTreshold--;
        
        if(!playBack)
        {
            playBack = true;
            sendBypassMessage = true;
            showHint = false;
            updateButtons(clickedButtonID, true, wClickButton);
        }
    }
}



//==============================================================================
//== M O U S E =================================================================
//==============================================================================
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



//==============================================================================
//== S E T T I N G S  ==========================================================
//==============================================================================
void PajAuanalyserAudioProcessorEditor::setPajFFTsize(int fftSizeID)
{
    switch (fftSizeID) {
        case b1024ID:
            pajFFTsize = 1024.0f;
            return;
            
        case b2048ID:
            pajFFTsize = 2048.0f;
            return;
            
        case b4096ID:
            pajFFTsize = 4096.0f;
            return;
            
        case b8192ID:
            pajFFTsize = 8192.0f;
            return;
            
        case b16384ID:
            pajFFTsize = 16384.0f;
            return;
            
        case b32768ID:
            pajFFTsize = 32768.0f;
            return;
            
        case b65536ID:
            pajFFTsize = 65536.0f;
            return;
            
        default:
            return;
    }
}



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
    
    latencyDetectLabel.setColour(Label::textColourId, Colours::yellow);
    latencyDetect.setColour(ToggleButton::tickColourId, Colours::yellow);
    
    //===================
    logoSpace.setBounds(margX-45, 5, 40, 40);
    buttonsSpace.setBounds(margX, 5.0f, 445.0f-3, 40.0f);
    
    
    //===================
    addAndMakeVisible(&setResolutLabel);
    setResolutLabel.setJustificationType(Justification::centredBottom);
    setResolutLabel.setText("(resolution):", dontSendNotification);
    setResolutLabel.setFont(wFontSize);
    setResolutLabel.setAlwaysOnTop(true);
    
    addAndMakeVisible(&setBuffSizLabel);
    setBuffSizLabel.setJustificationType(Justification::centredBottom);
    setBuffSizLabel.setText("BUFFER SIZE:", dontSendNotification);
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
    addAndMakeVisible(&latencyDetectLabel);
    latencyDetectLabel.setJustificationType(Justification::centredBottom);
    latencyDetectLabel.setText("LAT.", dontSendNotification);
    latencyDetectLabel.setFont(wFontSize);
    latencyDetectLabel.setAlwaysOnTop(true);
    
    addAndMakeVisible(&pajUnwrap);
    pajUnwrap.setAlwaysOnTop(true);
    pajUnwrap.onClick = [this] { updateToggleState(&pajUnwrap, unWrapID); };
    addAndMakeVisible(&pajUnwrapLabel);
    pajUnwrapLabel.setJustificationType(Justification::right);
    pajUnwrapLabel.setText("unwrap", dontSendNotification);
    pajUnwrapLabel.setFont(wFontSize);
    pajUnwrapLabel.setAlwaysOnTop(true);
    
    pajUnwrap.setVisible(showPhaseBool);
    pajUnwrapLabel.setVisible(showPhaseBool);
    latencyDetect.setVisible(showPhaseBool);
    latencyDetectLabel.setVisible(showPhaseBool);
    
    
    
    //== P R O C E S S O R == D E F A U L T ==
    addAndMakeVisible(&drawingThread.display_magni);
    addAndMakeVisible(&drawingThread.display_phase);
    drawingThread.display_phase.setVisible(showPhaseBool);
    drawingThread.drawPhase = showPhaseBool;
    
    for(int channel=0; channel<wNumChannel; ++channel)
    {
        addAndMakeVisible(&drawingThread.magAnal[channel]);
        addAndMakeVisible(&drawingThread.phaAnal[channel]);
        drawingThread.phaAnal[channel].setVisible(showPhaseBool);
    }
}





//==============================================================================
//== S O C K E T == C O N N E C T I O N ========================================
//==============================================================================
void PajAuanalyserAudioProcessorEditor::sendFFTsizeToGenerator(uint8 fftSizeID)
{
    memoryMessage.fillWith(fftSizeID);
    sendMessage(memoryMessage);
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
    if(message[0] == muteImpulseID)
    {
        updateButtons(muteImpulseID, false, false);
    }
    else if (message[0] == pajOffButtonID)
    {
    }
    else
    {
    }
    
    if(!isConnected())
        connectToSocket("127.0.0.1", 52425, 1000);
}


/*
void PajAuanalyserAudioProcessorEditor::pajDrawAllComponents()
{
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
    
    //===================
    logoSpace.setBounds(margX-45, 5, 40, 40);
    buttonsSpace.setBounds(margX, 5.0f, 445.0f-3, 40.0f);
    
    
    //===================
    addAndMakeVisible(&setResolutLabel);
    setResolutLabel.setJustificationType(Justification::centredBottom);
    setResolutLabel.setText("(resolution):", dontSendNotification);
    setResolutLabel.setFont(wFontSize);
    setResolutLabel.setAlwaysOnTop(true);
    
    addAndMakeVisible(&setBuffSizLabel);
    setBuffSizLabel.setJustificationType(Justification::centredBottom);
    setBuffSizLabel.setText("BUFFER SIZE:", dontSendNotification);
    setBuffSizLabel.setFont(wFontSize2);
    setBuffSizLabel.setAlwaysOnTop(true);
    
    
     //===================
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
    addAndMakeVisible(&latencyDetectLabel);
    latencyDetectLabel.setJustificationType(Justification::centredBottom);
    latencyDetectLabel.setText("LAT.", dontSendNotification);
    latencyDetectLabel.setFont(wFontSize);
    latencyDetectLabel.setAlwaysOnTop(true);
    
    addAndMakeVisible(&pajUnwrap);
    pajUnwrap.setAlwaysOnTop(true);
    pajUnwrap.onClick = [this] { updateToggleState(&pajUnwrap, unWrapID); };
    addAndMakeVisible(&pajUnwrapLabel);
    pajUnwrapLabel.setJustificationType(Justification::right);
    pajUnwrapLabel.setText("unwrap", dontSendNotification);
    pajUnwrapLabel.setFont(wFontSize);
    pajUnwrapLabel.setAlwaysOnTop(true);
    
    pajUnwrap.setVisible(false);
    pajUnwrapLabel.setVisible(false);
    latencyDetect.setVisible(false);
    latencyDetectLabel.setVisible(false);
    
    
    
    //== P R O C E S S O R == D E F A U L T ==
    addAndMakeVisible(&drawingThread.display_magni);
    addAndMakeVisible(&drawingThread.display_phase);
    drawingThread.display_phase.setVisible(false);
    drawingThread.drawPhase = false;
    
    for(int channel=0; channel<wNumChannel; ++channel)
    {
        addAndMakeVisible(&drawingThread.magAnal[channel]);
        addAndMakeVisible(&drawingThread.phaAnal[channel]);
        drawingThread.phaAnal[channel].setVisible(false);
    }
}
*/


/*
void PajAuanalyserAudioProcessorEditor::updateButtons(uint8 buttonID, bool toggleState, bool clickOrNot)
{
    switch (buttonID)
    {
        case muteImpulseID:
            buff_1024.setToggleState(false, dontSendNotification);
            buff_2048.setToggleState(false, dontSendNotification);
            buff_4096.setToggleState(false, dontSendNotification);
            buff_8192.setToggleState(false, dontSendNotification);
            buff_16384.setToggleState(false, dontSendNotification);
            buff_32768.setToggleState(false, dontSendNotification);
            buff_65536.setToggleState(false, dontSendNotification);
            return;

        case b1024ID:
            buff_1024.setToggleState(toggleState, dontSendNotification);
            if(clickOrNot)
                updateToggleState(&buff_1024, b1024ID);
            return;

        case b2048ID:
            buff_2048.setToggleState(toggleState, dontSendNotification);
            if(clickOrNot)
                updateToggleState(&buff_2048, b2048ID);
            return;

        case b4096ID:
            buff_4096.setToggleState(toggleState, dontSendNotification);
            if(clickOrNot)
                updateToggleState(&buff_4096, b4096ID);
            return;

        case b8192ID:
            buff_8192.setToggleState(toggleState, dontSendNotification);
            if(clickOrNot)
                updateToggleState(&buff_8192, b8192ID);
            return;

        case b16384ID:
            buff_16384.setToggleState(toggleState, dontSendNotification);
            if(clickOrNot)
                updateToggleState(&buff_16384, b16384ID);
            return;

        case b32768ID:
            buff_32768.setToggleState(toggleState, dontSendNotification);
            if(clickOrNot)
                updateToggleState(&buff_32768, b32768ID);
            return;

        case b65536ID:
            buff_65536.setToggleState(toggleState, dontSendNotification);
            if(clickOrNot)
                updateToggleState(&buff_65536, b65536ID);
            return;

        default:
            return;
    }
}
*/
