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
    

    EthernetOptions ethernetOptions(argv[1]);

    vector<uint8_t> TestPayload(48, 0xFF);
    
    EthernetFrame TestFrame(ethernetOptions);
    TestFrame.SetPayload(TestPayload);

    std::cout << TestFrame << std::endl; 



    return 0;
}
