/*
  ==============================================================================

     WojFFT.cpp
     Created: 13 Mar 2018 9:11:15pm
     Author:  Wojtek Pilwinski

  ==============================================================================
  ==============================================================================
  =========================== RADIX-2 FFT ALGORITHM ============================
  ==============================================================================
  ==============================================================================
*/

#include "PajFFT_Radix2.h"


// =========================================================================================================================================
// == C O N S T R U C T O R ==== D E S T R U C T O T =======================================================================================
// =========================================================================================================================================
// ==== PUBLIC: ====
PajFFT_Radix2::PajFFT_Radix2() : fPi(4.0 * atan(1.0)),
                                 wSampleRate(0.0f),
                                 wBufferSize(0.0f)
{
}


PajFFT_Radix2::~PajFFT_Radix2()
{
    
}




// =========================================================================================================================================
// == S E T T I N G S ======================================================================================================================
// =========================================================================================================================================
// ==== PRIVATE: ====
void PajFFT_Radix2::setSampleRate                          (float sampleR)
{
    wSampleRate = sampleR;
}


void PajFFT_Radix2::setBufferSize                          (float bufferS)
{
    wBufferSize = bufferS;
}


bool PajFFT_Radix2::resetData                        ()
{
    if(   bitReversal(wBufferSize) &&
          prepare_sN0_matrix()     &&
          prepareTwiddlesArray()      )
        return SETTINGS_READY;
    else
        return false;
}



// ==== PUBLIC: ====
bool PajFFT_Radix2::wSettings                              (float sampleRate, float bufferSize)
{
    setSampleRate(sampleRate);
    setBufferSize(bufferSize);
    
    if(resetData())
        return SETTINGS_READY;
    else
        return false;
}



// =========================================================================================================================================
// == P R E == C R E A T I O N =============================================================================================================
// =========================================================================================================================================
// ==== PRIVATE: ====
bool PajFFT_Radix2::bitReversal                           (float bufSize)
{
    bitReversed.resize(bufSize);
    
    for(int i=0; i<bitReversed.size(); i++)
    {
        bitReversed[i] = i;
    }
    
    unsigned long nn, n, m, j;
    
    nn = bitReversed.size()/2;
    n  = nn<<1;
    j  = 1;
    
    for (int i=1; i<n; i+=1)
    {
        if (j>i) {
            std::swap(bitReversed[j-1], bitReversed[i-1]);
        }
        
        m = nn;
        while (m>=2 && j>m)
        {
            j -= m;
            m >>= 1;
        }
        j += m;
    }
    
    return SETTINGS_READY;
}


bool PajFFT_Radix2::prepareTwiddlesArray                   ()
{
    wnkN_forw.resize(wBufferSize);
    
    for(unsigned int i=0; i<wBufferSize; i++)
    {
        wnkN_forw[i] = twiddleCalculator((float)i);
    }
    
    return SETTINGS_READY;
}


bool PajFFT_Radix2::prepare_sN0_matrix                     ()
{
    sN0.resize(log2(wBufferSize));
    for(int z=0; z<sN0.size(); z++)
    {
        sN0[z].resize(wBufferSize/pow(2, z+1));
        
        for(int i=0; i<sN0[z].size(); i++)
        {
            std::vector<std::complex<float>> temp;
            temp.resize(pow(2, z+1));
            sN0[z][i] = temp;
        }
    }
    
    return SETTINGS_READY;
}




// =========================================================================================================================================
// == F F T == A L G O R I T H M ===========================================================================================================
// =========================================================================================================================================
// ==== PUBLIC: ====
void PajFFT_Radix2::makeFFT                                (std::vector<float> &inputSignal, std::vector<std::vector<float>> &wOutputC, int channel)
{
    wOutputData = &wOutputC;

    for(int radix2=0; radix2<sN0.size(); radix2++)
    {
        if      (radix2==0)
            firstStepFFT(inputSignal, radix2);

        else if (radix2 >0 && radix2<sN0.size()-1)
            divideAndConquereFFT(radix2, wnkN_forw);

        else
            lastStepFFT(radix2, wnkN_forw);
    }
}


// PRIVATE:
void PajFFT_Radix2::firstStepFFT                           (std::vector<float> &inputSignal, int &rdx2)
{
    for(int k=0; k<wBufferSize/pow(2, rdx2+1); k++)
    {
        for(int n=0; n<pow(2, rdx2+1); n++)
        {
            sN0[rdx2][k][n]   = inputSignal[bitReversed[2*k]]
                                + pow(-1.0f, (float)(n/1))
                                * inputSignal[bitReversed[2*k+1]];

        }
    }
}


