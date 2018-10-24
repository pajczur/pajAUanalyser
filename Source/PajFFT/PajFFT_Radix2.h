/*
  ==============================================================================

     WojFFT.h
     Created: 13 Mar 2018 9:11:15pm
     Author:  Wojtek Pilwinski

  ==============================================================================
  ==============================================================================
  =========================== RADIX-2 FFT ALGORITHM ============================
  ==============================================================================
  ==============================================================================
*/

#pragma once
#include <iostream>
#include <cmath>
#include <complex>
#include <vector>
#include "../JuceLibraryCode/JuceHeader.h"
#include "../DefinitionMacros.h"


class PajFFT_Radix2
{
public:
    PajFFT_Radix2();
    ~PajFFT_Radix2();
  
    
    // == SETTINGS ==================================================================
private:
    void setSampleRate            (float sampleR);
    void setBufferSize            (float bufferS);
    bool resetData          ();
public:
    bool wSettings                (float sampleRate, float bufferSize);
    
    
    // == PRE CREATION ==============================================================
private:
    bool bitReversal              (float bufSize);
    bool prepareTwiddlesArray     ();
    bool prepare_sN0_matrix       ();
    
    
    
    // == F F T - RADIX 2 - ALGORITHM ===============================================
public:
    void makeFFT (std::vector<float>  &inputSignal, std::vector<std::vector<float>> &wOutputC, int channel);

private:
    void firstStepFFT                      (std::vector<             float>  &inputSignal,  int &rdx2);
    void divideAndConquereFFT              (int &rdx2, std::vector<std::complex<float>> &twiddle);
    void lastStepFFT                       (int &rdx2, std::vector<std::complex<float>> &twiddle);
    
    
    // == CALCULATORS ===============================================================
private:
    std::complex<float>    twiddleCalculator        (float nXk);
public:
    float                  freqMagnitudeCalc        (std::complex<float> &fftOutput, long freqBin);
    float                  phaseCalculator          (std::complex<float> &fftOutput, long index);

    
private:
    double fPi;
    
    float wSampleRate;
    float wBufferSize;
    int   dividerInt;
    float dividerFloat;
    
    std::vector<std::complex<float>> wnkN_forw;      // Array of precalculated forward twiddle
    std::vector<int>                 bitReversed;  // Array of bit reversed indexes for Zero padding
    
    std::vector<std::vector<std::vector<std::complex<float>>>> sN0;  // Temporarily input complex FFT - S(n)

public:
    std::vector<std::vector<float>> *wOutputData;
};
