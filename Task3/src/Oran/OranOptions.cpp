#include "Oran.h"

#include <fstream>
#include <stdexcept>


using std::string;
using std::ifstream;
using std::invalid_argument;
using std::to_string;
using std::stoi;
using std::min;

bool CheckLineEmptyOran(const string &line);
int intlog2(int x);

OranOptions::OranOptions(const string &FileName)
{
    uint32_t SCS_kHz; // not using int to make sure when doing error checking sum of ctz and clz are 31

    ifstream ConfigFile(FileName);
    if (ConfigFile.fail())
        throw invalid_argument("File :" + FileName + " Doesn't exist, Please input the correct file name.");

    string line;
    
    int LineNo = 0;

    while (getline(ConfigFile, line))
    {
        
        LineNo++;
        if (line.substr(0, line.find('.')) == "Oran")
        {
            // Only takes part between . and  space or = 
            string OranMember = line.substr(5, min(line.find(' ', 5), line.find('=', 5)) - 5);
            // Takes part after = or space till comment or other
            int EqualPosition = line.find('=', 5);
            string OranMemberValue =  line.substr(EqualPosition + 1, min((line.find("//") - 1), line.length() - 1) - EqualPosition);
            // Removes trailling and leading space/tabs/return charachters
            OranMemberValue.erase(0, OranMemberValue.find_first_not_of(' '));
            OranMemberValue.erase(OranMemberValue.find_last_not_of(' ') + 1);
            OranMemberValue.erase(0, OranMemberValue.find_first_not_of('\t'));
            OranMemberValue.erase(OranMemberValue.find_last_not_of('\t') + 1);
            OranMemberValue.erase(OranMemberValue.find_last_not_of('\n') + 1);
            OranMemberValue.erase(OranMemberValue.find_last_not_of('\r') + 1);
            
            if (OranMember == "SCS")
                SCS_kHz = stoi(OranMemberValue);
            else if (OranMember == "MaxMrb")
                MaxRBs = stoi(OranMemberValue);
            else if (OranMember == "NrbPerPacket")
                nRBPerPacket = stoi(OranMemberValue);
            else if (OranMember == "PayloadType")
                PayloadType = OranMemberValue;
            else if (OranMember == "Payload")
                PayloadFile = OranMemberValue;
            else
                throw invalid_argument("Error at Line: " + to_string(LineNo) + "\n Line must Option for Oran. Not found // \n Line is :" + line + "\nOptions is: " + OranMember);
            
        }
        else if (line.substr(0, line.find('.')) == "Eth"); // Ignore Eth options
        // Checks if line doesn't start with a commant or isn't emptpy
        else if (line.find("//") != 0 && !CheckLineEmptyOran(line))
            throw invalid_argument("Error at Line: " + to_string(LineNo) + "\n Line must start with option or comment // \n Line is :" + line);
        
    }

    ConfigFile.close();


    if (SCS_kHz % 15 != 0 || __builtin_ctz(SCS_kHz / 15) + __builtin_clz(SCS_kHz / 15) != 31) // Fast way to check if power of 2
        throw invalid_argument("SCS need to be in the form 15 * 2^u");
    nSlots = SCS_kHz / 15;

    SeqID = 0;
    FrameID = 0;
    SubFrameID = 0;
    SlotID = 0;
    SymbolID = 0;
    PRBStart = 0;
}


OranOptions::~OranOptions()
{
}

bool CheckLineEmptyOran(const string &line)
{
    for (const char &c: line)
    {
        // Check for any visable characters
        if (c > 32)
            return false;
    }

    return true;
}

int intlog2(int x)
{
}
