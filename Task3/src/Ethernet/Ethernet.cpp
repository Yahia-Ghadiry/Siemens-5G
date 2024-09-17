#include "Ethernet.h"
#include <cstdint>
#include <stdexcept>
#include <algorithm>

using std::invalid_argument;
using std::copy;

EthernetFrame::EthernetFrame(const vector<uint8_t> DestMAC, const vector<uint8_t> SrcMAC, const array<uint8_t, 2> EtherType, const vector<uint8_t> Payload, const int MinIFGs, const int MaxSize)
    : MinIFGs(MinIFGs), MaxSize(MaxSize)
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

    
    int FrameSize = HeadersSize + PayloadSize + FCSSize + MinIFGs;
   
    FrameSize += FrameSize % 4;

    Frame = vector<uint8_t>(FrameSize);  
    
    this->DestMAC = Frame.begin() + 8;
    this->SrcMAC = this->DestMAC + 6;
    this->EtherType = this->SrcMAC + 6;
    this->Payload = this->EtherType + 2;
    this->FCS = this->Payload + PayloadSize;
    this->IFGs = this->FCS + 4;
   

    copy(Preamble_SFD.begin(), Preamble_SFD.end(), Frame.begin());
    copy(DestMAC.begin(), DestMAC.end(), this->DestMAC);
    copy(SrcMAC.begin(), SrcMAC.end(), this->SrcMAC);
    copy(EtherType.begin(), EtherType.end(), this->EtherType);
    copy(Payload.begin(), Payload.end(), this->Payload);
    

    CalculateFCS();
    FillIFGs();

}




EthernetFrame::~EthernetFrame()
{

}

void EthernetFrame::CalculateFCS()
{
    
}


void EthernetFrame::FillIFGs()
{
    vector<uint8_t>::iterator i = IFGs;
    while(i != Frame.end())
    {
        *i = IFG;
        i += 1;
    }
}
