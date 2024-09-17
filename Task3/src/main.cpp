#include "Ethernet/Ethernet.h"
#include <cstdint>
#include <vector>
#include <iostream>

using std::vector;

int main()
{
    
    vector<uint8_t> TestDestMAC = {0x01, 0x01, 0x01, 0x01, 0x01, 0x01};
    vector<uint8_t> TestSrcMAC = {0x33, 0x33, 0x33, 0x33, 0x33, 0x33};
    
    int TestMaxSize = 1000;
    int TestMinIFGs = 3;
    
    vector<uint8_t> TestPayload(48, 0xFF);

    EthernetFrame TestFrame(TestDestMAC, TestSrcMAC, EthernetFrame::eCPRI_Type, TestPayload, TestMinIFGs, TestMaxSize);
    std::cout << TestFrame << std::endl; 
    return 0;
}
