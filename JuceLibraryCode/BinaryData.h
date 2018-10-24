/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace pajAUanalyser
{
    extern const char*   StartHere_ban_png;
    const int            StartHere_ban_pngSize = 451;

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

    extern const char*   buffToggleButton_true_png;
    const int            buffToggleButton_true_pngSize = 1468;

    extern const char*   pajLogoYellow_png;
    const int            pajLogoYellow_pngSize = 11976;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 9;

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
