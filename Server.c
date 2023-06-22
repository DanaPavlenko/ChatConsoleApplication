/* 
 * @file   Server.c
 * @author Dana
 *
 */

#include "Socket.h"

int main(void)
{
	if (!Init()) {
		printf("WSA Startup fail\n");
		return 0;
	}

	int listener;
	if (OpenConnecton(listener, PORT)) {
	   printf("server: waiting for connections...\n");
	   ScanConnection(listener);
	}
	return 0;
}
