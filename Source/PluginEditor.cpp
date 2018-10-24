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
    offWasClicked = false;
    waitForGenerator = true;
    buttonWasClicked = false;
    pajMessageReceived=false;
    setResizable(true, true);
    setSize (wWidth, wHeight);
    setResizeLimits(520, 300, 10000, 10000);
    resizableCorner->addMouseListener(this, true);
    
    
    // == H I N T == B U B B L E ==

    
    if(connectToSocket("127.0.0.1", 52425, 1000))
         waitForGenerator = false;
    
    pajDrawAllComponents();
    
    memoryMessage.setSize(1);
    
    settingsTimerUnlocked = false;
    
    hintWall.setText("1) \"pajAUanalyser - gen\" must be lounched and ON\n\n2) Be sure there is any audio source on measured track\n\n3) HIT PLAY", dontSendNotification);
    hintWall.setJustificationType(Justification::centred);
    hintWall.setColour(Label::ColourIds::backgroundColourId, Colours::black);
    hintWall.setAlwaysOnTop(true);
    hintWall.setAlpha(0.8);
    addAndMakeVisible(hintWall);
    hintWall.setVisible(false);
    
    startTimer(HINT_TIMER_ID, 1000);
}


PajAuanalyserAudioProcessorEditor::~PajAuanalyserAudioProcessorEditor()
{
    if(drawingThread.isThreadRunning())
        drawingThread.stopThread (3000);
    
    if(connectToSocket("127.0.0.1", 52425, 1000))
    {
        sendFFTsizeToGenerator(MUTE_IMPULSE_ID);
        
        processor.startTimer(100);
    }
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
    
//    g.drawImage(icon1024, buffIconSpace[B_1024ID]);
//    g.drawImage(icon2048, buffIconSpace[B_2048ID]);
//    g.drawImage(icon4096, buffIconSpace[B_4096ID]);
//    g.drawImage(icon8192, buffIconSpace[B_8192ID]);
//    g.drawImage(icon16384, buffIconSpace[B_16384ID]);
//    g.drawImage(icon32768, buffIconSpace[B_32768ID]);
//    g.drawImage(icon65536, buffIconSpace[B_65536ID]);
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
        case PAJ_OFF_BUTTON_ID:   clickOFF();           return;
        case PAJ_PHASE_BUTTON_ID: clickShowPhase();     return;
        case PAJ_RESET_BUTTON_ID: clickReset();         return;
        case LATENCY_ID:          clickDetectLatency(); return;
        case UNWRAP_PHASE_ID:     clickUnWrap();        return;
    }
    
    if( button->getRadioGroupId() == BUFF_BUTTON_RADIO_GROUP )
        fftSizeClicked(buttonID);

}


void PajAuanalyserAudioProcessorEditor::fftSizeClicked(uint8 buttonID)
{
    if(waitForSettings)
    {
        buffBut[buttonID].setToggleState(W_BUTTON_OFF, dontSendNotification);
        updateButtons(clickedFFTsizeID, W_BUTTON_ON, W_DONT_CLICK);
    }
    else
    {
        if( !buffBut[buttonID].getToggleState() ) { return; }
        else
        {
            if( isConnected() && setPajFFTsize(buttonID))
            {
                buttonWasClicked = true;
                offWasClicked = false;
                waitForSettings=true;
                clickedFFTsizeID = buttonID;
                fftSizeID = buttonID;
                processor.isBypassed = false;
                
                if(!processor.wIsPaused)
                    settingsTimerUnlocked = true;
                
                processor.wIsPaused = true;
                drawingThread.isHold = true;
                
                startTimer(SETTINGS_TIMER_ID, processor.bypassTime);
            }
            else
            {
                updateButtons(clickedFFTsizeID, W_BUTTON_ON, W_DONT_CLICK);
//                showBubbleHint(showHint);
            }
        }
    }
}


