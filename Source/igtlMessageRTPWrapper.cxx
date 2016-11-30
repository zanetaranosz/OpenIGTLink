/*=========================================================================

  Program:   The OpenIGTLink Library
  Language:  C++
  Web page:  http://openigtlink.org/

  Copyright (c) Insight Software Consortium. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "igtlMessageRTPWrapper.h"
#include <string.h>


namespace igtl {
  
  MessageRTPWrapper::MessageRTPWrapper():Object(){
    this->SeqNum = 0;
    this->AvailabeBytesNum = RTP_PAYLOAD_LENGTH;
    this->numberOfDataFrag = 1;
    this->numberOfDataFragToSent = 1;
    this->packedMsg = NULL;
    this->appSpecificFreq = 100;
    this->status = PaketReady;
    this->curMSGLocation = 0;
    this->curPackedMSGLocation = 0;
    this->framentNumber = 0;
    this->MSGHeader= new igtl_uint8[IGTL_HEADER_SIZE];
    this->extendedHeaderSize = sizeof(igtl_extended_header);
  }
  
  MessageRTPWrapper::~MessageRTPWrapper()
  {
  }
  
  
  void MessageRTPWrapper::SetMSGHeader(igtl_uint8* header)
  {
    memcpy(this->MSGHeader, header, IGTL_HEADER_SIZE+this->extendedHeaderSize);
  }

  
  void MessageRTPWrapper::SetSSRC(igtl_uint32 identifier)
  {
    SSRC = identifier;
    if(igtl_is_little_endian())
    {
      SSRC = BYTE_SWAP_INT32(SSRC);
    }
  }
  
  void MessageRTPWrapper::SetCSRC(igtl_uint32 identifier)
  {
    CSRC = identifier;
    if(igtl_is_little_endian())
    {
      CSRC = BYTE_SWAP_INT32(CSRC);
    }
  }
  // SSRC should be set only once before wraping the message in a transmission session.
  // CSRC should be set when messages from different devices are packed into the same paket.
  // this special header is here for the compatiblity with standard RTP protocal.
  // we have our own defined openigtlink header, which is 58 byte size.
  // append the openigtlink header as the Extension header after CSRC.
  int MessageRTPWrapper::WrapMessage(igtl_uint8* messageContent, int bodyMsgLen)
  {
    // Set up the RTP header:
    igtl_uint32 rtpHdr = 0x80000000; // RTP version 2;
    rtpHdr |= (RTPPayLoadType<<16);
    rtpHdr |= SeqNum; // sequence number, increment the sequence number after sending the data
#if defined(WIN32) || defined(_WIN32)

                      //LARGE_INTEGER tick;
                      //
                      //::QueryPerformanceCounter( &tick );
                      //
                      //TimeStampType value = 
                      //    static_cast< TimeStampType >( (__int64)tick.QuadPart ) / 
                      //    this->m_WinFrequency;
                      //
                      //value += this->m_WinOrigin;
                      //
                      //double second = floor(value);

    clock_t c1 = clock();
    clock_t winClockOrigin = time(NULL);
    clock_t second =  + (c1 - winClockOrigin) / CLOCKS_PER_SEC;
    clock_t microsecond = (c1 - winClockOrigin) % CLOCKS_PER_SEC * (1e6 / CLOCKS_PER_SEC);
    clock_t timeIncrement = appSpecificFreq*second;
    timeIncrement += igtl_uint32(appSpecificFreq*(microsecond / 1.0e6) + 0.5);
#else
    struct timeval timeNow;
    gettimeofday(&timeNow, NULL);
    igtl_uint32 timeIncrement = (appSpecificFreq*timeNow.tv_sec); //need to check the frequency of different application
    timeIncrement += igtl_uint32(appSpecificFreq*(timeNow.tv_usec/1.0e6)+ 0.5);
#endif
    //igtl_uint32 CSRC = 0x00000000; not used currently
    if(igtl_is_little_endian())
    {
      rtpHdr = BYTE_SWAP_INT32(rtpHdr);
      timeIncrement = BYTE_SWAP_INT32(timeIncrement);
    }
    if (status == PaketReady)
    {
      delete packedMsg;
      packedMsg = new unsigned char[RTP_PAYLOAD_LENGTH + RTP_HEADER_LENGTH];
      AvailabeBytesNum = RTP_PAYLOAD_LENGTH;
      curMSGLocation = 0;
      curPackedMSGLocation = 0;
      framentNumber = 0;
    }
    if (status != WaitingForFragment)
    {
      this->fragmentTimeIncrement = timeIncrement;
      if (status != WaitingForAnotherMSG) // only add header at the paket begin
      {
        memmove(packedMsg, (void *)(&rtpHdr), 4);
        memmove(packedMsg+4, (void *)(&timeIncrement), 4);
        memmove(packedMsg+8, (void *)(&SSRC), 4); // SSRC needs to set by different devices, collision should be avoided.
        curPackedMSGLocation += RTP_HEADER_LENGTH;
      }
      if (bodyMsgLen <= (AvailabeBytesNum-IGTL_HEADER_SIZE-this->extendedHeaderSize))
      {
        igtl_uint16 temp = 0X0000;
        memmove(this->MSGHeader+IGTL_HEADER_SIZE+this->extendedHeaderSize-2, (void*)&temp,2);// no fragmented message here
        memmove(packedMsg+curPackedMSGLocation, this->MSGHeader, IGTL_HEADER_SIZE+this->extendedHeaderSize);
        curPackedMSGLocation += (IGTL_HEADER_SIZE + this->extendedHeaderSize);
        memmove(packedMsg + curPackedMSGLocation, (void *)(messageContent), bodyMsgLen);
        AvailabeBytesNum -= (bodyMsgLen+this->extendedHeaderSize+IGTL_HEADER_SIZE);
        curPackedMSGLocation += bodyMsgLen;
        if (AvailabeBytesNum > MinimumPaketSpace)// when it is packing the fragment, we want to sent the data ASAP, otherwize, we will wait for another message
        {
          status = WaitingForAnotherMSG;
        }
        else
        {
          status = PaketReady;
          SeqNum++;
        }
      }
      else if(bodyMsgLen > (AvailabeBytesNum-IGTL_HEADER_SIZE-this->extendedHeaderSize))
      {
        igtl_uint16 temp = 0X8000;
        if(igtl_is_little_endian())
        {
          temp = BYTE_SWAP_INT16(temp);
        }
        memmove(this->MSGHeader+IGTL_HEADER_SIZE+this->extendedHeaderSize-2, (void*)&temp,2);// no fragmented message here
        // fragmented message exists, first bit indicate the existance, the second bit indicates if the current section is the ending fragment, the other 14 bits indicates the fragements' sequence number.
        memmove(packedMsg+curPackedMSGLocation, this->MSGHeader, IGTL_HEADER_SIZE+this->extendedHeaderSize);
        curPackedMSGLocation += (IGTL_HEADER_SIZE + this->extendedHeaderSize);
        memmove(packedMsg + curPackedMSGLocation, (void *)(messageContent), AvailabeBytesNum-this->extendedHeaderSize-IGTL_HEADER_SIZE);
        status = WaitingForFragment;
        this->curPackedMSGLocation = RTP_PAYLOAD_LENGTH+RTP_HEADER_LENGTH;
        this->curMSGLocation = AvailabeBytesNum-IGTL_HEADER_SIZE-this->extendedHeaderSize;
        AvailabeBytesNum = RTP_PAYLOAD_LENGTH;
      }
    }
    else
    {
      memmove(packedMsg, (void *)(&rtpHdr), 4);
      memmove(packedMsg+4, (void *)(&this->fragmentTimeIncrement), 4);
      memmove(packedMsg+8, (void *)(&SSRC), 4); // SSRC needs to set by different devices, collision should be avoided.
      curPackedMSGLocation = RTP_HEADER_LENGTH;
      framentNumber++;
      if (bodyMsgLen <= (AvailabeBytesNum-IGTL_HEADER_SIZE-this->extendedHeaderSize))
      {
        igtl_uint16 temp = 0XE000+framentNumber; //set the seconde bit to be 1, indicates the end of fragmented msg.;
        if(igtl_is_little_endian())
        {
          temp = BYTE_SWAP_INT16(temp);
        }
        memmove(this->MSGHeader+IGTL_HEADER_SIZE+this->extendedHeaderSize-2, (void*)&temp,2);
        // fragmented message exists, first bit indicate the existance, the second bit indicates if the current section is the ending fragment, the other 14 bits indicates the fragements' sequence number.
        memmove(packedMsg+curPackedMSGLocation, this->MSGHeader, IGTL_HEADER_SIZE+this->extendedHeaderSize);
        curPackedMSGLocation += (IGTL_HEADER_SIZE + this->extendedHeaderSize);
        memmove(packedMsg + curPackedMSGLocation, (void *)(messageContent), bodyMsgLen);
        this->curPackedMSGLocation += bodyMsgLen;
        // when it is packing the fragment, we want to sent the data ASAP, otherwize, we will wait for another message
        status = PaketReady;
      }
      else if(bodyMsgLen > (AvailabeBytesNum-IGTL_HEADER_SIZE-this->extendedHeaderSize))
      {
        igtl_uint16 temp = 0X0800+framentNumber; //set the seconde bit to be 1, indicates the end of fragmented msg.;
        if(igtl_is_little_endian())
        {
          temp = BYTE_SWAP_INT16(temp);
        }
        memmove(this->MSGHeader+IGTL_HEADER_SIZE+this->extendedHeaderSize-2, (void*)&temp,2);//set the second bit to be 0, indicates more fragmented msg are comming.
        memmove(packedMsg+curPackedMSGLocation, MSGHeader, IGTL_HEADER_SIZE+this->extendedHeaderSize);
        curPackedMSGLocation += (IGTL_HEADER_SIZE + this->extendedHeaderSize);
        memmove(packedMsg + curPackedMSGLocation, (void *)(messageContent), AvailabeBytesNum-this->extendedHeaderSize-IGTL_HEADER_SIZE);
        status = WaitingForFragment;
        this->curMSGLocation += (AvailabeBytesNum-this->extendedHeaderSize-IGTL_HEADER_SIZE);
      }
      AvailabeBytesNum = RTP_PAYLOAD_LENGTH;
    }
    return status;
  }
  
  
  igtl::MessageBase::Pointer MessageRTPWrapper::UnWrapMessage(igtl_uint8* messageContent, int bodyMsgLen)
  {
    return NULL;
  }

} // namespace igtl