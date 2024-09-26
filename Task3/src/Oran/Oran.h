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
    
        // eCPRI Header
        static const int eCPRIHeaderSize = 8;

        std::vector<uint8_t>::iterator eCPRIVersion_Contacation;
        std::vector<uint8_t>::iterator eCPRIMessageType;
        std::vector<uint8_t>::iterator eCPRIPayloadSize;
        std::vector<uint8_t>::iterator eCPRI_RTC;
        std::vector<uint8_t>::iterator eCPRISeqID;

        
        std::vector<uint8_t>::iterator OranDirection_Version_fIndex;
        std::vector<uint8_t>::iterator FramID;
        std::vector<uint8_t>::iterator SubFrameID_SlotIDp1;
        std::vector<uint8_t>::iterator SlotIDp2_SymbolID;
        
        // SectionID is 4095 as specificed. rb is 0 for concurrent RBs , symlc is 0 to not increment SymbolNum.
        static constexpr std::array<uint8_t, 2> SectionID_rb_symlc_Configuration {0xFF, 0xF0};

        std::vector<uint8_t>::iterator SectionIDp1;
        std::vector<uint8_t>::iterator SectionIDp2_rb_symlc_StartPRBUp1;
        std::vector<uint8_t>::iterator StartPRBUp2;
        std::vector<uint8_t>::iterator NumPRBUp;
        


        // TODO Make sure negative samples don't cause error
        std::vector<uint8_t>::iterator IQSamples;


        std::vector<uint8_t> Payload;
    
    public:
        
        OranPacket();

        

        ~OranPacket();

};

#endif
