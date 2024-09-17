#include "Ethernet.h"
#include <cstdint>
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
   
    FrameSize += FrameSize % 4;

    Frame = vector<uint8_t>(FrameSize);  
    
    this->DestMAC = Frame.begin() + 8;
    this->SrcMAC = this->DestMAC + 6;
    this->EtherType = this->SrcMAC + 6;
    this->Payload = this->EtherType + 2;
    this->FCS = this->Payload + PayloadSize;
    this->IFGS = this->FCS + 4;

    CalculateFCS();
    FillIFGS();

}




EthernetFrame::~EthernetFrame()
{

}


void EthernetFrame::FillIFGS()
{
    vector<uint8_t>::iterator i = IFGS;
    while(i != Frame.end())
    {
        *i = IFG;
        i += 1;
    }
}
