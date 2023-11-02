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

	SOCKET server_socket = INVALID_SOCKET;
	int port = 5555;

	// This code is for tcp so we select sock_stream for tcp and if udp we pass SOCK_DGRAM
	// af_inet means a family that contains udp and tcp 
	// The protocol for TCP is IPPROTO_TCP
	// returns 0 if successful
	server_socket = socket(AF_INET,
	 						SOCK_STREAM,
	 						IPPROTO_TCP);

	if(server_socket == INVALID_SOCKET)
	{
		std::cout << "ERROR at socket(): " << WSAGetLastError() << std::endl;
		WSACleanup();
		return 0;
	}
	else
	{
		std::cout << "socket() is OK!" << std::endl;
	}

	// BIND SOCKET

	sockaddr_in service;
	service.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
	service.sin_port = htons(port);
	if(bind(server_socket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
	{
		std::cout << "bind() failed " << WSAGetLastError() << std::endl;
		closesocket(server_socket);
		WSACleanup();
		return 0;
	}
	else 
	{
		std::cout << "bind() is OK!" << std::endl;
	}

	// LISTEN 

	if(listen(server_socket, 2) == SOCKET_ERROR)
		std::cout << "listen() ERROR listening on socket: " << WSAGetLastError() << std::endl;
	else
		std::cout << "listen() is OK" << std::endl;

	SOCKET accept_socket = INVALID_SOCKET;
	accept_socket = accept(server_socket, nullptr, nullptr);
	if(accept_socket == INVALID_SOCKET)
	{
		std::cout << "accept failed" << WSAGetLastError() << std::endl;
		return -1;	
	}

	std::cout << "accepted connection" << std::endl;

	closesocket(server_socket);
	WSACleanup();

	return 0;
}