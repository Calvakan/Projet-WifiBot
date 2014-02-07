#include "StdAfx.h"
#include "wifibotClient.h"

WifibotClient::WifibotClient(void)
{
	socketnotok=true;
	socketnotokudp=true;
	moyx=0;moyy=0;
	vmd=0;vmg=0;
	comg=0;comd=0;stop=0;
	ctrlg=0;ctrld=0;
	joyvirtual=false;
	joyusb=false;
	joywii=false;
	udp=false;
	//myip="";
	myport=0;
	ok=false;
	okOut=false;
	first=false;
	Thread_TCP_Run=false;
	Thread_TCP_Trooper_In_Run=false;
	Thread_TCP_Trooper_Out_Run=false;
}

WifibotClient::~WifibotClient(void)
{
}

void WifibotClient::SetControl(bool control)
{	
	if (control) ctrlg=128;
	else ctrlg=0;
	if (control) ctrld=128;
	else ctrld=0;
}

bool WifibotClient::ConnectToRobot(char* ip,int port)
{
	if(socketnotok)
	{
		char szServerAddress[30];
		sprintf(szServerAddress,"%s",ip);
		int iPort=port;
		
		WSAStartup(MAKEWORD(2,2),&wsatcp);

		memset(&sintcp,0,sizeof(sockaddr_in));
		sintcp.sin_family = AF_INET;
		sintcp.sin_addr.s_addr = inet_addr (szServerAddress);

		if (sintcp.sin_addr.s_addr == INADDR_NONE)
		{
		lphost = gethostbyname(szServerAddress);
		if (lphost != NULL)
		sintcp.sin_addr.s_addr = ((LPIN_ADDR)lphost->h_addr)->s_addr;
		else
		{
		WSASetLastError(WSAEINVAL);
		}
		}
		sintcp.sin_port = htons(iPort);
		// Open the socket
		socktcp = socket(AF_INET, SOCK_STREAM, 0);
		int err = connect(socktcp, (struct sockaddr*)&sintcp,sizeof(sockaddr));
		if(err == SOCKET_ERROR)
		{ 
		if(socktcp != INVALID_SOCKET)
		{
		closesocket(socktcp);
		socktcp = INVALID_SOCKET;
		}
		}
		else 
		{
		  m_hThread2=CreateThread(0,0,Thread_TCP,this,0,&m_dwThreadID2);
		  Thread_TCP_Run=true;
		  udp=false;
		  socketnotok=0;
		}
		return 0;
	}
	else return 1;
}

void WifibotClient::DisconnectRobot()
{
	if (!socketnotok) 
	{
		closesocket(socktcp);
		Thread_TCP_Run=false;
		TerminateThread(m_hThread2,0);
		socketnotok=true;
	}
}

bool WifibotClient::ConnectToRobotUdp(char* ip,int port)
{		
	if(socketnotokudp)
	{
		char szServerAddress[30];
		sprintf(myipsend,"%s",ip);
		
		myportsend=port;
			
		m_hThread4=CreateThread(0,0,Thread_TCP_Trooper_In,this,0,&m_dwThreadID4);
		Thread_TCP_Trooper_In_Run=true;
		m_hThread5=CreateThread(0,0,Thread_TCP_Trooper_Out,this,0,&m_dwThreadID5);	
		Thread_TCP_Trooper_Out_Run=true;
		udp=true;		
		socketnotokudp=false;
	   return 0;
	}
	else return 1;
}

void WifibotClient::DisconnectRobotUdp()
{
	if(!socketnotokudp)
	{
		Thread_TCP_Trooper_In_Run=false;
		Thread_TCP_Trooper_Out_Run=false;
		udp=false;
		ok=false;
		okOut=false;
		closesocket(sock);
		closesocket(sockOut);	
		TerminateThread(m_hThread4,0);
		TerminateThread(m_hThread5,0);
		socketnotokudp=true;
	}	
}

void WifibotClient::SendConsigne(CPoint point)
{
	sendbuf[0]=(char)(point.x);
    sendbuf[1]=(char)(point.y);
	if (!socketnotok) send(socktcp,sendbuf,2,0);
}

void WifibotClient::SendConsigneUdp(CPoint point)
{	
	mutexSend.acquire();
	pointx=point.x;
	pointy=point.y;
	mutexSend.release();
if(ok)
{
	if (sendto(sock,buffso_sendOUT,20,0,(SOCKADDR*)&sin,sizeof(sin))==20) ok=true;
		else {
			ok=false;
		printf("ok send false\n");
		}
}
}

