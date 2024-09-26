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

    fill(this->eCPRIVersion_Contacation, this->eCPRIVersion_Contacation + 1, 0x00);
    copy(eCPRIType_IQdata.begin(), eCPRIType_IQdata.end(), this->eCPRIMessageType);
    // PayloadSize
    fill(this->eCPRI_RTC, this->eCPRI_RTC + 2, 0x00);
    // SeqID

    fill(this->OranDirection_Version_fIndex, this->OranDirection_Version_fIndex + 1, 0x00);
    

    
    
}
