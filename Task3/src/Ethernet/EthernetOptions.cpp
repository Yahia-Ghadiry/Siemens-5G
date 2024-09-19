#include "Ethernet.h"
#include <cstdio>
#include <fstream>
#include <stdexcept>

using std::string;
using std::ifstream;
using std::invalid_argument;
using std::to_string;

//tmp
#include <iostream>


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
            
        }
        else if (line.find("//") != 0)
        {
            throw invalid_argument("Error at Line :" + to_string(LineNo) + "\n Line must start with option or comment // \n Line is :" + line);
        }
        
    }
 
    ConfigFile.close();
}

EthernetOptions::~EthernetOptions()
{
}

