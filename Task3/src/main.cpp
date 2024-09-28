#include "Ethernet/Ethernet.h"
#include "Oran/Oran.h"
#include <cstdint>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <iomanip>
#include <fstream>

using std::vector;
using std::invalid_argument;
using std::ofstream;

int main(int argc, const char * argv[])
{
    if (argc < 3)
        throw invalid_argument("Program Should be excuated with options file and ouput file name ex: \"program_name options.txt output.txt\" ");


    EthernetOptions ethernetOptions(argv[1]);
    OranOptions oranOptions(argv[1]);
    ofstream OuputFile(argv[2]);
    

    EthernetFrame frame(ethernetOptions);
    

    int NumberOfFrames = ethernetOptions.CaptureSize_ms / 10;

    if (NumberOfFrames * 10 != ethernetOptions.CaptureSize_ms)
        std::cout << "Warning Capture Size only implemented for 10ms Multiples. It will be rounded down." << std::endl;
    
    int SlotSize = 0; // TODO Should add a better way to calculate Symbol Size
    
    while (true)
    {
        
            frame.SetPayload(oranOptions.GetPacket().GetPayload());
            if (oranOptions.FrameID == NumberOfFrames) // break when enough frames read
                break;
            OuputFile << frame;
            SlotSize += frame.GetFrameSize();
            if (oranOptions.SymbolID == 0) // Check if starting new Symbol
            {
              
                int SlotSize_b = SlotSize * 8;
                float SlotTime_us = (float) SlotSize_b / (ethernetOptions.Linerate_Gbs * 1000);
                float IFGsTime_us = ((float) 1000 /  oranOptions.nSlots) - SlotTime_us;
                int NumIFGsPerSlot = (IFGsTime_us * ethernetOptions.Linerate_Gbs * 1000) / 8;
                NumIFGsPerSlot += 4 - NumIFGsPerSlot % 4;
                
                for (int j = 0; j < NumIFGsPerSlot; j++)
                {
                    OuputFile << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(EthernetFrame::IFG);
                    if (j % 4 ==3)
                    OuputFile << std::endl;
                }

                SlotSize = 0;
            }

    }
    return 0;
}
