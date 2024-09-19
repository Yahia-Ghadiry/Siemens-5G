#include "Ethernet/Ethernet.h"
#include <cstdint>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <fstream>

using std::vector;
using std::invalid_argument;
using std::ofstream;

int main(int argc, const char * argv[])
{
    if (argc < 3)
        throw invalid_argument("Program Should be excuated with options file and ouput file name ex: \"program_name options.txt output.txt\" ");


    EthernetOptions ethernetOptions(argv[1]);
    ofstream OuputFile(argv[2]);


    int TotalNumBursts = ethernetOptions.CalcTotalBursts();
    int NumIFGsPerBurst = ethernetOptions.CalcTotalIFGsPerBurst();
    
    for (int i = 0; i < TotalNumBursts; i++)
    {
        for (int j = 0; j < ethernetOptions.BurstSize; j++)
        {
            vector<uint8_t> DummyPayload(ethernetOptions.MaxPacketSize);
            std::generate(DummyPayload.begin(), DummyPayload.end(), std::rand);

            EthernetFrame ethernetFrame(ethernetOptions);
            ethernetFrame.SetPayload(DummyPayload);
            
            OuputFile << ethernetFrame; 
        }
        for (int j = 0; j < NumIFGsPerBurst; j++)
        {

            OuputFile << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(EthernetFrame::IFG);
            if (j % 4 ==3)
                OuputFile << std::endl;
        }
    }


    return 0;
}
