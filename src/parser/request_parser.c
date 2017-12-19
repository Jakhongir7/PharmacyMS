/*
 *  This is the function which is dealt with
 *  clients query to the Server,
 *  so this is the functions that is intermediate
 *  between GUI and Client's Socket.
 *  Also the structure is like:
 *  GUI ---> This function ---> Socket
 *  and GUI controls this function whereas
 *  this function controls Client's Socket
 *
 */
#include "request_parser.h"

/*int main() {
    *//*client_message = (toServer *)malloc(sizeof(toServer));
    strcpy(client_message->authorization.login, "login");
    strcpy(client_message->authorization.password, "password");
    client_message->type = (uid_t) 0;
    serialization1(client_message);
    //test1();
    //free(client_message);

    server_message = (toClient *)malloc(sizeof(toClient));

     // Here should be some assigning values to the struct

    free(server_message);


    //server_answer = (fromServer *)malloc(sizeof(fromServer));
    client_query = (fromClient *)malloc(sizeof(fromClient));
    client_query = deserialization2(serialization1(client_message), client_query);


    free(client_message);*//*
    test1();
    return 0;
}*/
/*
 *  Just testing function
 *
 * */

/*
 *  This function converts queries to be
 *  sent to the server from clientOn (Drug Stores)
 *
 * */
char* clientStructToStr(const toServer *client_struct) {
    cJSON *root = cJSON_CreateObject();
    cJSON *authorization;
    cJSON *searching;
    cJSON *purchasing;
    char *out;

    cJSON_AddItemToObject(root, "type", cJSON_CreateNumber(client_struct->type));
    switch (client_struct->type) {
        case AUTHORIZATION:
            cJSON_AddItemToObject(root, "authorization", authorization = cJSON_CreateObject());
            cJSON_AddItemToObject(authorization, "login",
                                  cJSON_CreateString(client_struct->authorization.login));
            cJSON_AddItemToObject(authorization, "password",
                                  cJSON_CreateString(client_struct->authorization.password));
            break;
        case SEARCH:
            cJSON_AddItemToObject(root, "search", searching = cJSON_CreateObject());
            cJSON_AddItemToObject(searching, "name",
                                  cJSON_CreateString(client_struct->search.name));
            break;

        case INVENTORY:
            cJSON_AddItemToObject(root, "type", cJSON_CreateNumber(client_struct->type));
            break;

        case PURCHASE:
            cJSON_AddItemToObject(root, "purchase", purchasing = cJSON_CreateObject());
            cJSON_AddItemToObject(purchasing, "name",
                                  cJSON_CreateString(client_struct->purchase.name));
            cJSON_AddItemToObject(purchasing, "quantity",
                                  cJSON_CreateNumber(client_struct->purchase.quantity));
            break;

        case JOURNAL:
            /*
             *  In this condition do nothing as there is no
             *  additional information but type
             *
             *  This case is to identified by Company client
             *  to make query to the server to see its purchase Journal
             * */
        default:
            perror("Please enter proper type!");
            break;
    }
    out = cJSON_Print(root);
    cJSON_Delete(root);
    return out;
}