void PajAuanalyserAudioProcessorEditor::clickOFF()
{
    if(waitForSettings) return;
    else
    {
        offWasClicked = true;
        
        waitForSettings = true;
        drawingThread.isHold=true;

        sendFFTsizeToGenerator(MUTE_IMPULSE_ID);

        clickedFFTsizeID = MUTE_IMPULSE_ID;

        updateButtons(MUTE_IMPULSE_ID, W_BUTTON_OFF, W_DONT_CLICK);
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
        showMagniBool = (showPhaseBool+1)%2;
        
        drawingThread.wSetBounds(getWidth(), getHeight(), showPhaseBool);
        
        pajUnwrap.setVisible(showPhaseBool);
        pajUnwrapLabel.setVisible(showPhaseBool);
        latencyDetect.setVisible(showPhaseBool);
        latencyDetectLabel.setVisible(showPhaseBool);

        drawingThread.display_magni.setVisible(showMagniBool);
        drawingThread.display_phase.setVisible(showPhaseBool);


        for(int channel=0; channel<processor.wNumInputChannel; ++channel)
        {
            drawingThread.magAnal[channel].setVisible(showMagniBool);
            drawingThread.phaAnal[channel].setVisible(showPhaseBool);
        }
        
        pajPhaseButton.setButtonText(!showPhaseBool?"PHASE":"MAGN.");
        
        waitForSettings = false;
        
//        if(drawingThread.isWaiting)
//            drawingThread.notify();
    }
}

void PajAuanalyserAudioProcessorEditor::clickReset()
{
    if(clickedFFTsizeID == MUTE_IMPULSE_ID || !playBack)
    {
        drawingThread.resetAnalGraph();
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
        for(int channel=0; channel<processor.wNumInputChannel; ++channel)
        {
        drawingThread.phaAnal[channel].pajUnwrapping = true;
            
            if(clickedFFTsizeID == MUTE_IMPULSE_ID || !playBack)
                drawingThread.phaAnal[channel].staticWrapToggle();
        }
    }
    else
    {
        isUnWrapToggled = false;
        for(int channel=0; channel<processor.wNumInputChannel; ++channel)
        {
            drawingThread.phaAnal[channel].pajUnwrapping = false;
            
            if(clickedFFTsizeID == MUTE_IMPULSE_ID || !playBack)
                drawingThread.phaAnal[channel].staticWrapToggle();
        }
    }
}


void PajAuanalyserAudioProcessorEditor::updateButtons(uint8 buttonID, bool toggleState, bool clickOrNot)
{
    if(buttonID>=0 && buttonID<NUM_OF_RADIO_BUTTONS)
    {
        buffBut[buttonID].setToggleState(toggleState, dontSendNotification);
        if(clickOrNot)
            updateToggleState(&buffBut[buttonID], buttonID);
    }
    else if(buttonID == MUTE_IMPULSE_ID)
    {
        for(int i=0; i<NUM_OF_RADIO_BUTTONS; ++i)
        {
            buffBut[i].setToggleState(W_BUTTON_OFF, dontSendNotification);
        }
    }
}


ToggleButton* PajAuanalyserAudioProcessorEditor::getPajButton(uint8 buttonID)
{
    switch (fftSizeID) {
        case B_1024ID:
            return &buffBut[0];
            
        case B_2048ID:
            return &buffBut[1];
            
        case B_4096ID:
            return &buffBut[2];
            
        case B_8192ID:
            return &buffBut[3];
            
        case B_16384ID:
            return &buffBut[4];
            
        case B_32768ID:
            return &buffBut[5];
            
        case B_65536ID:
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
        case BYPASS_TIMER_ID:          bypassTimerCallback();            return;
        case SETTINGS_TIMER_ID:        settingsTimerCallback();          return;
        case WAIT_FOR_PREP_TO_PLAY_ID: waitForPrepToPlayTimerCallback(); return;
        case HINT_TIMER_ID:            hintTimerCallback();              return;
        case MSG_RECEIVED_TIMER_ID:    msgReceivedTimerCallback();       return;
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
            stopTimer(SETTINGS_TIMER_ID);
            if(processor.updateFFTSize())
            {
                settingsTimerUnlocked = false;
                dataIsInUse.clear();

                if(playBack)
                    sendFFTsizeToGenerator(fftSizeID);
                
                if(!drawingThread.isThreadRunning())
                    drawingThread.startThread(1);
                
                drawingThread.isSystemReady = true;
                drawingThread.isHold = false;
                processor.waitForLatDetect = 5*(int)processor.pajFFTsize;
                processor.wDetectLatency = true;
                
                processor.wIsPaused = false;
                waitForSettings=false;
            }
            
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
                sendFFTsizeToGenerator(MUTE_IMPULSE_ID);
//                processor.startTimer(1);
            }
            pajMessageReceived=false;
            fftSizeID=MUTE_IMPULSE_ID;
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
                fftSizeID=clickedFFTsizeID;
                updateButtons(clickedFFTsizeID, W_BUTTON_ON, W_CLICK);
//                if(blockButtons)
//                    sendFFTsizeToGenerator(clickedFFTsizeID);
            }
            pajMessageReceived=false;
        }
    }
}


