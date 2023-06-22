/* 
 * @file   Socket.c
 * @author Dana
 *
 */

#include "Socket.h"

char message[MAX_MESSAGE_LENGTH] = {0}; 
int sock = 0;
int clients_count = 0;
int clients [SERVER_MAX_CONNECTIONS] = {0}; 

bool Init() 
{
#ifdef _WIN32
	WSAData wData;
	if (WSAStartup(MAKEWORD(2, 2), &wData) != 0) {
		return false;
	}
#endif
	return true;
}

bool OpenConnecton(int& sock, int port)
{
	struct sockaddr_in addr;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		perror("socket");
		return false;
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		perror("bind");
		return false;
	}

	if (listen(sock, SERVER_MAX_CONNECTIONS) == -1) {
		perror("listen");
		return false;
	}
	return true;
}

void ScanConnection(int sock) 
{
	int client_socket;
	struct sockaddr_in client_addr;

	#ifdef __linux__ 
	unsigned int client_addr_size = sizeof(client_addr);
    #elif _WIN32
	int client_addr_size = sizeof(client_addr);
     #endif

	while (client_socket = accept(sock, (sockaddr*)&client_addr, &client_addr_size)) {
		clients_count++;
		for (int i = 0; i < clients_count; i++) {
			if (!clients[i]) {
				clients[i] = client_socket;
				break;
			}
		}
		hostent *hst;
		hst=gethostbyaddr((char*) &client_addr.sin_addr.s_addr, 4, AF_INET);

		printf("+%s [%s] new connect! | %d user online\n",
			(hst)?hst->h_name:"", inet_ntoa(client_addr.sin_addr), clients_count);

		CreateClientThread(&client_socket);
	}
}

bool ServerConnect(int& src, char* IP, int port)
{
	struct sockaddr_in server_addr;

	src = socket(AF_INET, SOCK_STREAM, 0);
	if (src == INVALID_SOCKET) {
		perror("socket");
		return false;
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = inet_addr(IP); 

	if (connect(src, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
		perror("connect");
		return false;
	}
	return true;
}

void* Client(void* client_socket)
{
	int bytes_recv;
	int my_sock = *(int*)client_socket;
	char buff[MAX_MESSAGE_LENGTH];
	static const char congratulation [] = "\rWelcome to chatroom!";

	send(my_sock, congratulation, strlen(congratulation), 0);

	while((bytes_recv=recv(my_sock, &buff[0], sizeof(buff), 0)) != INVALID_SOCKET) {
		if (!strncmp(buff, portChangeReq, sizeof(portChangeReq)-1)) {
			my_sock = ChangePortAnswer(my_sock, atoi(buff + sizeof(portChangeReq) - 1));
		{
		else { //sending message to other clients
			for (int i = 0; i < SERVER_MAX_CONNECTIONS; i++) {
				if (clients[i] && clients[i] != my_sock) {
					send(clients[i], &buff[0], bytes_recv, 0);
				}
			}
		}
	}
	// disconecting process
	for (int i = 0; i < SERVER_MAX_CONNECTIONS; i++) {
		if (clients[i] == my_sock) {
			clients[i] = 0;
		}
	}
	clients_count--;
	printf("disconnect | %d user online\n", clients_count);
	closesocket(my_sock);
	return 0;
}

void* Listener (void* lsock)
{
	int bytes_recv;
	while ((bytes_recv = recv(*(int*)lsock, &message[0], sizeof(message), 0)) != INVALID_SOCKET) {
		if (strcmp(message, success)) {
			printf("\r%s\nYou: ", message);
		}
	}
	closesocket(*(int*)lsock);
	return 0;
}

void* PortChanger (void* IP) 
{	
	bool running = true;
	char intport [PORT_LENGTH];
	srand(time(NULL));

	while (running) {
		Sleep(45000);
		int port = PORT + rand() % PORT_CHANGING_RANGE + 1;
		sprintf(intport,"%d", port);
		strcpy(message, portChangeReq);
		strcat(message, intport);
		strcat(message, ">");
		ChangePortRequest((char*)IP, port); 
	}
	return 0;
}

char* GetClientName () 
{
	char* name = new char[MAX_CLIENT_NAME];
	gethostname(name, MAX_CLIENT_NAME);
	strcat(name, ": ");
	return name;
}

void ChangePortRequest (char* IP, int port)
{
	send(sock, message, sizeof(message), 0);
	while (!strncmp(message, portChangeReq, sizeof(portChangeReq)-1)) { 
		/* wait for answer */ 
	}
	if (!strncmp(message, success, sizeof(success)-1)) {
		closesocket(sock);
		if (!ServerConnect(sock, IP, port)) {
			ServerConnect(sock, IP, PORT);
		}
		CreateListenerThread(&sock);
	}
}

int ChangePortAnswer (int client_socket, int port) 
{
	int lisener, new_sock;
	if (!OpenConnecton(lisener, port)) {
		send(client_socket, failure, sizeof(failure), 0);
		return client_socket;
	}
	else {
		send(client_socket, success, sizeof(success), 0);
	}
	new_sock = accept(lisener, NULL, NULL);
	closesocket(lisener);
	for (int i = 0; i < SERVER_MAX_CONNECTIONS; i++) {
		if (clients[i] == client_socket) {
			closesocket(client_socket);
			clients[i] = new_sock;
		}
	}
	return new_sock;
}
