// BluetoothTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
<<<<<<< Updated upstream
#include <WinSock2.h>
#include <winsock.h>
#include <windows.h>
#include <ws2bth.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;
=======
#include <pch.h>
#include <windows.h>
#include <CSerial>
#include <winsock32>
#include "stdafx.h"
>>>>>>> Stashed changes

int main(int argc, _TCHAR* argv[])
{
<<<<<<< Updated upstream:CppTest/BluetoothTest/BluetoothTest/BluetoothTest.cpp
    //Opsætning af wsaData
=======
<<<<<<< Updated upstream
>>>>>>> Stashed changes:C++/BluetoothTest/BluetoothTest/BluetoothTest.cpp
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        wprintf(L"WSAStartup function failed with error: %d\n", iResult);
        return 1;
    }
    // Opsætning af socket
    SOCKET s;
    s = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
    if (s == INVALID_SOCKET) {
        wprintf(L"socket function failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    //Opsætning af bth socket adresse
    _SOCKADDR_BTH sbth;
    //memset(&sbth, 0, sizeof(SOCKADDR_BTH));
    sbth.addressFamily = AF_BTH;
    sbth.serviceClassId = RFCOMM_PROTOCOL_UUID;
    sbth.btAddr = BTH_ADDR(0x00066619FD59);
    sbth.port = 0;
<<<<<<< Updated upstream:CppTest/BluetoothTest/BluetoothTest/BluetoothTest.cpp
    // Tilslutning til bluetooth module
=======
=======
	LPCWSTR port = L"COM3";

	HANDLE hcomm = ::CreateFile(port, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);

// Check if port has been opened succesfully
if (hComm == INVALID_HANDLE_VALUE) std::cout << "Failed to open " << port << " error: " << GetLastError() << std::endl;
else std::cout << port << " has been opened succesfully\n";

// Create DCB structure 
DCB dcb = { 0 };

// Get Comm state
if (!::GetCommState(hComm, &dcb)) std::cout << "Failed to get Comm state, error: " << GetLastError() << std::endl;

// Configure strcutre
dcb.DCBlength = sizeof(DCB);

// Set Baud rate
dcb.BaudRate = CBR_9600;
// Set number of bytes in bits that are recieved through the port
dcb.ByteSize = 8;
dcb.StopBits = ONESTOPBIT;

// Check if port has been configured correctly
if (!::SetCommState(hComm, &dcb)) std::cout << "\nFailed to set Comm State, error: " << GetLastError();
else std::cout << "Comm state has been set succesfully\n";

///-----------------------------Read data-------------------------------------------------------------------

char buffer;
DWORD maxBytes = 1;
if (!::ReadFile(hComm, &buffer, maxBytes, NULL, NULL)) std::cout << "\nFailed to read from " << port << " error: " << GetLastError() << std::endl;
else std::cout << "File has been read succesfully\n";
	/*CSerial serial;
	if (serial.Open(2, 9600))
	{
		static char* szMessage[] = "This is test data";
		int nBytesSent = serial.SendData(szMessage, strlen(szMessage));
		ASSERT(nBytesSent == strlen(szMessage));
	}
	else
		AfxMessageBox("Failed to open port!");

	char buffer;
	DWORD maxBytes = 1;
	if (ReadFile(hComm, &buffer, maxBytes, NULL, NULL)) std::cout << "\nFailed to read from " << port << " error: " << GetLastError() << std::endl;
	else std::cout << "File has been read succesfully\n";*/


}
>>>>>>> Stashed changes

>>>>>>> Stashed changes:C++/BluetoothTest/BluetoothTest/BluetoothTest.cpp
    iResult = connect(s, (sockaddr*)&sbth, sizeof(sbth));
    if (iResult == SOCKET_ERROR) {
        wprintf(L"connect function failed with error: %ld\n", WSAGetLastError());
        iResult = closesocket(s);
        if (iResult == SOCKET_ERROR)
            wprintf(L"closesocket function failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    //Modtagelse af data 
    char recvbuf[200];
    char sendbuf[1];
    do {

        iResult = recv(s, recvbuf, sizeof(recvbuf), 0);
        if (iResult > 0) {
            printf("Bytes received: %d\n", iResult);
            for (int i = 0; i < iResult; i++) {
                cout << recvbuf[i];
            }
            cout << endl;
        }
        else if (iResult == 0)
            printf("Connection closed\n");
        else
            printf("recv failed: %d\n", WSAGetLastError());

    } while (iResult > 0);
    // Hvis error opstår output error code, og cleanup wsa
    iResult = closesocket(s);
    if (iResult == SOCKET_ERROR) {
        wprintf(L"closesocket function failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    // hvis ingen fejl output recvbuf, send modtagelse og kør cleanup
    iResult = send(s, sendbuf, sizeof(sendbuf), 0);
    WSACleanup();
    return 0;
}