char* serverStructToStr(const toClient* server_message) {
    cJSON *root = cJSON_CreateObject();
    cJSON *authorization;
    cJSON *searching;
    cJSON *searching_inventory;
    cJSON *medical;
    cJSON *purchasing;
    cJSON *journal;
    cJSON *purchase_query;
    char *out;
    int i;

    cJSON_AddItemToObject(root, "type", cJSON_CreateNumber(server_message->type));
    switch (server_message->type) {
        case AUTHORIZATION:
            cJSON_AddItemToObject(root, "authorization", authorization = cJSON_CreateObject());
            cJSON_AddItemToObject(authorization, "isExist",
                                  cJSON_CreateNumber(server_message->authorization.isExist));
            if(server_message->authorization.isExist == TRUE) {
                cJSON_AddItemToObject(authorization, "id",
                                      cJSON_CreateString(server_message->authorization.id));
                cJSON_AddItemToObject(authorization, "name",
                                      cJSON_CreateString(server_message->authorization.name));
                cJSON_AddItemToObject(authorization, "address",
                                      cJSON_CreateString(server_message->authorization.address));
                cJSON_AddItemToObject(authorization, "contact",
                                      cJSON_CreateString(server_message->authorization.contact));
                cJSON_AddItemToObject(authorization, "user_type",
                                      cJSON_CreateNumber(server_message->authorization.user_type));
            }
            break;
        case SEARCH:
            cJSON_AddItemToObject(root, "search", searching = cJSON_CreateObject());
            cJSON_AddItemToObject(searching, "isExist",
                                  cJSON_CreateNumber(server_message->search.isExist));
            if(server_message->search.isExist == TRUE) {
                cJSON_AddItemToObject(searching, "med_id",
                                      cJSON_CreateString(server_message->search.med_id));
                cJSON_AddItemToObject(searching, "name",
                                      cJSON_CreateString(server_message->search.name));
                cJSON_AddItemToObject(searching, "description",
                                      cJSON_CreateString(server_message->search.description));
                cJSON_AddItemToObject(searching, "price",
                                      cJSON_CreateNumber(server_message->search.price));
                cJSON_AddItemToObject(searching, "comp_id",
                                      cJSON_CreateString(server_message->search.comp_id));
            }
            break;
        case INVENTORY:
            cJSON_AddItemToObject(root, "inventory", searching_inventory = cJSON_CreateArray());
            i = 0;
            while (server_message->search_inventory) {
                cJSON_AddItemToArray(searching_inventory, medical = cJSON_CreateObject());
                cJSON_AddItemToObject(medical, "store_id",
                                      cJSON_CreateString(server_message->search_inventory[i].store_id));
                cJSON_AddItemToObject(medical, "med_id",
                                      cJSON_CreateString(server_message->search_inventory[i].med_id));
                cJSON_AddItemToObject(medical, "name",
                                      cJSON_CreateString(server_message->search_inventory[i].name));
                cJSON_AddItemToObject(medical, "quantity",
                                      cJSON_CreateNumber(server_message->search_inventory[i].quantity));
                ++i;
            }

            break;
        case PURCHASE:
            cJSON_AddItemToObject(root, "purchase", purchasing = cJSON_CreateObject());
            cJSON_AddItemToObject(purchasing, "success",
                                  cJSON_CreateNumber(server_message->purchase.success));
            if(server_message->purchase.success == TRUE) {
                cJSON_AddItemToObject(purchasing, "trans_id",
                                      cJSON_CreateString(server_message->purchase.trans_id));
                cJSON_AddItemToObject(purchasing, "trans_date",
                                      cJSON_CreateString(server_message->purchase.trans_date));
                cJSON_AddItemToObject(purchasing, "comp_id",
                                      cJSON_CreateString(server_message->purchase.comp_id));
                cJSON_AddItemToObject(purchasing, "store_id",
                                      cJSON_CreateString(server_message->purchase.store_id));
                cJSON_AddItemToObject(purchasing, "med_id",
                                      cJSON_CreateString(server_message->purchase.med_id));
                cJSON_AddItemToObject(purchasing, "quantity",
                                      cJSON_CreateNumber(server_message->purchase.quantity));
            }
            break;

        case JOURNAL:
            cJSON_AddItemToObject(root, "journal", journal = cJSON_CreateArray());
            i = 0;
            while (server_message->journal) {
                cJSON_AddItemToArray(journal, purchase_query = cJSON_CreateObject());
                cJSON_AddItemToObject(purchase_query, "trans_id",
                                      cJSON_CreateString(server_message->journal[i].trans_id));
                cJSON_AddItemToObject(purchase_query, "trans_date",
                                      cJSON_CreateString(server_message->journal[i].trans_date));
                cJSON_AddItemToObject(purchase_query, "comp_id",
                                      cJSON_CreateString(server_message->journal[i].comp_id));
                cJSON_AddItemToObject(purchase_query, "store_id",
                                      cJSON_CreateString(server_message->journal[i].store_id));
                cJSON_AddItemToObject(purchase_query, "med_id",
                                      cJSON_CreateString(server_message->journal[i].med_id));
                cJSON_AddItemToObject(purchase_query, "quantity",
                                      cJSON_CreateNumber(server_message->journal[i].quantity));
                ++i;
            }
        default:
            perror("Please enter proper type!");
            break;
    }
    out = cJSON_Print(root);
    printf("%s\n", out);
    cJSON_Delete(root);
    return out;
}

char* adminClientStructToStr(const toAdmin *admin_struct) {
    cJSON *root = cJSON_CreateObject();
    char *out;
    cJSON_AddItemToObject(root, "type",
                          cJSON_CreateNumber(admin_struct->user_type));
    out = cJSON_Print(root);
    cJSON_Delete(root);
}

char* adminServerToStr(const toAdmin *admin_struct) {
    cJSON *root = cJSON_CreateObject();
    cJSON *users;
    cJSON *user;
    char *out;
    int i = 0;
    cJSON_AddItemToObject(root, "type",
                          cJSON_CreateNumber(admin_struct->user_type));
    cJSON_AddItemToObject(root, "users", users = cJSON_CreateArray());
    while (admin_struct->users) {
        cJSON_AddItemToArray(users, user);
        cJSON_AddItemToObject(user, "id",
                              cJSON_CreateString(admin_struct->users->id));
        cJSON_AddItemToObject(user, "name",
                              cJSON_CreateString(admin_struct->users->name));
        cJSON_AddItemToObject(user, "address",
                              cJSON_CreateString(admin_struct->users->address));
        cJSON_AddItemToObject(user, "contact",
                              cJSON_CreateString(admin_struct->users->contact));
    }
    out = cJSON_Print(root);
    cJSON_Delete(root);
}

