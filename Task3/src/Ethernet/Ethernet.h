#ifndef _ETHERNET_H_
#define _ETHERNET_H_

#include <cstdint>
#include <vector>
#include <array>

using std::vector;
using std::array;

class EthernetFrame
{       
    
    public:
       
        static constexpr array<uint8_t, 2> eCPRI_Type = {0xAE, 0xFE};
        
    private:
        int MinIFGs;
        int MaxSize;
        
        static const int HeadersSize = 22;
        static const int FCSSize = 4;

        static constexpr array<uint8_t, 8> Preamble_SFD {0xfb, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0xD5};
        vector<uint8_t>::iterator DestMAC;
        vector<uint8_t>::iterator SrcMAC;
        vector<uint8_t>::iterator EtherType;
        vector<uint8_t>::iterator Payload;
        int PayloadSize;
        vector<uint8_t>::iterator FCS;
        vector<uint8_t>::iterator IFGS;


        static const uint8_t IFG = 0x07;

        vector<uint8_t> Frame;
        
    public:


    EthernetFrame(const vector<uint8_t> DestMAC, const vector<uint8_t> SrcMAC, const vector<uint8_t> EtherType, const vector<uint8_t> Payload, const int MinIFGS, const int MaxSize);


    ~EthernetFrame();

    private:
        
        void CalculateFCS();
        void FillIFGS();
    
};



#endif
