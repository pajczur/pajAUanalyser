/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

namespace pajAUanalyser
{

//================== pajLogoYellow.png ==================
static const unsigned char temp_binary_data_0[] =
{ 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,15,0,0,0,15,8,6,0,0,0,59,214,149,74,0,0,0,6,98,75,71,68,0,255,0,255,0,255,160,189,167,147,0,0,0,9,112,72,89,115,0,0,46,35,0,0,46,35,1,120,165,63,118,0,0,0,7,116,73,77,69,7,226,10,11,20,2,44,17,40,138,
68,0,0,0,25,116,69,88,116,67,111,109,109,101,110,116,0,67,114,101,97,116,101,100,32,119,105,116,104,32,71,73,77,80,87,129,14,23,0,0,0,108,73,68,65,84,40,207,181,82,201,13,192,48,8,51,108,145,253,135,203,24,244,133,132,28,23,81,69,245,43,225,48,200,6,
184,69,108,68,108,4,199,56,199,117,158,15,91,176,90,84,227,149,180,254,157,39,125,129,191,177,78,8,125,178,222,104,114,78,203,70,69,160,196,109,157,192,111,200,85,148,85,236,241,225,179,45,216,68,32,174,113,37,84,183,225,113,36,170,81,9,85,175,176,181,
96,162,195,21,30,96,62,102,245,26,103,103,191,0,0,0,0,73,69,78,68,174,66,96,130,0,0 };

const char* pajLogoYellow_png = (const char*) temp_binary_data_0;


const char* getNamedResource (const char* resourceNameUTF8, int& numBytes)
{
    unsigned int hash = 0;
    if (resourceNameUTF8 != 0)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0x6c86b0e2:  numBytes = 260; return pajLogoYellow_png;
        default: break;
    }

    numBytes = 0;
    return nullptr;
}

const char* namedResourceList[] =
{
    "pajLogoYellow_png"
};

const char* originalFilenames[] =
{
    "pajLogoYellow.png"
};

const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8)
{
    for (unsigned int i = 0; i < (sizeof (namedResourceList) / sizeof (namedResourceList[0])); ++i)
    {
        if (namedResourceList[i] == resourceNameUTF8)
            return originalFilenames[i];
    }

    return nullptr;
}

}
