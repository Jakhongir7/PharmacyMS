#ifndef PHARMACYMS_SERVER_H
#define PHARMACYMS_SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "request_parser.h"
#include "../define/define.h"
#include "../dbManagement"

#define PORT 5000
#define TRUE 1
#define FALSE 0
#define MAX_CLIENT 100
#define MAX_SIZE 2048

typedef struct {
    struct sockaddr_in addr;    // Client remote address
    int connfd;                 // Connection file descriptor
    int uid;                    // Client unique identifier
} client_t;

void queue_add(client_t *);
void server();
void *connection_handler(void*);
size_t str_length(const char*);
void jsonParser(const char *);
void requestHander(const fromClient *);

#endif //PHARMACYMS_SERVER_H
