/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace pajAUanalyser
{
    extern const char*   buffToggleButton_true_png;
    const int            buffToggleButton_true_pngSize = 1637;

    extern const char*   magnitudeButton_false_png;
    const int            magnitudeButton_false_pngSize = 4820;

    extern const char*   magnitudeButton_true_png;
    const int            magnitudeButton_true_pngSize = 298;

    extern const char*   offButton_false_png;
    const int            offButton_false_pngSize = 3573;

    extern const char*   offButton_true_png;
    const int            offButton_true_pngSize = 193;

    extern const char*   phaseButton_false_png;
    const int            phaseButton_false_pngSize = 5550;

    extern const char*   phaseButton_true_png;
    const int            phaseButton_true_pngSize = 257;

    extern const char*   resetButton_false_png;
    const int            resetButton_false_pngSize = 5247;

    extern const char*   resetButton_true_png;
    const int            resetButton_true_pngSize = 275;

    extern const char*   pajLogoYellow_png;
    const int            pajLogoYellow_pngSize = 11487;

    extern const char*   buffToggleButton_1024_false_png;
    const int            buffToggleButton_1024_false_pngSize = 2880;

    extern const char*   buffToggleButton_2048_false_png;
    const int            buffToggleButton_2048_false_pngSize = 3758;

    extern const char*   buffToggleButton_4096_false_png;
    const int            buffToggleButton_4096_false_pngSize = 3619;

    extern const char*   buffToggleButton_8192_false_png;
    const int            buffToggleButton_8192_false_pngSize = 3873;

    extern const char*   buffToggleButton_16384_false_png;
    const int            buffToggleButton_16384_false_pngSize = 4427;

    extern const char*   buffToggleButton_32768_false_png;
    const int            buffToggleButton_32768_false_pngSize = 4870;

    extern const char*   buffToggleButton_65536_false_png;
    const int            buffToggleButton_65536_false_pngSize = 253;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 17;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