void PajFFT_Radix2::divideAndConquereFFT                   (int &rdx2, std::vector<std::complex<float>> &twiddle)
{
    for(int k=0; k<wBufferSize/pow(2, rdx2+1); k++)
    {
        for(int n=0; n<pow(2, rdx2+1); n++)
        {
            sN0[rdx2][k][n] = sN0[rdx2-1] [2*k][n%(int)pow(2, rdx2)]
                            +
                            pow(-1.0f, (float)(n/(int)pow(2, rdx2)))
                            *
                            (
                                  sN0[rdx2-1][2*k+1][n%(int)pow(2, rdx2)]
                                * twiddle[(n%(int)pow(2, rdx2)) * (int)(wBufferSize/pow(2.0f, (float)rdx2+1.0f))]
                            );
        }
    }
}


void PajFFT_Radix2::lastStepFFT                            (int &rdx2, std::vector<std::complex<float>> &twiddle)
{
    float wAvarageMag=0.0f;
    float wAvaragePha=0.0f;
    int dividerInt = ((wBufferSize/2)<1024)?1:((wBufferSize/2)/1024);
    float dividerFloat = (float)dividerInt;
    
    for(int k=0; k<wBufferSize/pow(2, rdx2+1); k++)
    {
        int binScale=0;
        
        for(int n=0; n<wBufferSize/2; n++)
        {
            sN0[rdx2][k][n] = sN0[rdx2-1] [2*k][n%(int)pow(2, rdx2)]
                            +
                            pow(-1.0f, (float)(n/(int)pow(2, rdx2)))
                            *
                            (
                                 sN0[rdx2-1][2*k+1][n%(int)pow(2, rdx2)]
                               * twiddle[(n%(int)pow(2, rdx2)) * (int)(wBufferSize/pow(2.0f, (float)rdx2+1.0f))]
                            );

            float tempMag = freqMagnitudeCalc(sN0[rdx2][k][n], n);
            float tempPha = phaseCalculator(sN0[rdx2][k][n], n);
            
            if(n<=512)
            {
                wOutputData->at(wMag)[binScale] = tempMag;
                wOutputData->at(wPha)[binScale] = tempPha;
                binScale++;
            }
            else if(n>512 && n<=32768)
            {
                wAvarageMag += tempMag;
                wAvaragePha += tempPha;
                if(n%dividerInt==0)
                {
                    wOutputData->at(wMag)[binScale] = wAvarageMag/dividerFloat;
                    wOutputData->at(wPha)[binScale] = wAvaragePha/dividerFloat;
                    wAvarageMag=0.0f;
                    wAvaragePha=0.0f;
                    binScale++;
                }
            }
        }
    }
}





// =========================================================================================================================================
// == C A L C U L A T O R S ================================================================================================================
// =========================================================================================================================================
// ==== PRIVATE: ====
std::complex<float> PajFFT_Radix2::twiddleCalculator       (float nXk)
{
    std::complex<float> wnk_N_temp;
    if((int)nXk % (int)wBufferSize == 0)
    {
        wnk_N_temp.real(1.0f);
        wnk_N_temp.imag(0.0f);
    }
    else if(((int)nXk%((int)wBufferSize/2)==0) && ((int)nXk % (int)wBufferSize != 0) && ((int)wBufferSize%2 == 0))
    {
        wnk_N_temp.real(-1.0f);
        wnk_N_temp.imag(0.0f);
    }
    else
    {
        wnk_N_temp.real(cosf(-2.0f * fPi * nXk / wBufferSize));
        wnk_N_temp.imag(sinf(-2.0f * fPi * nXk / wBufferSize));
    }
    return wnk_N_temp;
}


float PajFFT_Radix2::freqMagnitudeCalc               (std::complex<float> &fftOutput, long freqBin)
{
        float _Re_2;
        float _Im_2;
        _Re_2 = fftOutput.real() * fftOutput.real();
        _Im_2 = fftOutput.imag() * fftOutput.imag();

        return pow(_Re_2 + _Im_2, 0.5f);
}


float PajFFT_Radix2::phaseCalculator          (std::complex<float> &fftOutput, long freqBin)
{
    return atan2(fftOutput.imag(),fftOutput.real())/fPi;
//    return atan( (fftOutput.imag() / fftOutput.real()) )/fPi;
}
