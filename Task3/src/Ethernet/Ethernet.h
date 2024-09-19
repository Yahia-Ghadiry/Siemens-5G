#ifndef _ETHERNET_H_
#define _ETHERNET_H_

#include <cstdint>
#include <vector>
#include <string>
#include <array>
#include <ostream>

struct EthernetOptions;

class EthernetFrame
{       
    
    public:
        
        static constexpr std::array<uint8_t, 2> eCPRI_Type {0xAE, 0xFE};
            
    private:
        
        static const int HeadersSize = 22;
        static const int FCSSize = 4;

        int MinIFGs;
        int MaxSize; 

        static constexpr std::array<uint8_t, 8> Preamble_SFD {0xfb, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0xD5};
        std::vector<uint8_t>::iterator DestMAC;
        std::vector<uint8_t>::iterator SrcMAC;
        std::vector<uint8_t>::iterator EtherType;
        std::vector<uint8_t>::iterator Payload;
        int PayloadSize;
        std::vector<uint8_t>::iterator FCS;
        std::vector<uint8_t>::iterator IFGs;


        static const uint8_t IFG = 0x07;

        std::vector<uint8_t> Frame;
        
    public:
        
        EthernetFrame(const std::vector<uint8_t> &DestMAC, const std::vector<uint8_t> &SrcMAC, const std::array<uint8_t, 2> &EtherType, const std::vector<uint8_t> &Payload, const int &MinIFGS, const int &MaxSize);
        EthernetFrame(const EthernetOptions &FrameConfigrations);
        
        void SetPayload(const std::vector<uint8_t> &Payload);  


        ~EthernetFrame();

        friend std::ostream &operator<<(std::ostream &os, const EthernetFrame &EthernetFrame);   


    private:
        
        void CalculateFCS();
        void FillIFGs();
    
};

struct EthernetOptions
{
    int Linerate_GBs;
    int CaptureSize_ms;
    int MinIFGsPerPacket;
    std::string DestMAC;
    std::string SrcMAC;
    int MaxPacketSize;
    int BurstSize;
    int BurstPeriodicity_us;
    std::array<uint8_t, 2> EthernetType;

    EthernetOptions(const std::string &FileName);
    
    ~EthernetOptions();
};


#endif
