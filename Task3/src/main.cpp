#include "Ethernet/Ethernet.h"
#include <cstdint>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <random>
#include <iomanip>

using std::vector;
using std::invalid_argument;
using std::floor;

int main(int argc, const char * argv[])
{
    if (argc < 2)
        throw invalid_argument("Program Should be excuated with options file ex: \"program_name options.txt\" ");


    int IFG = 0x07;

    EthernetOptions ethernetOptions(argv[1]);
    

    int TotalNumBursts = (ethernetOptions.CaptureSize_ms * 1000) /ethernetOptions.BurstPeriodicity_us;
    int BurstsSize_b = ethernetOptions.BurstSize * ethernetOptions.MaxPacketSize * 8;
    float BurstsTime_us = (float) BurstsSize_b / (ethernetOptions.Linerate_Gbs * 1000);
    float IFGsTime_us = ethernetOptions.BurstPeriodicity_us - BurstsTime_us;
    int NumOfIFGsPerBurst = (IFGsTime_us * ethernetOptions.Linerate_Gbs * 1000) / 8;
    NumOfIFGsPerBurst += 4 - NumOfIFGsPerBurst % 4;
    for (int i = 0; i < TotalNumBursts; i++)
    {
        for (int j = 0; j < ethernetOptions.BurstSize; j++)
        {
            vector<uint8_t> TestPayload(ethernetOptions.MaxPacketSize, 0xFF);
            EthernetFrame TestFrame(ethernetOptions);
            TestFrame.SetPayload(TestPayload);
            std::cout << TestFrame; 
        }
        for (int j = 0; j < NumOfIFGsPerBurst; j++)
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
