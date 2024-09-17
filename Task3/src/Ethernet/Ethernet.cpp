#include "Ethernet.h"
#include <stdexcept>

using std::invalid_argument;

EthernetFrame::EthernetFrame(const vector<uint8_t> DestMAC, const vector<uint8_t> SrcMAC, const vector<uint8_t> EtherType, const vector<uint8_t> Payload, const int MinIFGS, const int MaxSize)
    : MinIFGs(MinIFGS), MaxSize(MaxSize)
{

    PayloadSize = Payload.size();

    if(PayloadSize < 46)
    {
       throw invalid_argument("Payload Size musn't be smaller than 46 bits"); 
    }
    else if (PayloadSize > (MaxSize - HeadersSize - FCSSize))
    {
       throw invalid_argument("Payload Size musn't be larger than MaxSize - HeadersSize - FCSSize"); 
    }

    
    int FrameSize = HeadersSize + PayloadSize + FCSSize + MinIFGS;
    
    

    CalculateFCS();

}