void WifibotClient::GetSensorData(SensorData *RobotSensors)
{
	mutexRcv.acquire();
	if(!udp)
	{
		RobotSensors->BatVoltage=(int)rcvbuftemp[0];
		RobotSensors->SpeedFrontLeft=(int)rcvbuftemp[1];
		RobotSensors->SpeedRearLeft=(int)rcvbuftemp[2];
		RobotSensors->SpeedFrontRight=(int)rcvbuftemp[3];
		RobotSensors->SpeedRearRight=(int)rcvbuftemp[4];
		RobotSensors->IRLeft=(int)rcvbuftemp[5];
		RobotSensors->IRRight=(int)rcvbuftemp[6];
	}
	else
	{
		RobotSensors->BatVoltage=(int)buffso_rcvOUT[93];
		RobotSensors->SpeedFrontLeft=(int)buffso_rcvOUT[94];
		RobotSensors->SpeedRearLeft=(int)buffso_rcvOUT[95];
		RobotSensors->SpeedFrontRight=(int)buffso_rcvOUT[96];
		RobotSensors->SpeedRearRight=(int)buffso_rcvOUT[97];
		RobotSensors->IRLeft=(int)buffso_rcvOUT[98];
		RobotSensors->IRRight=(int)buffso_rcvOUT[99];		
	}
	mutexRcv.release();
}

CPoint WifibotClient::CalculConsigne(CPoint joypoint)
{
	CPoint calcpoint;

    ////debut filtrage	
	moyx=joypoint.x;
	moyy=-joypoint.y;
		
	if(moyy>=0)
	{
	vmg=(abs(moyx+moyy));
	vmd=(abs(moyx-moyy));
	}
	else if (moyy<0)
	{
	vmg=(abs(moyx-moyy));
	vmd=(abs(moyx+moyy));
	}

	if (ctrlg==128) minmax=40;//
	else minmax=60;
	
	if (moyy>0) 
	{	
		if (moyx>=0) 
		{
			if(vmg>minmax) vmg=minmax;
			if(moyx>moyy) vmd=0;
		}

		if (moyx<=0) // 
		{
			if(abs(moyx)>moyy) vmg=0;
			if(vmd>minmax) vmd=minmax;
		}
		if (ctrlg==128) if(vmg>minmax)vmg=minmax;
		if (ctrlg==128) if(vmd>minmax)vmd=minmax;
		comg=ctrlg+64+vmg;comd=ctrld+64+vmd;							   //Av
	}	
	else if (moyy<0) 
	{
	if (moyx>=0) 
	{
		if(vmg>minmax) vmg=minmax;
		if(moyx>abs(moyy)) vmd=0;		
	}

	if (moyx<=0)  //
	{
		if(vmd>minmax) vmd=minmax;
		if(moyx<moyy) vmg=0;		
	}
	if (ctrlg==128) if(vmg>minmax)vmg=minmax;
	if (ctrlg==128) if(vmd>minmax)vmd=minmax;
	comg=ctrlg+vmg;comd=ctrld+vmd; 							//Ar
	}
	
	else 
	{
	if ((moyy==0)&&(moyx<0)) {comg=ctrlg+vmg;comd=ctrld+64+vmd;} 			//Gpivot
	if ((moyy==0)&&(moyx>0)) {comg=ctrlg+64+vmg;comd=ctrld+vmd;}			//Dpivot
	if ((moyx==0)&&(moyy==0)) {stop=1;comg=0;comd=0;vmg=0;vmd=0;}
    //Fin filtrage
	}
	calcpoint.x=comg;
	calcpoint.y=comd;

	return calcpoint;
}

CPoint WifibotClient::CalculConstConsigne(CPoint point)
{
	CPoint calcpoint;

    ////debut filtrage	
	vmg=point.x;
	vmd=point.y;
		
	if (ctrlg==128) minmax=40;
	else minmax=60;
	
	if (vmg>0) 
	{
		comg=ctrlg+64+abs(vmg);							   //Av
	}
	if (vmd>0) 
	{
		comd=ctrld+64+abs(vmd);							   //Av
	}
	if (vmg<0) 
	{
		comg=ctrlg+abs(vmg);							//Ar
	}
	
	if (vmd<0) 
	{
		comd=ctrld+abs(vmd); 							//Ar
	}

	calcpoint.x=comg;
	calcpoint.y=comd;

	return calcpoint;
}

void WifibotClient::Thread_TCP(void) 
{
	while(Thread_TCP_Run)
	{		
		int rcvnbr = recv(socktcp,rcvbuf,7,0);

        if (rcvnbr==7)
		{
			mutexRcv.acquire();
			memcpy(rcvbuftemp,rcvbuf,7);
			mutexRcv.release();
		}		
	Sleep(1);
	}		
}

DWORD WINAPI WifibotClient::Thread_TCP(LPVOID p)
{
   WifibotClient *me = (WifibotClient *)p;
   me->Thread_TCP();
   return 0;
}