void serverStrToStruct(const char *message, fromServer *server_answer) {
    cJSON *root = cJSON_Parse(message);
    cJSON *type_item = cJSON_GetObjectItemCaseSensitive(root, "type");
    if (type_item->valueint == AUTHORIZATION) {
        cJSON *authorization_item = cJSON_GetObjectItemCaseSensitive(root, "authorization");
        cJSON *isExist_item = cJSON_GetObjectItemCaseSensitive(authorization_item, "isExist");
        if (isExist_item->valueint == TRUE) {
            cJSON *id_item = cJSON_GetObjectItemCaseSensitive(authorization_item, "id");
            cJSON *name_item = cJSON_GetObjectItemCaseSensitive(authorization_item, "name");
            cJSON *address_item = cJSON_GetObjectItemCaseSensitive(authorization_item, "address");
            cJSON *contact_item = cJSON_GetObjectItemCaseSensitive(authorization_item, "contact");
            cJSON *user_type_item = cJSON_GetObjectItemCaseSensitive(authorization_item, "user_type");
            strcpy(server_answer->authorization.id, id_item->valuestring);
            strcpy(server_answer->authorization.name, name_item->valuestring);
            strcpy(server_answer->authorization.address, address_item->valuestring);
            strcpy(server_answer->authorization.contact, contact_item->valuestring);
            server_answer->authorization.user_type = (uid_t) user_type_item->valueint;
        }
        server_answer->authorization.isExist = (uid_t) isExist_item->valueint;
    } else if (type_item->valueint == SEARCH) {
        cJSON *search_item = cJSON_GetObjectItemCaseSensitive(root, "search");
        cJSON *isExist_item = cJSON_GetObjectItemCaseSensitive(search_item, "isExist");
        if (isExist_item->valueint == TRUE) {
            cJSON *med_id_item = cJSON_GetObjectItemCaseSensitive(search_item, "med_id");
            cJSON *name_item = cJSON_GetObjectItemCaseSensitive(search_item, "name");
            cJSON *description_item = cJSON_GetObjectItemCaseSensitive(search_item, "description");
            cJSON *price_item = cJSON_GetObjectItemCaseSensitive(search_item, "price");
            cJSON *comp_id_item = cJSON_GetObjectItemCaseSensitive(search_item, "comp_id");
            strcpy(server_answer->search.med_id, med_id_item->valuestring);
            strcpy(server_answer->search.name, name_item->valuestring);
            strcpy(server_answer->search.description, description_item->valuestring);
            server_answer->search.price = price_item->valueint;
            strcpy(server_answer->search.comp_id, comp_id_item->valuestring);
        }
        server_answer->search.isExist = (uid_t) isExist_item->valueint;
    } else if (type_item->valueint == INVENTORY) {
        cJSON *inventory_item = cJSON_GetObjectItemCaseSensitive(root, "inventory");
        cJSON *medical;
        cJSON *store_id_item;
        cJSON *med_id_item;
        cJSON *name_item;
        cJSON *quantity_item;
        for (int i = 0; i < cJSON_GetArraySize(inventory_item); ++i) {
            medical = cJSON_GetArrayItem(inventory_item, i);
            store_id_item = cJSON_GetObjectItemCaseSensitive(medical, "store_id");
            med_id_item = cJSON_GetObjectItemCaseSensitive(medical, "med_id");
            name_item = cJSON_GetObjectItemCaseSensitive(medical, "name");
            quantity_item = cJSON_GetObjectItemCaseSensitive(medical, "quantity");
            strcpy(server_answer->search_inventory[i].store_id, store_id_item->valuestring);
            strcpy(server_answer->search_inventory[i].med_id, med_id_item->valuestring);
            strcpy(server_answer->search_inventory[i].name, name_item->valuestring);
            server_answer->search_inventory[i].quantity = quantity_item->valueint;
        }
    } else if (type_item->valueint == PURCHASE) {
        cJSON *purchase_item = cJSON_GetObjectItemCaseSensitive(root, "purchase");
        cJSON *success_item = cJSON_GetObjectItemCaseSensitive(purchase_item, "success");
        if (success_item->valueint == TRUE) {
            cJSON *trans_id_item = cJSON_GetObjectItemCaseSensitive(purchase_item, "trans_id");
            cJSON *trans_date_item = cJSON_GetObjectItemCaseSensitive(purchase_item, "trans_date");
            cJSON *comp_id_item = cJSON_GetObjectItemCaseSensitive(purchase_item, "comp_id");
            cJSON *store_id_item = cJSON_GetObjectItemCaseSensitive(purchase_item, "store_id");
            cJSON *med_id_item = cJSON_GetObjectItemCaseSensitive(purchase_item, "med_id");
            cJSON *quantity_item = cJSON_GetObjectItemCaseSensitive(purchase_item, "quantity");
            strcpy(server_answer->purchase.trans_id, trans_id_item->valuestring);
            strcpy(server_answer->purchase.trans_date, trans_date_item->valuestring);
            strcpy(server_answer->purchase.comp_id, comp_id_item->valuestring);
            strcpy(server_answer->purchase.store_id, store_id_item->valuestring);
            strcpy(server_answer->purchase.med_id, med_id_item->valuestring);
            server_answer->purchase.quantity = quantity_item->valueint;
        }
        server_answer->purchase.success = success_item->valueint;
    } else if (type_item->valueint == JOURNAL) {
        cJSON *journal_item = cJSON_GetObjectItemCaseSensitive(root, "journal");
        cJSON *purchase_item;
        cJSON *trans_id_item;
        cJSON *trans_date_item;
        cJSON *comp_id_item;
        cJSON *store_id_item;
        cJSON *med_id_item;
        cJSON *quantity_item;
        for (int i = 0; i < cJSON_GetArraySize(journal_item); ++i) {
            purchase_item = cJSON_GetArrayItem(journal_item, i);
            trans_id_item = cJSON_GetObjectItemCaseSensitive(purchase_item, "trans_id");
            trans_date_item = cJSON_GetObjectItemCaseSensitive(purchase_item, "trans_date");
            comp_id_item = cJSON_GetObjectItemCaseSensitive(purchase_item, "comp_id");
            store_id_item = cJSON_GetObjectItemCaseSensitive(purchase_item, "store_id");
            med_id_item = cJSON_GetObjectItemCaseSensitive(purchase_item, "med_id");
            quantity_item = cJSON_GetObjectItemCaseSensitive(purchase_item, "quantity");
            strcpy(trans_id_item->valuestring, server_answer->journal[i].trans_id);
            strcpy(trans_date_item->valuestring, server_answer->journal[i].trans_date);
            strcpy(comp_id_item->valuestring, server_answer->journal[i].comp_id);
            strcpy(store_id_item->valuestring, server_answer->journal[i].store_id);
            strcpy(med_id_item->valuestring, server_answer->journal[i].comp_id);
            strcpy(comp_id_item->valuestring, server_answer->journal[i].med_id);
            server_answer->journal[i].quantity = quantity_item->valueint;
        }
    }

    server_answer->type = (uid_t) type_item->valueint;
    cJSON_Delete(root);
}

