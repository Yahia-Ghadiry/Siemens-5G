#ifndef _ORAN_H_
#define _ORAN_H_

#include <cstdint>
#include <array>
#include <vector>


class OranPacket
{
    public:
        
        static constexpr std::array<uint8_t, 2> eCPRIType_IQdata {0x00, 0x00};
    
    private:
    
        static const int eCPRIHeaderSize = 8;
        // eCPRI Header
        std::vector<uint8_t>::iterator eCPRIVersion_Contacation;
        std::vector<uint8_t>::iterator eCPRIMessage;
        std::vector<uint8_t>::iterator eCPRIPayload;
        std::vector<uint8_t>::iterator eCPRI_RTC;
        std::vector<uint8_t>::iterator eCPRISeqID;


        


        std::vector<uint8_t> Payload;
    
    public:
        
        OranPacket();

        

        ~OranPacket();

};

#endif
