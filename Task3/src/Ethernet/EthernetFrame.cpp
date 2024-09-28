#include "Ethernet.h"
#include <cstdint>
#include <iomanip>
#include <ios>
#include <iterator>
#include <stdexcept>
#include <algorithm>
#include <cmath>

using std::vector;
using std::array;
using std::ostream;
using std::invalid_argument;
using std::copy;
using std::stoi;

EthernetFrame::EthernetFrame(const vector<uint8_t> &DestMAC, const vector<uint8_t> &SrcMAC, const array<uint8_t, 2> &EtherType, const vector<uint8_t> &Payload, const int &MinIFGs, const int &MaxSize)
    : MinIFGs(MinIFGs), MaxSize(MaxSize)
{

    PayloadSize = Payload.size();
    
    if(PayloadSize < 46)
       throw invalid_argument("Payload Size musn't be smaller than 46 bits"); 
    else if (PayloadSize > (MaxSize - HeadersSize - FCSSize))
       throw invalid_argument("Payload Size musn't be larger than MaxSize - HeadersSize - FCSSize"); 

    
    int FrameSize = HeadersSize + PayloadSize + FCSSize + MinIFGs;
   
    FrameSize += 4 - (FrameSize % 4);

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

EthernetFrame::EthernetFrame(const EthernetOptions &FrameConfigrations)
{
    MinIFGs = FrameConfigrations.MinIFGsPerPacket;
    MaxSize = FrameConfigrations.MaxPacketSize;
   
    
    vector<uint8_t> DestMAC(6);
    vector<uint8_t> SrcMAC(6);
    
    for (int i = 2; i < 14; i += 2)
    {
        DestMAC[i/2] = stoi(FrameConfigrations.DestMAC.substr(i, 2));
        SrcMAC[i/2] = stoi(FrameConfigrations.SrcMAC.substr(i, 2));
    }

    int FrameSize = HeadersSize;

    Frame = vector<uint8_t>(FrameSize);  
    

    this->DestMAC = Frame.begin() + 8;
    this->SrcMAC = this->DestMAC + 6;
    EtherType = this->SrcMAC + 6;
    
    
    copy(Preamble_SFD.begin(), Preamble_SFD.end(), Frame.begin());
    copy(DestMAC.begin(), DestMAC.end(), this->DestMAC);
    copy(SrcMAC.begin(), SrcMAC.end(), this->SrcMAC);
    copy(FrameConfigrations.EthernetType.begin(), FrameConfigrations.EthernetType.end(), EtherType);
}

void EthernetFrame::SetPayload(const std::vector<uint8_t> &Payload)
{
    PayloadSize = Payload.size();
        
    int FrameSize = HeadersSize + PayloadSize + FCSSize + MinIFGs;
   
    FrameSize += 4 - (FrameSize % 4);

    Frame.resize(FrameSize);  
    
    this->DestMAC = Frame.begin() + 8;
    this->SrcMAC = this->DestMAC + 6;
    this->EtherType = this->SrcMAC + 6;
    this->Payload = this->EtherType + 2;
    this->FCS = this->Payload + PayloadSize;
    this->IFGs = this->FCS + 4;
   

    copy(Payload.begin(), Payload.end(), this->Payload);
    
    CalculateFCS();
    FillIFGs();
}


int EthernetFrame::GetFrameSize()
{
    return Frame.size();
}



void EthernetFrame::CalculateFCS()
{
    // Calculating the size of FrameDivion, and shifting it if it isn't a multiple of 4
    int offset = std::distance(DestMAC, IFGs) % 4;
    int sizeFCSincluded = std::ceil(std::distance(DestMAC, IFGs) / 4.0) ;
    
    vector<uint32_t> FrameDivison(sizeFCSincluded);
    vector<uint8_t>::iterator curByte = DestMAC - (4 - offset);
    
    for (uint32_t &Dword: FrameDivison)
    {
        Dword = ((*curByte) << 24) + (*(curByte + 1) << 16) + (*(curByte + 2) << 8) + *(curByte + 3);
        curByte += 4;
    }
    
    // Removing preamble data goten from shift and adding startreg
    if (offset != 0)
    {
        FrameDivison[0] &= ~(0xFFFFFFFF << offset * 8);
        FrameDivison[0] ^= (0xFFFFFFFF >> (4 - offset) * 8);
        FrameDivison[1] ^= (0xFFFFFFFF << offset * 8);
    }
    else
    {
        FrameDivison[0] ^= 0xFFFFFFFF;
    }

    uint32_t FCS;
    uint32_t Polynomial = 0x04C11DB7;
    
    vector<uint32_t>::iterator curDWORD = FrameDivison.begin();

    while(curDWORD != FrameDivison.end() - 1)
    {

        if (*curDWORD == 0)
        {
            curDWORD++;
            continue;
        }
        
        int firstBit = __builtin_clz(*curDWORD);
        if (firstBit == 31)
        {
            *curDWORD = 0;
            *(curDWORD + 1) ^= Polynomial;
            curDWORD++;
            continue;
        }

        *curDWORD ^= Polynomial >> (firstBit + 1);
        *curDWORD ^= 0x1 << (32 - (firstBit + 1));
        
        *(curDWORD + 1) ^= Polynomial << (32 - (firstBit + 1));
    }


    FCS = *(FrameDivison.end() -1) ^ 0xFFFFFFFF;
    
    for (int i = 0; i < 4; i++)
    {
        *(this->FCS + i) = ((0xFF000000 >> i * 8) & FCS) >> (3 - i) * 8;
        
    }
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



ostream &operator<<(ostream &os, const EthernetFrame &ethernetFrame)
{
    int ByteNo = 0;
    
    for (const uint8_t &byte: ethernetFrame.Frame)
    {
        os << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << static_cast<int>(byte);
        ByteNo++;
        ByteNo %= 4;
        if (ByteNo == 0)
        {
            os << std::endl;
        }
    }

    // Restoring defaults
    os << std::setfill(' ') << std::setw(0) << std::nouppercase << std::dec;
    
    return os;
}