void WifibotClient::Thread_TCP_Trooper_In(void) 
{
	// Source address of echo
	SOCKADDR_IN fromAddr;   
	WSAStartup(MAKEWORD(2,2),&wsaOut);
	sockOut=socket(AF_INET,SOCK_DGRAM,0);//On initialise le socket avec SOCK_DGRAM pour dire qu'on est en UDP

	sinOut.sin_family=AF_INET;
    
	sinOut.sin_addr.s_addr=inet_addr(myipsend);
	int res2=bind(sockOut,(SOCKADDR*)&sinOut,sizeof(sinOut));
	sinOut.sin_port=htons(myportsend+10);
    //int res2=bind(sockOut,(SOCKADDR*)&sinOut,sizeof(sinOut));
	sinsizeOut=sizeof(sinOut);
	
while(Thread_TCP_Trooper_In_Run)
	{		
	// In-out address size for RecvFrom()
  int fromSize = sizeof(fromAddr); 

  while (!okOut)
  {
	if (sendto(sockOut,"init",20,0,(SOCKADDR*)&sinOut,sizeof(sinOut)) ==20)
	 {
		Sleep(300);
		 //sendto(sockOut,"init",20,0,(SOCKADDR*)&sinOut,sizeof(sinOut));
		memset(buffso_rcvOUT,0,3);
		//Sleep(1);
		//printf("befor ");
		int pp=recvfrom(sockOut,buffso_rcvOUT, 3,0,(SOCKADDR*)&sinOut, &sinsizeOut);
		//printf("after \n") ;
		if(!(strstr(buffso_rcvOUT,"ok")==NULL))
		 {
			 okOut=true;
			 printf("ok \n");
		 }
	 }
	//Sleep(10);
  }
	//else
	{
	memset(buffso_sendIN,0,20);
	sprintf(buffso_sendIN,"data");
	if (sendto(sockOut,buffso_sendIN,20,0,(SOCKADDR*)&sinOut,sizeof(sinOut))==20)
	{
	//	mutexRcv.acquire();
		Sleep(5);
		sendto(sockOut,buffso_sendIN,20,0,(SOCKADDR*)&sinOut,sizeof(sinOut));
		//printf("recv befor ");
		int pp=recvfrom(sockOut,buffso_rcvOUT, 100,0,(SOCKADDR*)&sinOut, &sinsizeOut);//
		//printf("recv after \n");
		//	mutexRcv.release();	
	}
	else {
		ok=false;
		printf("ok=false \n");
	
	}
	}
	}
}

DWORD WINAPI WifibotClient::Thread_TCP_Trooper_In(LPVOID p)
{
   WifibotClient *me = (WifibotClient *)p;
   me->Thread_TCP_Trooper_In();
   return 0;
}

void WifibotClient::Thread_TCP_Trooper_Out(void) 
{
	WSAStartup(MAKEWORD(2,2),&wsa);
	closesocket(sock);
	sock=socket(AF_INET,SOCK_DGRAM,0);//On initialise le socket avec SOCK_DGRAM pour dire qu'on est en UDP

	sin.sin_family=AF_INET;
	sin.sin_addr.s_addr=inet_addr(myipsend);
	int res= bind(sock,(SOCKADDR*)&sin,sizeof(sin));
	sin.sin_port=htons(myportsend);
	//int res= bind(sock,(SOCKADDR*)&sin,sizeof(sin));//bug to be tested on SBC
	sinsize=sizeof(sin);
	
while(Thread_TCP_Trooper_Out_Run)
	{	
	if (!ok)
	{
	//	first=true;
	while (!ok)
	{		
		Sleep(600);
		if (sendto(sock,"init",20,0,(SOCKADDR*)&sin,sizeof(sin)) ==20)
		{
			//sendto(sock,"init",20,0,(SOCKADDR*)&sin,sizeof(sin));
			memset(buffso_rcvIN,0,20);
			//Sleep(100);
			int pp=recvfrom(sock,buffso_rcvIN, 3,0,(SOCKADDR*)&sin, &sinsize);
			if(!(strstr(buffso_rcvIN,"ok")==NULL))
			{
			  ok=true;
			}
	 }
	}
	}
	//else
	{
		memset(buffso_sendOUT,0,20);
		mutexSend.acquire();
		sprintf(buffso_sendOUT,"speed %c %c",pointy,pointx);
		mutexSend.release();		
	}
	Sleep(1);
	}	
	
}

DWORD WINAPI WifibotClient::Thread_TCP_Trooper_Out(LPVOID p)
{
   WifibotClient *me = (WifibotClient *)p;
   me->Thread_TCP_Trooper_Out();
   return 0;
}

#ifndef api
Mutex::Mutex ()
{
	mutex = (void*)CreateMutex (0, false, 0);
}

Mutex::~Mutex ()
{
	CloseHandle (mutex);
}

void Mutex::acquire ()
{
	WaitForSingleObject (mutex, INFINITE);
}

int Mutex::acquired ()
{
	return (WaitForSingleObject (mutex, 0) != WAIT_TIMEOUT);
}

void Mutex::release ()
{
	ReleaseMutex (mutex);
}
#endif