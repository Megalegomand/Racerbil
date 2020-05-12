#pragma once
#include <iostream>
#include <WinSock2.h>
#include <winsock.h>
#include <windows.h>
#include <ws2bth.h>
#include<vector>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

class Bluetooth
{
public:
	Bluetooth(int sendbuff, int recvbuff);
	void init();
	void receive();
	void send();
	~Bluetooth();


private:
	char* recvbuff;
	char* sendbuff;
	SOCKET s;
	int iResult;
	
};

