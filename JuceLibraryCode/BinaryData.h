/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace pajAUanalyser
{
    extern const char*   pajLogoYellow_png;
    const int            pajLogoYellow_pngSize = 11976;

    extern const char*   buff_Icon_alt1_1024_png;
    const int            buff_Icon_alt1_1024_pngSize = 224;

    extern const char*   buff_Icon_alt1_2048_png;
    const int            buff_Icon_alt1_2048_pngSize = 260;

    extern const char*   buff_Icon_alt1_4096_png;
    const int            buff_Icon_alt1_4096_pngSize = 218;

    extern const char*   buff_Icon_alt1_8192_png;
    const int            buff_Icon_alt1_8192_pngSize = 240;

    extern const char*   buff_Icon_alt1_16384_png;
    const int            buff_Icon_alt1_16384_pngSize = 243;

    extern const char*   buff_Icon_alt1_32768_png;
    const int            buff_Icon_alt1_32768_pngSize = 231;

    extern const char*   buff_Icon_alt1_65536_png;
    const int            buff_Icon_alt1_65536_pngSize = 245;

    extern const char*   buff_Icon_alt2_1024_png;
    const int            buff_Icon_alt2_1024_pngSize = 14189;

    extern const char*   buff_Icon_alt2_2048_png;
    const int            buff_Icon_alt2_2048_pngSize = 14615;

    extern const char*   buff_Icon_alt2_4096_png;
    const int            buff_Icon_alt2_4096_pngSize = 14581;

    extern const char*   buff_Icon_alt2_8192_png;
    const int            buff_Icon_alt2_8192_pngSize = 13641;

    extern const char*   buff_Icon_alt2_16384_png;
    const int            buff_Icon_alt2_16384_pngSize = 12858;

    extern const char*   buff_Icon_alt2_32768_png;
    const int            buff_Icon_alt2_32768_pngSize = 11852;

    extern const char*   buff_Icon_alt2_65536_png;
    const int            buff_Icon_alt2_65536_pngSize = 10248;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 15;

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
