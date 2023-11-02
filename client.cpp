#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <tchar.h>

int main() 
{
	// INITIALIZE WSAStartup

	WSADATA wsa_data;
	int wsa_err;

	// MAKEWORD creates a certain format which is 2.2 for starting our windows socket
	WORD m_version_requested = MAKEWORD(2,2);
	// wsa_err is for checking if our dll is found or not
	wsa_err = WSAStartup(m_version_requested, &wsa_data);

	if(wsa_err != 0)
	{
		std::cout << "The Winsock dll not found!" << std::endl;
		return 0;		
	}
	else 
	{
		std::cout << "The Winsock dll found" << std::endl;
		std::cout << "The status: " << wsa_data.szSystemStatus << std::endl;
	}

// CREAT SOCKET

	SOCKET client_socket = INVALID_SOCKET;
	int port = 5555;

	// This code is for tcp so we select sock_stream for tcp and if udp we pass SOCK_DGRAM
	// af_inet means a family that contains udp and tcp 
	// The protocol for TCP is IPPROTO_TCP
	// returns 0 if successful
	client_socket = socket(AF_INET,
	 						SOCK_STREAM,
	 						IPPROTO_TCP);

	if(client_socket == INVALID_SOCKET)
	{
		std::cout << "ERROR at socket(): " << WSAGetLastError() << std::endl;
		WSACleanup();
		return 0;
	}
	else
	{
		std::cout << "socket() is OK!" << std::endl;
	}

	sockaddr_in service;
	service.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
	service.sin_port = htons(port);

	if(connect(client_socket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
	{
		std::cout << "Client: connect() Failed to connect" << std::endl;
		WSACleanup();
		return 0;


	}
	else 
	{
		std::cout << "Client connect is OK" << std::endl;

	}

	WSACleanup();
	return 0;
}
