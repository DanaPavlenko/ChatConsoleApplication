/* 
 * @file   Socket.h
 * @author Dana
 *
 */

#ifndef __SOCKET_H__
#define __SOCKET_H__

#define PORT 7300
#define SERVER_MAX_CONNECTIONS 27
#define MAX_CLIENT_NAME 27
#define MAX_MESSAGE_LENGTH 1024
#define PORT_CHANGING_RANGE 100
#define PORT_LENGTH 4

#include <stdio.h>
#include <time.h>
#include "Thread.h"

extern char message [MAX_MESSAGE_LENGTH]; 
extern int sock;
extern int clients_count;
extern int clients [SERVER_MAX_CONNECTIONS];

static const char portChangeReq [] = "NewPort-<";
static const char success [] = "success";
static const char failure [] = "failure";

bool Init();                            //initialize WSA
bool OpenConnecton(int&, int);          //create socket and setting it to accept incoming connections
void ScanConnection(int);               //wait for incoming connections and add new clients
bool ServerConnect(int&, char*, int);   //create socket and connect to server
void* Client(void*);                    //sending messages to other clients
void* Listener(void*);                  //receive and display incoming 
void* PortChanger(void*);               //change communication port each 45
char* GetClientName();                  //return host name for the local computer
void ChangePortRequest(char*, int); 	//send request, connect via new port and close old 
int ChangePortAnswer(int, int);         //return new socket with accepted client and close old

#endif //__SOCKET_H__
