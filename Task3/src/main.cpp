#include "Ethernet/Ethernet.h"
#include <cstdint>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <iomanip>
#include <random>
#include <algorithm>

using std::vector;
using std::invalid_argument;

int main(int argc, const char * argv[])
{
    if (argc < 3)
        throw invalid_argument("Program Should be excuated with options file and ouput file name ex: \"program_name options.txt output.txt\" ");


    EthernetOptions ethernetOptions(argv[1]);
    

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
            
            std::cout << ethernetFrame; 
        }
        for (int j = 0; j < NumIFGsPerBurst; j++)
        {

            std::cout << std::setfill('0') << std::setw(2) << std::hex << EthernetFrame::IFG;
            if (j % 4 ==3)
            {
                std::cout << std::endl;
            }
        }
    }


    return 0;
}
