
#pragma once
#ifndef    CLIENT_H
#define    CLIENT_H

//#define api //if used in GUI API, comment if used in your software or 3impact

#ifdef api
#include "../tools/mutex.h"
#endif

#ifndef api
#include <windows.h>
#include <strsafe.h>
#include <stdio.h>
#include <math.h>
#include <winsock.h>
#pragma comment(lib,"ws2_32.lib")

struct CPoint
{
int x;
int y;
};

struct Mutex 
{
	Mutex ();
	virtual ~Mutex ();

	virtual void acquire ();
	virtual int acquired ();
	virtual void release ();

private:
	void* mutex;
};
#endif

struct SensorData
	{
	int BatVoltage;
	int SpeedFrontLeft;
	int SpeedRearLeft;
	int SpeedFrontRight;
	int SpeedRearRight;
	int IRLeft;
	int	IRRight;
	int IRLeft2;
	int	IRRight2;
	};

class WifibotClient
{
public:
	WifibotClient(void);
	~WifibotClient(void);

	bool joyvirtual;
	bool joyusb;
	bool joywii;
	
	CPoint CalculConsigne(CPoint);
	CPoint CalculConstConsigne(CPoint);
	void GetSensorData(SensorData*);
	void SetControl(bool control);
	
	void SendConsigne(CPoint point);
	void SendConsigneUdp(CPoint point);
	void SendConsigneCRC(CPoint point);
	short Crc16(unsigned char *Adresse_tab, unsigned char Taille_max);
	bool ConnectToRobot(char* ip,int port);
	void DisconnectRobot();
	bool ConnectToRobotUdp(char* ip,int port);
	void DisconnectRobotUdp();

private:
	Mutex mutexRcv;
	Mutex mutexSend;

	bool ok,okOut;
	bool first;

	bool socketnotok;
	bool socketnotokudp;
	
	HANDLE Handle_Of_Thread_TCP;
	HANDLE Handle_Of_Thread_TCP_trooper_In;
	HANDLE Handle_Of_Thread_TCP_trooper_Out;

	static DWORD WINAPI Thread_TCP( LPVOID lpParam );
	static DWORD WINAPI Thread_TCP_Trooper_In( LPVOID lpParam );
	static DWORD WINAPI Thread_TCP_Trooper_Out( LPVOID lpParam );
			
	volatile bool Thread_TCP_Run;
	volatile bool Thread_TCP_Trooper_In_Run;
	volatile bool Thread_TCP_Trooper_Out_Run;

	void Thread_TCP(void);
	void Thread_TCP_Trooper_In(void);
	void Thread_TCP_Trooper_Out(void);

	DWORD  m_dwThreadID2;
	DWORD  m_dwThreadID4;
	DWORD  m_dwThreadID5;
	HANDLE m_hThread2;
	HANDLE m_hThread4;
	HANDLE m_hThread5;	

	int minmax,moyx,moyy,smg,smd,vmd,vmg,comg,comd,stop;
	int ctrlg,ctrld;
	char sendbuf[2];
	unsigned char sendBuffer[9];
    char rcvbuf[7],rcvbuftemp[7];	
	int udp;
	char myip[30];
	int myport;
	char myipsend[30];
	int myportsend;

	int pointx,pointy;

	char buffso_rcvIN[100]; 
	char buffso_rcvOUT[100]; 
	char buffso_sendIN[100];
	char buffso_sendOUT[100];

	char szServerAddress[30];
	
	WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in sin;
    int dataLen;
    int sinsize;

	WSADATA wsaOut;
    SOCKET sockOut;
    struct sockaddr_in sinOut;
    int dataLenOut;
    int sinsizeOut;

	WSADATA wsatcp;
    SOCKET socktcp;
    struct sockaddr_in sintcp;
    int dataLentcp;
    int sinsizetcp;
	LPHOSTENT	lphost;
};
#endif
