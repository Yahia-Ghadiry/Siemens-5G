#include "Ethernet/Ethernet.h"
#include <cstdint>
#include <vector>
#include <iostream>
#include <stdexcept>

using std::vector;
using std::invalid_argument;

int main(int argc, const char * argv[])
{
    if (argc < 2)
        throw invalid_argument("Program Should be excuated with options file ex: \"program_name options.txt\" ");
    
    vector<uint8_t> TestDestMAC = {0x01, 0x01, 0x01, 0x01, 0x01, 0x01};
    vector<uint8_t> TestSrcMAC = {0x33, 0x33, 0x33, 0x33, 0x33, 0x33};
    
    int TestMaxSize = 1000;
    int TestMinIFGs = 3;

    vector<uint8_t> TestPayload(48, 0xFF);

    EthernetFrame TestFrame(TestDestMAC, TestSrcMAC, EthernetFrame::eCPRI_Type, TestPayload, TestMinIFGs, TestMaxSize);
    std::cout << TestFrame << std::endl; 


    EthernetOptions ethernetOptions(argv[1]);

    return 0;
}
