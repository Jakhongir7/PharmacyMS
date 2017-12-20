#ifndef PHARMACYMS_REQUEST_PARSER_H
#define PHARMACYMS_REQUEST_PARSER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include "../define/define.h"

#define MAX_SIZE 30
#define MAX_TEXT 50

/* These structs are used by clientOn (Company) */
struct auth_back {
    int isExist;
    char id[MAX_SIZE];
    char name[MAX_SIZE];
    char address[MAX_TEXT];
    char contact[MAX_SIZE];
    uid_t user_type;
};

struct search_back {
    int isExist;
    char med_id[MAX_SIZE];
    char name[MAX_SIZE];
    char description[MAX_TEXT];
    double price;
    char comp_id[MAX_SIZE];
};

struct search_back_inventory{
    char store_id[MAX_SIZE];
    char med_id[MAX_SIZE];
    char name[MAX_SIZE];
    int quantity;
} ;

struct purchase_back {
    int success;
    char trans_id[MAX_SIZE];
    char trans_date[MAX_SIZE];
    char comp_id[MAX_SIZE];
    char store_id[MAX_SIZE];
    char med_id[MAX_SIZE];
    int quantity;
    int status;
};

struct journal_back {
    char trans_id[MAX_SIZE];
    char trans_date[MAX_SIZE];
    char comp_id[MAX_SIZE];
    char store_id[MAX_SIZE];
    char med_id[MAX_SIZE];
    int quantity;
};

/* These structs are used by clientOn (Drugstore) */
struct authorizing {
    char login[MAX_SIZE];
    char password[MAX_SIZE];
    uid_t type;
};

struct searching {
    char name[MAX_SIZE];
};

struct purchasing {
    char name[MAX_SIZE];
    int quantity;
};

/* This struct is used by admin */

struct usersToAdmin {
    char id[MAX_SIZE];
    char name[MAX_SIZE];
    char address[MAX_TEXT];
    char contact[MAX_SIZE];
};

struct toAdmin {
    struct usersToAdmin* users;
    uid_t user_type;
} ;

struct fromAdmin {
    uid_t user_type;
};

typedef struct {
    struct auth_back authorization;
    struct search_back search;
    struct search_back *medicine;
    struct search_back_inventory* search_inventory;
    struct purchase_back purchase;
    struct journal_back* journal;
    struct toAdmin admin;
    uid_t type;
} toClient;

typedef struct {
    struct authorizing authorization;
    struct searching search;
    struct purchasing purchase;
    struct fromAdmin admin;
    uid_t type;
} toServer;

/* This struct is used when got answer from server by clientOn (Drugstore) */
typedef struct {
    struct auth_back authorization;
    struct search_back search;
    struct search_back* medicine;
    struct search_back_inventory* search_inventory;
    struct purchase_back purchase;
    struct journal_back* journal;
    struct toAdmin admin;
    uid_t type;
} fromServer;

/* This struct is used when got query from clientOn (Company) */
typedef struct {
    struct authorizing authorization;
    struct searching search;
    struct purchasing purchase;
    struct fromAdmin admin;
    uid_t type;
} fromClient;

void test1();
char* clientStructToStr(const toServer *);
char* serverStructToStr(const toClient*);
void serverStrToStruct(const char *, fromServer *);
void clientStrToStruct(const char *, fromClient *);
#endif //PHARMACYMS_REQUEST_PARSER_H
