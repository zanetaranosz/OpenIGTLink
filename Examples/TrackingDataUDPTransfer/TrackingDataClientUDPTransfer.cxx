/*=========================================================================

  Program:   Open IGT Link -- Example for Tracker Client Program
  Module:    $RCSfile: $
  Language:  C++
  Date:      $Date: $
  Version:   $Revision: $

  Copyright (c) Insight Software Consortium. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include <iostream>
#include <math.h>
#include <cstdlib>
#include <cstring>

#include <string.h>

#include "igtlOSUtil.h"
#include "igtlTrackingDataMessage.h"
#include "igtlMessageRTPWrapper.h"
#include "igtlUDPClientSocket.h"


int ReceiveTrackingData(igtl::MessageBase::Pointer& msgData);

int main(int argc, char* argv[])
{
  //------------------------------------------------------------
  // Parse Arguments

  if (argc != 4) // check number of arguments
    {
    // If not correct, print usage
    std::cerr << "Usage: " << argv[0] << " <hostname> <port> <fps>"    << std::endl;
    std::cerr << "    <hostname> : IP or host name"                    << std::endl;
    std::cerr << "    <port>     : Port # (18944 in Slicer default)"   << std::endl;
    std::cerr << "    <fps>      : Frequency (fps) to send coordinate" << std::endl;
    exit(0);
    }

  char*  hostname = argv[1];
  int    port     = atoi(argv[2]);
  double fps      = atof(argv[3]);
  int    interval = (int) (1000.0 / fps);

  //------------------------------------------------------------
  // Establish Connection

  igtl::UDPClientSocket::Pointer socket;
  socket = igtl::UDPClientSocket::New();
  socket->JoinNetwork("226.0.0.1", port, 1);
  //socket->JoinNetwork("127.0.0.1", port, 0); // join the local network for a client connection
  igtl::MessageRTPWrapper::Pointer rtpWrapper = igtl::MessageRTPWrapper::New();
  igtl::MessageBase::Pointer trackingMultiPKTMSG = igtl::MessageBase::New();
  const char *trackingDeviceName = "Tracker";
  const char *deviceType = "TDATA";
  trackingMultiPKTMSG->SetHeaderVersion(IGTL_HEADER_VERSION_2);
  //std::vector<ReorderBuffer> reorderBufferVec(10, ReorderBuffer();
  int loop = 0;
  unsigned char UDPPaket[RTP_PAYLOAD_LENGTH+RTP_HEADER_LENGTH];
  for (loop = 0; loop<100; loop++)
  {
    int totMsgLen = socket->ReadSocket(UDPPaket, RTP_PAYLOAD_LENGTH+RTP_HEADER_LENGTH);
    if (totMsgLen>0)
    {
      rtpWrapper->UnWrapMessageWithTypeAndName(UDPPaket, totMsgLen, trackingMultiPKTMSG, deviceType, trackingDeviceName);
      if (rtpWrapper->GetRTPWrapperStatus()==igtl::MessageRTPWrapper::MessageReady)
        ReceiveTrackingData(trackingMultiPKTMSG);
    }//igtl::Sleep(interval);
  }
}


int ReceiveTrackingData(igtl::MessageBase::Pointer& msgData)
{
  // Deserialize the transform data
  // If you want to skip CRC check, call Unpack() without argument.
  igtl::TrackingDataMessage::Pointer trackingMSG = igtl::TrackingDataMessage::New();
  //memcpy(trackingMSG->GetPackPointer(), msgData->GetPackPointer(), msgData->GetPackSize());
  trackingMSG->SetHeaderVersion(IGTL_HEADER_VERSION_2);
  trackingMSG->Copy(msgData);
  int c = trackingMSG->Unpack(0); // to do crc check fails, fix the error

  if (c & igtl::MessageHeader::UNPACK_BODY) // if CRC check is OK
    {
    int nElements = trackingMSG->GetNumberOfTrackingDataElements();
    for (int i = 0; i < nElements; i ++)
      {
      igtl::TrackingDataElement::Pointer trackingElement;
      trackingMSG->GetTrackingDataElement(i, trackingElement);

      igtl::Matrix4x4 matrix;
      trackingElement->GetMatrix(matrix);


      std::cerr << "========== Element #" << i << " ==========" << std::endl;
      std::cerr << " Name       : " << trackingElement->GetName() << std::endl;
      std::cerr << " Type       : " << (int) trackingElement->GetType() << std::endl;
      std::cerr << " Matrix : " << std::endl;
      igtl::PrintMatrix(matrix);
      std::cerr << "================================" << std::endl;
      }
    return 1;
    }
  return 0;
}


