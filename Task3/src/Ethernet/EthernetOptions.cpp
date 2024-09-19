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

//tmp
#include <iostream>


bool CheckLineEmpty(const string &line);

EthernetOptions::EthernetOptions(const string &FileName)
{
    ifstream ConfigFile(FileName);
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
                Linerate_GBs = stoi(EthernetMemberValue);
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

        // Checks if line doesn't start with a commant or isn't emptpy
        else if (line.find("//") != 0 && !CheckLineEmpty(line))
        {
            std::cout << (int)line[0] << std::endl;
            throw invalid_argument("Error at Line: " + to_string(LineNo) + "\n Line must start with option or comment // \n Line is :" + line);
        }
        
    }

    EthernetType = EthernetFrame::eCPRI_Type; 
    
    ConfigFile.close();
}

EthernetOptions::~EthernetOptions()
{
}


bool CheckLineEmpty(const string &line)
{
    for (const char &c: line)
    {
        // Check for any visable characters
        if (c > 32)
            return false;
    }

    return true;
}
