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
  Module:    $RCSfile: vtkServerSocket.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "igtlUDPServerSocket.h"

namespace igtl
{

//-----------------------------------------------------------------------------
UDPServerSocket::UDPServerSocket()
{
}

//-----------------------------------------------------------------------------
UDPServerSocket::~UDPServerSocket()
{
}

bool UDPServerSocket::IsMulticastAddreesValid(const char* add)
{
  //224.0.0.0 through 224.0.0.255, are not routable
  igtl_uint32 address;
  inet_pton(AF_INET, add, &(address));// to do: make sure the endian is correct
  if(igtl_is_little_endian())
  {
    address = BYTE_SWAP_INT32(address);
  }
  return address >  0xE00000FF &&
  address <= 0xEFFFFFFF;
}
  
int UDPServerSocket::AddGroup(const char* add, igtl_uint16 port, unsigned int groupID)
{
  if (IsMulticastAddreesValid(add))
  {
    for(int i = 0; i < this->groups.size(); i++)
    {
      if (this->groups[i].groupID == groupID &&
          (strcmp((const char *)this->groups[i].address ,add)==0)
          && this->groups[i].portNum ==  port )
      {
        
        return -1;
      }
    }
    this->groups.push_back(GroupDest(add, port, groupID));
  }
  return 0;
}
  
int UDPServerSocket::WriteSocket(unsigned char* buffer, unsigned bufferSize)
{
  int successul = 0;
  for(int i = 0; i < this->groups.size(); i++)
  {
#if defined(OpenIGTLink_HAVE_GETSOCKNAME_WITH_SOCKLEN_T)
    socklen_t addressLength = sizeof(this->groups[i].address);
#else
    int addressLength = sizeof(this->groups[i].address);
#endif
    this->SetIPAddress((const char*)this->groups[i].address);
    this->SetPortNumber(this->groups[i].portNum);
    successul = SendUDP((char*)buffer, bufferSize);
    if (!successul) {
      successul = -1;
      continue; //to do: how to handle the unsuccessful transmission?
    }
  }
  return successul;
}
  
int UDPServerSocket::CreateUDPServer(int port)
{
  if (this->m_SocketDescriptor != -1)
  {
    igtlWarningMacro("Server Socket already exists. Closing old socket.");
    this->CloseSocket(this->m_SocketDescriptor);
    this->m_SocketDescriptor = -1;
  }
  this->m_SocketDescriptor = this->CreateUDPSocket();
  if (this->m_SocketDescriptor < 0)
  {
    return -1;
  }
  const igtl_uint8 loop = 0; //disable loop back to the host
  if (setsockopt(this->m_SocketDescriptor, IPPROTO_IP, IP_MULTICAST_LOOP,
                 (const char*)&loop, sizeof loop) < 0) {
    CloseSocket(this->m_SocketDescriptor);
    return -1;
  }
  
  struct in_addr addr;
  addr.s_addr = INADDR_ANY; // the address could be others
  
  if (setsockopt(this->m_SocketDescriptor, IPPROTO_IP, IP_MULTICAST_IF, &addr, sizeof addr) < 0) {
    CloseSocket(this->m_SocketDescriptor);
    return -1;
  }
  
  //If not otherwise specified, multicast datagrams are sent with a default value of 1, to prevent them to be forwarded beyond the local network. To change the TTL to the value you desire (from 0 to 255), put that value into a variable (here I name it "ttl") and write somewhere in your program:
  
  unsigned char ttl = 1;
  if(setsockopt(this->m_SocketDescriptor, IPPROTO_IP, IP_MULTICAST_TTL, &ttl, sizeof(ttl))<0)
  {
    CloseSocket(this->m_SocketDescriptor);
    return -1;
  }
  /*if ( this->BindSocket(this->m_SocketDescriptor, port) != 0)
  {
    // failed to bind or listen.
    this->CloseSocket(this->m_SocketDescriptor);
    this->m_SocketDescriptor = -1;
    return -1;
  }*/ // Bind socket in the server would conflict the binding in the client.
  // Success.
  return 0;
}
  
int UDPServerSocket::DeleteClient(unsigned int groupID)
{
  for(int i = 0; this->groups.size(); i++)
  {
    if (this->groups[i].groupID == groupID)
    {
      this->groups.erase(this->groups.begin()+i);
      return 0;
    }
  }
  return -1;
}

//-----------------------------------------------------------------------------
void UDPServerSocket::PrintSelf(std::ostream& os) const
{
  this->Superclass::PrintSelf(os);
}


} // end of igtl namespace
