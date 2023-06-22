/*
 * @file   Thread.c
 * @author Dana
 *
 */

#include "Thread.h"

void CreateListenerThread(void* sock)
{
	DWORD thID;
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Listener, sock, NULL, &thID);
}

void CreatePortChangerThread(void* ip)
{
	DWORD thID;
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)PortChanger, ip, NULL, &thID);
}

void CreateClientThread(void* sock)
{
	DWORD thID;
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Client, sock, NULL, &thID);
}
