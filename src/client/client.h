#ifndef PHARMACYMS_CLIENT_H
#define PHARMACYMS_CLIENT_H
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../parser/request_parser.h"

#define TRUE 1
#define FALSE 0
#define PORT 5000
#define MAX_SIZE_BUF 2048
#define SERVER_ADDRESS "127.0.0.1"

int clientStart();
char * sendStrToServer(int server_info, char* messageToServer);
size_t str_length(const char* clientStr);
fromServer* authorizationClient(char * login, char * password);
#endif //PHARMACYMS_CLIENT_H
