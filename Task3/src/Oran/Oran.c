#include "Oran.h"

using std::vector;
using std::copy;
using std::fill;

OranPacket::OranPacket()
{

    Payload = vector<uint8_t>(eCPRIHeaderSize);
    
    this->eCPRIVersion_Contacation = Payload.begin();
    this->eCPRIMessageType = this->eCPRIVersion_Contacation + 1;
    this->eCPRIPayloadSize = this->eCPRIMessageType + 1;
    this->eCPRI_RTC = this->eCPRIPayloadSize + 2;
    this->eCPRISeqID = this->eCPRI_RTC + 2;

    this->OranDirection_Version_fIndex = this->eCPRISeqID + 2;
    this->FramID = this->OranDirection_Version_fIndex + 1;
    this->SubFrameID_SlotIDp1 = this->FramID + 1;
    this->SlotIDp2_SymbolID = this->SubFrameID_SlotIDp1 + 1;
    
    this->SectionIDp1 = this->SlotIDp2_SymbolID + 1;
    this->SectionIDp2_rb_symlc_StartPRBUp1 = this->SectionIDp1 + 1;
    this->StartPRBUp2 = this->SectionIDp2_rb_symlc_StartPRBUp1 + 1;
    this->NumPRBUp = this->StartPRBUp2 + 1;

    this->IQSamples = this->NumPRBUp + 1;


    fill(this->eCPRIVersion_Contacation, this->eCPRIVersion_Contacation + 1, 0x00);
    copy(eCPRIType_IQdata.begin(), eCPRIType_IQdata.end(), this->eCPRIMessageType);
    // PayloadSize
    fill(this->eCPRI_RTC, this->eCPRI_RTC + 2, 0x00);
    // SeqID

    fill(this->OranDirection_Version_fIndex, this->OranDirection_Version_fIndex + 1, 0x00);
    // Frame ID
    // Subframe ID, slot IDpart 1
    // slot ID part 2, Symbol ID;
    
    copy(SectionID_rb_symlc_Configuration.begin(), SectionID_rb_symlc_Configuration.end(), this->SectionIDp1);
    //PRBU p1 
    //PRBU p2
    //NumPRBU

    
}


OranPacket::~OranPacket()
{
}
