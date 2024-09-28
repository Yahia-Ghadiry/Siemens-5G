#include "Oran.h"
#include <cstdint>
#include <stdexcept>

using std::vector;
using std::copy;
using std::fill;
using std::pair;
using std::invalid_argument;

OranPacket::OranPacket(const uint8_t &SeqID, const uint8_t &FrameID, const uint8_t &SubFrameID, const uint8_t &SlotID, const uint8_t &SympolID, const uint16_t &PRBStart, const vector<pair<int8_t, int8_t>> &IQSamples)
{

    
    uint8_t NumPRBs = IQSamples.size() / 12;
    
    if (NumPRBs * 12 != IQSamples.size())
        throw invalid_argument("IQ samples need to be a multiple of 12 (Full RBs)");



    Payload = vector<uint8_t>(eCPRIHeaderSize + OranHeadersSize + IQSamples.size() * 2); // Note: If I and Q use 2 bytes each need to adjuse
    

    // Setting Iterators for each section
    this->eCPRIVersion_Contacation = Payload.begin();
    this->eCPRIMessageType = this->eCPRIVersion_Contacation + 1;
    this->eCPRIPayloadSize = this->eCPRIMessageType + 1;
    this->eCPRI_RTC = this->eCPRIPayloadSize + 2;
    this->eCPRISeqID = this->eCPRI_RTC + 2;

    this->OranDirection_Version_fIndex = this->eCPRISeqID + 2;
    this->FrameID = this->OranDirection_Version_fIndex + 1;
    this->SubFrameID_SlotIDp1 = this->FrameID + 1;
    this->SlotIDp2_SymbolID = this->SubFrameID_SlotIDp1 + 1;
    
    this->SectionIDp1 = this->SlotIDp2_SymbolID + 1;
    this->SectionIDp2_rb_symlc_StartPRBUp1 = this->SectionIDp1 + 1;
    this->StartPRBUp2 = this->SectionIDp2_rb_symlc_StartPRBUp1 + 1;
    this->NumPRBUp = this->StartPRBUp2 + 1;

    this->IQSamples = this->NumPRBUp + 1;


    // Setting everything in the correct bit postions
    fill(this->eCPRIVersion_Contacation, this->eCPRIVersion_Contacation + 1, 0x00);
    copy(eCPRIType_IQdata.begin(), eCPRIType_IQdata.end(), this->eCPRIMessageType);
    *(this->eCPRIPayloadSize) = OranHeadersSize + IQSamples.size() * 2; 
    fill(this->eCPRI_RTC, this->eCPRI_RTC + 2, 0x00);
    *(this->eCPRISeqID) = SeqID;

    fill(this->OranDirection_Version_fIndex, this->OranDirection_Version_fIndex + 1, 0x00);
    *(this->FrameID) = FrameID;
    *(this->SubFrameID_SlotIDp1) = (SubFrameID << 4) + ((SlotID >> 2) & 0b00001111);
    *(this->SlotIDp2_SymbolID) = (SlotID << 6) + (SympolID & 0b00111111);
    
    copy(SectionID_rb_symlc_Configuration.begin(), SectionID_rb_symlc_Configuration.end(), this->SectionIDp1);
    *(this->SectionIDp2_rb_symlc_StartPRBUp1) += ((PRBStart >> 8) & 0b00000011); 
    *(this->StartPRBUp2) = (PRBStart & 0b11111111);
    *(this->NumPRBUp) = NumPRBs;


   FillIQ(IQSamples); 
}


// Converts IQ samples to appropiate formate and puts them in the Packet
// Seprate function for future use If we need compression
void OranPacket::FillIQ(const std::vector<std::pair<int8_t, int8_t>> &IQSamples)
{

    for (int i = 0; IQSamples.size(); i++)
    {
        *(this->IQSamples + 2 * i) = static_cast<uint8_t>(IQSamples[i].first);
        *(this->IQSamples + 2 * i + 1) = static_cast<uint8_t>(IQSamples[i].second);
    }

}

OranPacket::~OranPacket()
{
}
