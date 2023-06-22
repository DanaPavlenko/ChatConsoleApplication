/* 
 * @file   Thread.h
 * @author Dana
 *
 */

#ifndef __THREAD_H__
#define __THREAD_H__

#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

void* Client(void*);                   //sending messages to other clients
void* Listener(void*);                 //receive and display incoming messages 
void* PortChanger(void*);              //change communication port each 45 seconds

void CreateListenerThread(void*); 
void CreatePortChangerThread(void*);   //create thread for changing communication port 
void CreateClientThread(void*);        //create thread for servicing client

#endif //__THREAD_H__
