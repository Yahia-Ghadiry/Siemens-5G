#ifndef _ETHERNET_H_
#define _ETHERNET_H_

#include <cstdint>

class EthernetFrame
{       
    
    public:
       
        static constexpr uint8_t eCPRI_Type[2] = {0xAE, 0xFE};
        
    private:
        
        int MinIFGs;
        int MaxSize;
        int PayloadSize;


        static constexpr uint8_t Preamble[7] = {0xfb, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55};
        static constexpr uint8_t SFD[1] = {0xD5};
        uint8_t DestMac[6];
        uint8_t SorMAC[6];
        uint8_t EtherType[2];
        const uint8_t *Paylod;
        uint8_t FCS[4];

        static constexpr uint8_t IFG[1] = {0x07};

        uint8_t *Frame;
        
    public:


    EthernetFrame();
    
    ~EthernetFrame();

    private:
        
        void CalculateFCS();
    



};





#endif
