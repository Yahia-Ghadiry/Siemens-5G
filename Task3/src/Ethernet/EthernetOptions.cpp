#include "Ethernet.h"
#include <cstdio>
#include <fstream>
#include <stdexcept>
#include <algorithm>

using std::string;
using std::ifstream;
using std::invalid_argument;
using std::to_string;
using std::stoi;
using std::min;

bool CheckLineEmptyEth(const string &line);

EthernetOptions::EthernetOptions(const string &FileName)
{
    ifstream ConfigFile(FileName);
    if (ConfigFile.fail())
        throw invalid_argument("File :" + FileName + " Doesn't exist, Please input the correct file name.");

    string line;
    
    int LineNo = 0;

    while (getline(ConfigFile, line))
    {
        
        LineNo++;
        if (line.substr(0, line.find('.')) == "Eth")
        {
            // Only takes part between . and  space or = 
            string EthernetMember = line.substr(4, min(line.find(' ', 4), line.find('=', 4)) - 4);
            // Takes part after = or space till comment or other
            int EqualPosition = line.find('=', 4);
            string EthernetMemberValue =  line.substr(EqualPosition + 1, min((line.find("//") - 1), line.length() - 1) - EqualPosition);
            // Removes trailling and leading space/tabs/return charachters
            EthernetMemberValue.erase(0, EthernetMemberValue.find_first_not_of(' '));
            EthernetMemberValue.erase(EthernetMemberValue.find_last_not_of(' ') + 1);
            EthernetMemberValue.erase(0, EthernetMemberValue.find_first_not_of('\t'));
            EthernetMemberValue.erase(EthernetMemberValue.find_last_not_of('\t') + 1);
            EthernetMemberValue.erase(EthernetMemberValue.find_last_not_of('\n') + 1);
            EthernetMemberValue.erase(EthernetMemberValue.find_last_not_of('\r') + 1);
            
            if (EthernetMember == "LineRate")
                Linerate_Gbs = stoi(EthernetMemberValue);
            else if (EthernetMember == "CaptureSizeMs")
                CaptureSize_ms = stoi(EthernetMemberValue);
            else if (EthernetMember == "MinNumOfIFGsPerPacket")
                MinIFGsPerPacket = stoi(EthernetMemberValue);
            else if (EthernetMember == "DestAddress")
                DestMAC = EthernetMemberValue;
            else if (EthernetMember == "SourceAddress")
                SrcMAC = EthernetMemberValue;
            else if (EthernetMember == "MaxPacketSize")
                MaxPacketSize = stoi(EthernetMemberValue);
            else if (EthernetMember == "BurstSize")
                BurstSize = stoi(EthernetMemberValue);
            else if (EthernetMember == "BurstPeriodicity_us")
                BurstPeriodicity_us = stoi(EthernetMemberValue);
            else
                throw invalid_argument("Error at Line: " + to_string(LineNo) + "\n Line must Option for Eth. Not found // \n Line is :" + line + "\nOptions is: " + EthernetMember);
            
        }
        else if (line.substr(0, line.find('.')) == "Oran"); // Ignore Oran options
        // Checks if line doesn't start with a commant or isn't emptpy
        else if (line.find("//") != 0 && !CheckLineEmptyEth(line))
            throw invalid_argument("Error at Line: " + to_string(LineNo) + "\n Line must start with option or comment // \n Line is :" + line);
        
    }

    EthernetType = EthernetFrame::EtherType_eCPRI; 
    
    ConfigFile.close();
}

int EthernetOptions::CalcTotalBursts()
{
    int ToatalNumBursts = (CaptureSize_ms * 1000) / BurstPeriodicity_us;
    return ToatalNumBursts;
}

int EthernetOptions::CalcTotalIFGsPerBurst()
{
    int BurstsSize_b = BurstSize * MaxPacketSize * 8;
    float BurstsTime_us = (float) BurstsSize_b / (Linerate_Gbs * 1000);
    float IFGsTime_us = BurstPeriodicity_us - BurstsTime_us;
    int NumIFGsPerBurst = (IFGsTime_us * Linerate_Gbs * 1000) / 8;
    NumIFGsPerBurst += 4 - NumIFGsPerBurst % 4;
    return NumIFGsPerBurst;
}

EthernetOptions::~EthernetOptions()
{
}


bool CheckLineEmptyEth(const string &line)
{
    for (const char &c: line)
    {
        // Check for any visable characters
        if (c > 32)
            return false;
    }

    return true;
}
