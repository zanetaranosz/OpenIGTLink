/*=========================================================================

  Program:   The OpenIGTLink Library
  Language:  C++
  Web page:  http://openigtlink.org/

  Copyright (c) Insight Software Consortium. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkClientSocket.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "igtlUDPClientSocket.h"
#include <string.h>

namespace igtl
{

//-----------------------------------------------------------------------------
UDPClientSocket::UDPClientSocket()
{
}

//-----------------------------------------------------------------------------
UDPClientSocket::~UDPClientSocket()
{
}
  
int UDPClientSocket::JoinNetwork(const char* groupIPAddr, int portNum, bool joinGroup)
{
  this->m_SocketDescriptor = this->CreateUDPSocket();
  this->SetIPAddress(groupIPAddr);
  this->SetPortNumber(portNum);
  if(BindSocket(this->m_SocketDescriptor, portNum)==0);
  {
  /*With UDP, you have to bind() the socket in the client because UDP is connectionless, so there is no other way for the stack to know which program to deliver datagrams to for a particular port.
  
  If you could recvfrom() without bind(), you'd essentially be asking the stack to give your program all UDP datagrams sent to that computer. Since the stack delivers datagrams to only one program, this would break DNS, Windows' Network Neighborhood, network time sync....*/
    if (joinGroup)
    {
      struct ip_mreq imreq;
      imreq.imr_multiaddr.s_addr = inet_addr(groupIPAddr);
      imreq.imr_interface.s_addr = INADDR_ANY; // use DEFAULT interface
      // JOIN multicast group on default interface
      if(setsockopt(this->m_SocketDescriptor, IPPROTO_IP, IP_ADD_MEMBERSHIP,
                          (const char *)&imreq, sizeof(struct ip_mreq))==0) // windows use (const char*), unix like system use (const void*)
      {
        return this->m_SocketDescriptor;
      }
    }
  }
  
  return -1;
}

//-----------------------------------------------------------------------------
int UDPClientSocket::ReadSocket(unsigned char* buffer, unsigned bufferSize) {
  if (!this->m_SocketDescriptor)
  {
    igtlErrorMacro("Failed to create socket.");
    return -1;
  }
  int bytesRead = ReceiveUDP(buffer, bufferSize);
  return bytesRead;
}
//-----------------------------------------------------------------------------
void UDPClientSocket::PrintSelf(std::ostream& os) const
{
  this->Superclass::PrintSelf(os);
}

} // end of igtl namespace

