#include "Ethernet.h"
#include <cstdint>
#include <iomanip>
#include <iterator>
#include <stdexcept>
#include <algorithm>
#include <cmath>

//tmp
#include <iostream>
using std::invalid_argument;
using std::copy;

EthernetFrame::EthernetFrame(const vector<uint8_t> DestMAC, const vector<uint8_t> SrcMAC, const array<uint8_t, 2> EtherType, const vector<uint8_t> Payload, const int MinIFGs, const int MaxSize)
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
   
    FrameSize += 4 - FrameSize % 4;

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

ostream &operator<<(ostream &os, const EthernetFrame &ethernetFrame)
{
    int ByteNo = 0;
    
    for (const uint8_t &byte: ethernetFrame.Frame)
    {
        os << std::setfill('0') << std::setw(2)<< std::uppercase <<std::hex << static_cast<int>(byte);
        ByteNo++;
        ByteNo %= 4;
        if (ByteNo == 0)
        {
            os << std::endl;
        }
    }
    return os;
}


void EthernetFrame::CalculateFCS()
{
    // Calculating the size of FrameDivion, and shifting it if it isn't a multiple of 4
    int offset = std::distance(DestMAC, IFGs) % 4;
    int sizeFCSincluded = std::ceil(std::distance(DestMAC, IFGs) / 4.0);
    
    vector<uint32_t> FrameDivison(sizeFCSincluded);
    vector<uint8_t>::iterator curByte = DestMAC - offset;
    
    for (uint32_t &Dword: FrameDivison)
    {
        Dword = ((*curByte) << 24) + (*(curByte + 1) << 16) + (*(curByte + 2) << 8) + *(curByte + 3);
        curByte += 4;
    }
    
    // removing preamble data goten from shift
    FrameDivison[0] &= ~(0xFFFFFFFF << (4 - offset) * 8);


    // tmp printng
    std::cout << std::endl;
    for (auto c: FrameDivison)
    {

        std::cout << std::setfill('0') << std::setw(8)<< std::uppercase <<std::hex << static_cast<int>(c) << std::endl;
    }
    std::cout << std::endl;
    uint32_t CRC = 0xFFFFFFFF;
    uint32_t Polynomial = 0x04C11DB7;


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


EthernetFrame::~EthernetFrame()
{
}
