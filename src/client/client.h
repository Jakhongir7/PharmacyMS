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

char* clientStart(char *string);
size_t str_length(const char* clientStr);
fromServer* authorizationClient(const char * login,const char * password);
fromServer* searchCompanyInventory(const char* id);
fromServer* adminAddUser();
fromServer* searchStoreInventory(const char* searchString);
fromServer* viewCompanyMedicine(const char*);
fromServer* orderNewMedicine(char* name, int quantity, char* id);
fromServer* produceMedicineByCompany(const char *drugName, const char *ID, const char *description, const char *price);
fromServer* addNewUser(char *user_id,char *user_password, char *user_name, char *user_adress, char *user_contact, int type);
fromServer* deleteUser(char *id, int userType);
fromServer* addNewMed(const char *med_id, const char *drugName, const char *description,
                      const char *price, const char* comp_id);
fromServer* viewOrder(char* companyID);
//fromServer* viewCompanyInventoryClient(char* compID);
#endif //PHARMACYMS_CLIENT_H