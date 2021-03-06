#pragma comment(lib,"ws2_32.lib") //Winsock Library

/*
Simple udp client
*/
#include<WinSock2.h>
#include<iostream>
#include<Ws2tcpip.h>
#ifdef linux
#include  <arpa/inet.h>
#endif

#define SERVER "127.0.0.1"  //ip address of udp server
#define LOCAL "127.0.0.1"  //ip address of local client
#define BUFLEN 512  //Max length of buffer
#define PORT 8051   //The port on which to listen for incoming data

using namespace std;

int main() {

	// init
	WSAData wsaData; // The WinSocket object
	WORD DllVersion; // DDL version  for WSAData
	SOCKADDR_IN destination_addr; // Address to be binded to our connection socket
	SOCKADDR_IN local_addr; // Address to be binded to our connection socket
	SOCKET thisSocket;  // Server's socket
	string buffer; // Received message
	int bufferlength; // Received message length

	// Setup WinSock Sockets
	DllVersion = MAKEWORD(2, 1);
	// catch any errors
	if (WSAStartup(DllVersion, &wsaData) != 0) {
		MessageBoxA(NULL, "Winstock startup failed", "Error", MB_OK | MB_ICONERROR);
		system("pause");
		WSACleanup();
		exit(10);
	}

	// Establish the socket and connection
	thisSocket = socket(AF_INET, SOCK_DGRAM, NULL); // Set up the socket connection
	if (thisSocket == INVALID_SOCKET) {
		printf("Could not create socket");
		WSACleanup();
		exit(0);
	}

	// Setup Socket address configuration
	destination_addr; // Address to be binded to our connection socket
	inet_pton(AF_INET, SERVER, &(destination_addr.sin_addr)); // Use server address - using localhost only
	destination_addr.sin_port = htons(PORT); // The port
	destination_addr.sin_family = AF_INET; // It is an IPv4 Socket. You could also use AF_INET6 for IPv6 Sockets

	// Setup Socket address configuration
	inet_pton(AF_INET, LOCAL, &(local_addr.sin_addr)); // Use server address - using localhost only
	local_addr.sin_port = htons(0); // The port
	local_addr.sin_family = AF_INET; // It is an IPv4 Socket. You could also use AF_INET6 for IPv6 Sockets

	if (bind(thisSocket, (SOCKADDR*)&local_addr, sizeof(local_addr)) == SOCKET_ERROR)
	{
		fprintf(stderr, "Could not bind name to socket.\n");
		closesocket(thisSocket);
		WSACleanup();
		exit(0);
	}

	while (true) {
		
		buffer = "Hellowwww :>";
		bufferlength = buffer.size();

		// Send length of buffer 
		if (sendto(thisSocket, (char*)&bufferlength, sizeof(int), NULL, (SOCKADDR*)&destination_addr, sizeof(destination_addr)) < 0) {
			cout << "Send message failed" << endl;
		}
		if (sendto(thisSocket, buffer.c_str(), bufferlength, NULL, (SOCKADDR*)&destination_addr, sizeof(destination_addr)) < 0) {
			cout << "Send message failed" << endl;
		}
	}



	system("pause");

	return 0;
}