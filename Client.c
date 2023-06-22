/* 
 * @file   Client.c
 * @author Dana
 *
 */

#include "Socket.h"

void CmdController(char*);  //realise comand controller and message sending

int main(int argc, char* argv[])
{
	if (argc < 2) {
		printf("No IP server!\n");
		return 0;
	}

	if (!Init()) {
		printf("WSA Startup fail\n", argv[1]);
		return 0;
	}

	if (ServerConnect(sock, argv[1], PORT)) {
	    CreateListenerThread(&sock);
		if (argc > 2) {
			if (!strcmp(argv[2], "bonus")) {
				CreatePortChangerThread(argv[1]);
			}
		}
	    CmdController(argv[1]);
	}
	return 0;
}

void CmdController(char* IP)
{
	bool running = true;
	char* clientName = GetClientName();

	while (running) { 
		gets(message);
		if (!strcmp(message,"")) {
			continue;
		}
		else if (!strncmp(message, portChangeReq, sizeof(portChangeReq)-1)) {
			ChangePortRequest(IP, atoi(message+sizeof(portChangeReq)-1));
			printf("Port changing result - %s\nYou:", message);
		}
		else if (!strcmp(message,"-exit")) {
		        running = false;
		}
		else {
			memmove(message+strlen(clientName), message, sizeof(message)-strlen(clientName));
			memmove(message, clientName, strlen(clientName));
			send(sock, message, sizeof(message), 0);
			printf("\rYou: ");
		}
	}
	closesocket(sock);
}
