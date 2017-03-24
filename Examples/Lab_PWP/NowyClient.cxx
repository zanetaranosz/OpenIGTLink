/*=========================================================================

  Program:   OpenIGTLink -- Example for Tracker Client Program
  Language:  C++

  Copyright (c) Insight Software Consortium. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include <iostream>
#include <math.h>
#include <cstdlib>
#include <cstring>
#include <iomanip>

#include "igtlOSUtil.h"
#include "igtlPointMessage.h"
#include "igtlClientSocket.h"
#include "igtlServerSocket.h"
#if OpenIGTLink_PROTOCOL_VERSION >= 2
#include "igtlPointMessage.h"
#include "igtlTrajectoryMessage.h"
#include "igtlStringMessage.h"
#include "igtlBindMessage.h"
#include "igtlCapabilityMessage.h"
#endif //OpenIGTLink_PROTOCOL_VERSION >= 2

#if OpenIGTLink_PROTOCOL_VERSION >= 2
int ReceivePoint(igtl::Socket * socket, igtl::MessageHeader * header);
#endif //OpenIGTLink_PROTOCOL_VERSION >= 2

int main(int argc, char* argv[])
{
  //------------------------------------------------------------
  // Parse Arguments

  if (argc != 3) // check number of arguments
    {
    // If not correct, print usage
    std::cerr << "Usage: " << argv[0] << " <hostname> <port> <fps>"    << std::endl;
    std::cerr << "    <hostname> : IP or host name"                    << std::endl;
    std::cerr << "    <port>     : Port # (18944 in Slicer default)"   << std::endl;
    exit(0);
    }

  char*  hostname = "localhost";
  int    port     = 10113;

  //------------------------------------------------------------
  // Establish Connection

  igtl::ClientSocket::Pointer socket;
  socket = igtl::ClientSocket::New();
  int r = socket->ConnectToServer(hostname, port);

  if (r != 0)
    {
    std::cerr << "Cannot connect to the server." << std::endl;
    exit(0);
    }

  //------------------------------------------------------------
  // Allocate Transform Message Class

  igtl::PointMessage::Pointer pointMsg;
  pointMsg = igtl::PointMessage::New();
  pointMsg->SetDeviceName("PointSender");

  //---------------------------
  // Create 1st point
  igtl::PointElement::Pointer point0;
  point0 = igtl::PointElement::New();
  point0->SetName("POINT_0");
  point0->SetGroupName("GROUP_0");
  point0->SetRGBA(0xFF, 0x00, 0x00, 0xFF);
  point0->SetPosition(10.0, 20.0, 30.0);
  point0->SetRadius(15.0);
  point0->SetOwner("IMAGE_0");
  
  //---------------------------
  // Create 2nd point
  igtl::PointElement::Pointer point1;
  point1 = igtl::PointElement::New();
  point1->SetName("POINT_1");
  point1->SetGroupName("GROUP_0");
  point1->SetRGBA(0x00, 0xFF, 0x00, 0xFF);
  point1->SetPosition(40.0, 50.0, 60.0);
  point1->SetRadius(45.0);
  point1->SetOwner("IMAGE_0");
  
  //---------------------------
  // Create 3rd point
  igtl::PointElement::Pointer point2;
  point2 = igtl::PointElement::New();
  point2->SetName("POINT_2");
  point2->SetGroupName("GROUP_0");
  point2->SetRGBA(0x00, 0x00, 0xFF, 0xFF);
  point2->SetPosition(70.0, 80.0, 90.0);
  point2->SetRadius(75.0);
  point2->SetOwner("IMAGE_0");
  
  //---------------------------
  // Pack into the point message
  pointMsg->AddPointElement(point0);
  pointMsg->AddPointElement(point1);
  pointMsg->AddPointElement(point2);
  pointMsg->Pack();
  
  //------------------------------------------------------------
  // Send
  socket->Send(pointMsg->GetPackPointer(), pointMsg->GetPackSize());
  

  igtl::ServerSocket::Pointer serverSocket;
  serverSocket = igtl::ServerSocket::New();
  int r1 = serverSocket->CreateServer(port);

  if (r1 < 0)
  {
	  std::cerr << "Cannot create a server socket." << std::endl;
	  exit(0);
  }

  igtl::Socket::Pointer socketOdb;

  while (1)
  {
	  //------------------------------------------------------------
	  // Waiting for Connection
	  
	  socketOdb = serverSocket->WaitForConnection(1000);

	  if (socket.IsNotNull()) // if client connected
	  {
		  // Create a message buffer to receive header
		  igtl::MessageHeader::Pointer headerMsg;
		  headerMsg = igtl::MessageHeader::New();

		  //------------------------------------------------------------
		  // Allocate a time stamp 
		  igtl::TimeStamp::Pointer ts;
		  ts = igtl::TimeStamp::New();

		  //------------------------------------------------------------
		  // loop
		  for (int i = 0; i < 100; i++)
		  {

			  // Initialize receive buffer
			  headerMsg->InitPack();

			  // Receive generic header from the socket
			  int r = socketOdb->Receive(headerMsg->GetPackPointer(), headerMsg->GetPackSize());
			  if (r == 0)
			  {
				  socketOdb->CloseSocket();
			  }
			  if (r != headerMsg->GetPackSize())
			  {
				  continue;
			  }

			  // Deserialize the header
			  headerMsg->Unpack();

			  // Get time stamp
			  igtlUint32 sec;
			  igtlUint32 nanosec;

			  headerMsg->GetTimeStamp(ts);
			  ts->GetTimeStamp(&sec, &nanosec);

			  std::cerr << "Time stamp: "
				  << sec << "." << std::setw(9) << std::setfill('0')
				  << nanosec << std::endl;

			  // Check data type and receive data body
			  
#if OpenIGTLink_PROTOCOL_VERSION >= 2
			  if (strcmp(headerMsg->GetDeviceType(), "POINT") == 0)
			  {
				  ReceivePoint(socket, headerMsg);
			  }
			
#endif //OpenIGTLink_PROTOCOL_VERSION >= 2
			  else
			  {
				  // if the data type is unknown, skip reading.
				  std::cerr << "Receiving : " << headerMsg->GetDeviceType() << std::endl;
				  std::cerr << "Size : " << headerMsg->GetBodySizeToRead() << std::endl;
				  socket->Skip(headerMsg->GetBodySizeToRead(), 0);
			  }
		  }
	  }
  }




  //------------------------------------------------------------
  // Close the socket
  socket->CloseSocket();

}


#if OpenIGTLink_PROTOCOL_VERSION >= 2
int ReceivePoint(igtl::Socket * socket, igtl::MessageHeader * header)
{

	std::cerr << "Receiving POINT data type." << std::endl;

	// Create a message buffer to receive transform data
	igtl::PointMessage::Pointer pointMsg;
	pointMsg = igtl::PointMessage::New();
	pointMsg->SetMessageHeader(header);
	pointMsg->AllocatePack();

	// Receive transform data from the socket
	socket->Receive(pointMsg->GetPackBodyPointer(), pointMsg->GetPackBodySize());

	// Deserialize the transform data
	// If you want to skip CRC check, call Unpack() without argument.
	int c = pointMsg->Unpack(1);

	if (c & igtl::MessageHeader::UNPACK_BODY) // if CRC check is OK
	{
		int nElements = pointMsg->GetNumberOfPointElement();
		for (int i = 0; i < nElements; i++)
		{
			igtl::PointElement::Pointer pointElement;
			pointMsg->GetPointElement(i, pointElement);

			igtlUint8 rgba[4];
			pointElement->GetRGBA(rgba);

			igtlFloat32 pos[3];
			pointElement->GetPosition(pos);

			std::cerr << "========== Element #" << i << " ==========" << std::endl;
			 //std::cerr << " Name      : " << pointElement->GetName() << std::endl;
			//std::cerr << " GroupName : " << pointElement->GetGroupName() << std::endl;
			//std::cerr << " RGBA      : ( " << (int)rgba[0] << ", " << (int)rgba[1] << ", " << (int)rgba[2] << ", " << (int)rgba[3] << " )" << std::endl;
			std::cerr << " Position  : ( " << std::fixed << pos[0] << ", " << pos[1] << ", " << pos[2] << " )" << std::endl;
			//std::cerr << " Radius    : " << std::fixed << pointElement->GetRadius() << std::endl;
			//std::cerr << " Owner     : " << pointElement->GetOwner() << std::endl;
			std::cerr << "================================" << std::endl;
		}
	}

	return 1;
}


#endif //OpenIGTLink_PROTOCOL_VERSION >= 2