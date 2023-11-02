#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

int main() 
{
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

	SOCKET server_socket = INVALID_SOCKET;
	server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

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

	closesocket(server_socket);
	WSACleanup();

	return 0;
}