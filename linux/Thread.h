/* 
 * @file   Thread.h
 * @author Dana
 *
 */

#ifndef __THREAD_H__
#define __THREAD_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <netdb.h>
#include <stdlib.h>

#define INVALID_SOCKET -1

void* Client(void*);                  //sending messages to other clients
void* Listener(void*);                //receive and display incoming messages 
void* PortChanger(void*);             //change communication port each 45 seconds

void CreateListenerThread(void*); 
void CreatePortChangerThread(void*);  //create thread for changing communication port 
void CreateClientThread(void*);       //create thread for servicing client

void closesocket (int);               //fix platform dependent func
void Sleep (int);                     //fix platform dependent func

#endif //__THREAD_H__
