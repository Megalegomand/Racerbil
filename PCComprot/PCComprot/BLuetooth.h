#pragma once
#include <iostream>
#include <WinSock2.h>
#include <winsock.h>
#include <windows.h>
#include <ws2bth.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

class Bluetooth
{
public:
	Bluetooth(char sendbuff, char recvbuff);
	void init();
	


private:
	char recvbuff;
	char sendbuff;
	SOCKET s;
	int iResult;

};

