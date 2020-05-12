#include "Bluetooth.h"
Bluetooth::Bluetooth(int sendbuf, int recbuf)
{
    recvbuff = new char[recbuf];
    sendbuff = new char[sendbuf];
}
void Bluetooth::init()
{

    WSADATA wsaData;
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        wprintf(L"WSAStartup function failed with error: %d\n", iResult);
        
    }
    // Ops�tning af socket
    
       s = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM); 
    if (s == INVALID_SOCKET) {
        wprintf(L"socket function failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
       
    }
    //Ops�tning af bth socket adresse
    _SOCKADDR_BTH sbth;
    //memset(&sbth, 0, sizeof(SOCKADDR_BTH));
    sbth.addressFamily = AF_BTH;
    sbth.serviceClassId = RFCOMM_PROTOCOL_UUID;
    sbth.btAddr = BTH_ADDR(0x00066619FD59);
    sbth.port = 0;

    // Tilslutning til bluetooth module
    iResult = connect(s, (sockaddr*)&sbth, sizeof(sbth));
    if (iResult == SOCKET_ERROR) {
        wprintf(L"connect function failed with error: %ld\n", WSAGetLastError());
        iResult = closesocket(s);
        if (iResult == SOCKET_ERROR)
            wprintf(L"closesocket function failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        
    }
}
void Bluetooth::receive() {
    
    do {

        iResult = recv(s, recvbuff, sizeof(recvbuff), 0);
        if (iResult > 0) {
            printf("Bytes received: %d\n", iResult);
            for (int i = 0; i < iResult; i++) {
                cout << recvbuff[i];
            }
            cout << endl;
        }
        else if (iResult == 0)
            printf("Connection closed\n");
        else
            printf("recv failed: %d\n", WSAGetLastError());

    } while (iResult > 0);
    // Hvis error opst�r output error code, og cleanup wsa
    iResult = closesocket(s);
    if (iResult == SOCKET_ERROR) {
        wprintf(L"closesocket function failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
     
    }
}
