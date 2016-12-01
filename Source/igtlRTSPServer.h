/*=========================================================================

  Program:   The OpenIGTLink Library
  Language:  C++
  Web page:  http://openigtlink.org/

  Copyright (c) Insight Software Consortium. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef __igtlRTSPServer_h
#define __igtlRTSPServer_h

#include <string>

#include "igtlObject.h"
#include "igtlMacro.h"
#include "igtlMath.h"
#include "igtlMessageBase.h"
#include "igtlConditionVariable.h"
#include "igtlMutexLock.h"
#include "igtlServerSocket.h"
#include "igtl_header.h"
#include "igtl_util.h"

#if defined(WIN32) || defined(_WIN32)
#include <windows.h>
#else
#include <sys/time.h>
#endif

namespace igtl
{
  
class IGTLCommon_EXPORT RTSPServer: public Object
{
public:
  typedef RTSPServer              Self;
  typedef Object               Superclass;
  typedef SmartPointer<Self>        Pointer;
  typedef SmartPointer<const Self>  ConstPointer;

  igtlTypeMacro(igtl::RTSPServer, Object)
  igtlNewMacro(igtl::RTSPServer);
  
  RTSPServer();
  ~RTSPServer();
  
  /**
   Start the server, this function will be holding the main program for a client connection.
   */
  int StartServer();
  
  /**
   Parse the configuration file to initialize the encoder and server.
   */
  bool InitializeEncoderAndServer();
  
  /**
   Set the input frame pointer , the encoder will read the frame from the pointer
   */
  void SetInputFramePointer(uint8_t* picPointer);
  
  /**
   Encode a frame, for performance issue, before encode the frame, make sure the frame pointer is updated with a new frame.
   Otherwize, the old frame will be encoded.
   */
  int EncodeSingleFrame();
  
  /**
   Pack the encoded frame into a OpenIGTLink message and send the message to a client.
   */
  void SendIGTLinkMessage();
  
  /**
   Set the server to wait for STT command or just send the bitstream when connection is setup.
   */
  void SetWaitSTTCommand(bool needSTTCommand){ waitSTTCommand = needSTTCommand;};
  
  /**
   Get the encoder and server initialization status.
   */
  bool GetInitializationStatus(){return InitializationDone;};
  
  /**
   Get Server connection status, true for connected, false for not connected
   */
  bool GetServerConnectStatus(){return serverConnected;}
  
  /**
   Encode the video stream from a source file
   */
  void* EncodeFile(void);
  
  /**
   Get the type of encoded frame
   */
  int GetVideoFrameType(){return videoFrameType;};
  
  int ParseConfigForServer();
  
  //void* ThreadFunctionServer(void*);
  
  static bool CompareHash (const unsigned char* digest, const char* hashStr);
  
  igtl::SimpleMutexLock* glock;
  
  igtl::Socket::Pointer socket;
  
  igtl::ServerSocket::Pointer serverSocket;
  
  igtl::ConditionVariable::Pointer conditionVar;
  
  int videoFrameType;
  
  int   interval;
  
  bool  useCompress;

  int   serverConnected;
  
  int   serverPortNumber;
  
  int argc;
  
  std::string augments;
  
  bool waitSTTCommand;
  
  std::string deviceName;
  
  bool InitializationDone;
  
};


} // namespace igtl

#endif // _igtlRTSPServer_h