void clientStrToStruct(const char *message, fromClient *client_query) {
    cJSON *root = cJSON_Parse(message);
    cJSON *type_item = cJSON_GetObjectItemCaseSensitive(root, "type");

    if(type_item->valueint == AUTHORIZATION) {
        cJSON *authorization_item = cJSON_GetObjectItemCaseSensitive(root, "authorization");
        cJSON *login_item = cJSON_GetObjectItemCaseSensitive(authorization_item, "login");
        cJSON *password_item = cJSON_GetObjectItemCaseSensitive(authorization_item, "password");
        strcpy(client_query->authorization.login, login_item->valuestring);
        strcpy(client_query->authorization.password, password_item->valuestring);
    } else if (type_item->valueint == SEARCH) {
        cJSON *search_item = cJSON_GetObjectItemCaseSensitive(root, "search");
        cJSON *name_item = cJSON_GetObjectItemCaseSensitive(search_item, "name");
        strcpy(client_query->search.name, name_item->valuestring);
    } else if (type_item->valueint == INVENTORY) {
        /*
         *  In this condition do nothing as there is no
         *  additional information but type
         *
         *  This condition is used by Drugstore client
         *  to see its inventory
         * */

    } else if (type_item->valueint == PURCHASE) {
        cJSON *purchase_item = cJSON_GetObjectItemCaseSensitive(root, "purchase");
        cJSON *name_item = cJSON_GetObjectItemCaseSensitive(purchase_item, "name");
        cJSON *quantity_item = cJSON_GetObjectItemCaseSensitive(purchase_item, "quantity");
        strcpy(client_query->purchase.name, name_item->valuestring);
        client_query->purchase.quantity = quantity_item->valueint;
    } else if(type_item->valueint == JOURNAL) {
        /*
         *  In this condition do nothing as there is no
         *  additional information but type
         *
         *  This condition is used by Company client
         *  to see its journal (purchase from Drugstore)*/
    }

    client_query->type = (uid_t) type_item->valueint;
    cJSON_Delete(root);
}