void PajAuanalyserAudioProcessorEditor::waitForPrepToPlayTimerCallback()
{
    if(processor.wasProcessorInit)
    {
        stopTimer(WAIT_FOR_PREP_TO_PLAY_ID);
        drawProcComponents();
    }
}

void PajAuanalyserAudioProcessorEditor::hintTimerCallback()
{
    if(!isConnected())
    {
        if(connectToSocket("127.0.0.1", 52425, 1000))
        {
            sendFFTsizeToGenerator(clickedFFTsizeID);
            waitForGenerator = false;
        }
    }
    
    
    if((!isConnected() && !offWasClicked) || (fftSizeID!=MUTE_IMPULSE_ID && (!playBack || waitForGenerator) && !offWasClicked) || (buttonWasClicked && waitForGenerator))
    {
        hintWall.setBounds(0, 0, getWidth(), getHeight());
        hintWall.setVisible(true);
        
        drawingThread.setVisibleGraph(0, 0);
    }
    else
    {
        if(hintWall.isVisible())
        {
            hintWall.setVisible(false);
            drawingThread.setVisibleGraph(showPhaseBool, showMagniBool);
        }
    }
    
    buttonWasClicked = false;
}


void PajAuanalyserAudioProcessorEditor::msgReceivedTimerCallback()
{
    stopTimer(MSG_RECEIVED_TIMER_ID);
    pajMessageReceived = false;
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
        case B_1024ID:
            processor.pajFFTsize = 1024.0f;
            return true;
            
        case B_2048ID:
            processor.pajFFTsize = 2048.0f;
            return true;
            
        case B_4096ID:
            processor.pajFFTsize = 4096.0f;
            return true;
            
        case B_8192ID:
            processor.pajFFTsize = 8192.0f;
            return true;
            
        case B_16384ID:
            processor.pajFFTsize = 16384.0f;
            return true;
            
        case B_32768ID:
            processor.pajFFTsize = 32768.0f;
            return true;
            
        case B_65536ID:
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
    
    if(message[0] == MUTE_IMPULSE_ID)
    {
//        blockButtons = true;
        waitForGenerator=true;
        drawingThread.isHold=true;
//        drawingThread.resetAnalGraph();
//        drawingThread.notify();
//        processor.startTimer(2*processor.bypassTime);
    }
    else if(message[0] == PAJ_PLAY)
    {
        waitForGenerator = false;

        if(clickedFFTsizeID != MUTE_IMPULSE_ID)
        {
            processor.isBypassed = false;
            processor.wIsPaused = false;
            
            if(!getPajButton(clickedFFTsizeID)->getToggleState())
            {
                updateButtons(clickedFFTsizeID, W_BUTTON_ON, W_CLICK);
            }
            else
                drawingThread.isHold=false;
        }
    }
    
    startTimer(MSG_RECEIVED_TIMER_ID, 200);
    if(!isConnected())
        connectToSocket("127.0.0.1", 52425, 1000);
}



