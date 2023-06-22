/*
 * @file   Thread.c
 * @author Dana
 *
 */

#include "Thread.h"

void CreateListenerThread(void* sock)
{
	pthread_t thID;
	pthread_create(&thID, NULL, Listener, sock);
}

void CreatePortChangerThread(void* ip)
{
	pthread_t thID;
	pthread_create(&thID, NULL, PortChanger, ip);
}

void CreateClientThread(void* sock)
{
	pthread_t thID;
	pthread_create(&thID, NULL, Client, sock);
}

void closesocket(int sock)
{
	close(sock);
}

void Sleep(int time)
{
	sleep(time / 1000);
}