//==============================================================================
//== D R A W == C O M P O N E N T S ============================================
//==============================================================================
void PajAuanalyserAudioProcessorEditor::pajDrawAllComponents()
{
    for(int i=0; i < 7; ++i)
    {
        addAndMakeVisible(&buffBut[i]);
        buffBut[i].setRadioGroupId(BUFF_BUTTON_RADIO_GROUP);
        buffBut[i].setAlwaysOnTop(true);
        buffBut[i].setBounds       ( MARG_X + BUF_BUT_X + i*SPACE_X, 24, 19, 17);
        
        buffIconSpace[i].setBounds(9+ MARG_X + BUF_LAB_X + i*SPACE_X, 9, 30, 15);
        
        switch(i)
        {
            case B_1024ID:  buffBut[i].onClick = [this] { updateToggleState(&buffBut[B_1024ID ], B_1024ID ); }; break;
            case B_2048ID:  buffBut[i].onClick = [this] { updateToggleState(&buffBut[B_2048ID ], B_2048ID ); }; break;
            case B_4096ID:  buffBut[i].onClick = [this] { updateToggleState(&buffBut[B_4096ID ], B_4096ID ); }; break;
            case B_8192ID:  buffBut[i].onClick = [this] { updateToggleState(&buffBut[B_8192ID ], B_8192ID ); }; break;
            case B_16384ID: buffBut[i].onClick = [this] { updateToggleState(&buffBut[B_16384ID], B_16384ID); }; break;
            case B_32768ID: buffBut[i].onClick = [this] { updateToggleState(&buffBut[B_32768ID], B_32768ID); }; break;
            case B_65536ID: buffBut[i].onClick = [this] { updateToggleState(&buffBut[B_65536ID], B_65536ID); }; break;
            default: break;
        }
    }
    
    //===================
    logoSpace.setBounds(MARG_X-45, 5, 40, 40);
    buttonsSpace.setBounds(MARG_X, 5.0f, 445.0f-3, 40.0f);
    
    
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
    
    setResolutLabel.setBounds( MARG_X + LAB_X, 23, 80, 15);
    setBuffSizLabel.setBounds( MARG_X + LAB_X, 10, 80, 15);
    
    
    //===================
    addAndMakeVisible(&pajOFFButton);
    pajOFFButton.setButtonText("Off");
    pajOFFButton.onClick = [this] { updateToggleState(&pajOFFButton, PAJ_OFF_BUTTON_ID); };
    pajOFFButton.setAlwaysOnTop(true);
    
    addAndMakeVisible(&pajResetButton);
    pajResetButton.setButtonText("RESET");
    pajResetButton.onClick = [this] { updateToggleState(&pajResetButton, PAJ_RESET_BUTTON_ID); };
    pajResetButton.setAlwaysOnTop(true);
    
    addAndMakeVisible(&pajPhaseButton);
    pajPhaseButton.setButtonText("PHASE");
    pajPhaseButton.onClick = [this] { updateToggleState(&pajPhaseButton, PAJ_PHASE_BUTTON_ID); };
    pajPhaseButton.setAlwaysOnTop(true);
    
    pajOFFButton.setBounds   (MARG_X + BUF_BUT_X + 8*SPACE_X+ 2,  7.6f, 35, 35);
    pajResetButton.setBounds (MARG_X + BUF_BUT_X + 8*SPACE_X-37,  7.6f, 38, 17);
    pajPhaseButton.setBounds (MARG_X + BUF_BUT_X + 8*SPACE_X-37, 25.6f, 38, 17);
    
    
    //===================
    addAndMakeVisible(&latencyDetect);
    latencyDetect.onClick = [this] { updateToggleState(&latencyDetect, LATENCY_ID); };
    latencyDetect.setAlwaysOnTop(true);
    latencyDetect.setButtonText("LATENCY");
    
    addAndMakeVisible(&pajUnwrap);
    pajUnwrap.setAlwaysOnTop(true);
    pajUnwrap.onClick = [this] { updateToggleState(&pajUnwrap, UNWRAP_PHASE_ID); };
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

    
    startTimer(WAIT_FOR_PREP_TO_PLAY_ID, 100);
}


void PajAuanalyserAudioProcessorEditor::drawProcComponents()
{
    //== P R O C E S S O R == D E F A U L T ==
    addAndMakeVisible(&drawingThread.display_magni);
    addAndMakeVisible(&drawingThread.display_phase);
    showMagniBool = (showPhaseBool+1)%2;
    drawingThread.display_magni.setVisible(showMagniBool);
    drawingThread.display_phase.setVisible(showPhaseBool);
    
    
    for(int channel=0; channel<processor.wNumInputChannel; ++channel)
    {
        addAndMakeVisible(&drawingThread.magAnal[channel]);
        addAndMakeVisible(&drawingThread.phaAnal[channel]);
        drawingThread.magAnal[channel].setVisible(showMagniBool);
        drawingThread.phaAnal[channel].setVisible(showPhaseBool);
    }
    
    drawingThread.magAnal[W_RIGHT].setAlwaysOnTop(false);
    drawingThread.phaAnal[W_RIGHT].setAlwaysOnTop(false);
    drawingThread.magAnal[W_LEFT].setAlwaysOnTop(true);
    drawingThread.phaAnal[W_LEFT].setAlwaysOnTop(true);
    
    drawingThread.magAnal[W_LEFT].setAlpha(1);
    drawingThread.phaAnal[W_LEFT].setAlpha(1);
    
    if(!drawingThread.isThreadRunning())
        drawingThread.startThread(1);
    
    pajUnwrap.setToggleState(isUnWrapToggled, dontSendNotification);
    
    drawingThread.rememberGraphBounds();
    drawingThread.resetAnalGraph();
    
    resized();
    
    
    
    startTimer(BYPASS_TIMER_ID, processor.bypassTime);
}
