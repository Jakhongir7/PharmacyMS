#include "dbManagement.h"
#include "../define/define.h"
#include "../parser/object.h"
#include "../parser/request_parser.h"

MYSQL *connectToDB() {
    MYSQL *con = mysql_init(NULL);

    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }
    if (mysql_real_connect(con, serverAddr, dbUser, dbPassword,
                           dbName, 3307, NULL, 0) == NULL) {
        finish_with_error(con);
    }
    return con;
}

void finish_with_error(MYSQL *con) {
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

int authorization(char *login_id, char *login_password) {
    int type=-1;
    MYSQL *con = connectToDB();
    char query[1024];
    sprintf(query, "SELECT * FROM authorization WHERE id = '%s' AND password = '%s'", login_id, login_password);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
    MYSQL_ROW row;
    MYSQL_RES *result = mysql_store_result(con);
    my_ulonglong numrows = mysql_num_rows(result);
    while ((row = mysql_fetch_row(result))){
        type=atoi(row[2]);
    }
    return type;
}
toClient *searchUser(char *user_id, char *user_password){
    MYSQL *con =connectToDB();
    char query[1024];
    if(authorization(user_id, user_password) == COMPANY){
        sprintf(query,"SELECT * FROM authorization natural join company WHERE id='%s'", user_id);
    }
    else if(authorization(user_id, user_password) == DRUGSTORE){
        sprintf(query,"SELECT * FROM authorization natural join drugstore WHERE id='%s'", user_id);
    } else if(authorization(user_id, user_password) == ADMIN){
        sprintf(query,"SELECT * FROM authorization WHERE id='%s'", user_id);
    }else
        {
            toClient *user;
            user = (toClient *)malloc(sizeof(toClient));
            user->authorization.isExist = FALSE;
            return user;
        }

    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
    MYSQL_RES *result = mysql_store_result(con);
    return object_parser("auth+comp", result);
}
bool isExistAlready(char *med_id, char *tablename,char *field){

    MYSQL *con =connectToDB();
    char query[1024];
    sprintf(query,"SELECT * FROM %s WHERE %s='%s'", tablename, field, med_id);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
    MYSQL_RES *result = mysql_store_result(con);
    
    my_ulonglong numrows = mysql_num_rows(result);
    if (numrows==0)
        return FALSE;
  
       return TRUE;
}

void addUser(char *user_id,char *user_password, char *user_name, char *user_adress, char *user_contact, int type) {
     MYSQL *con =connectToDB();

        char query[1024];
        sprintf(query,"INSERT INTO authorization VALUES('%s','%s', %d)", user_id, user_password, type);
        if (mysql_query(con, query)) {
        finish_with_error(con);
        }
        char query1[1024];

        if (type == COMPANY) {
            sprintf(query1,"INSERT INTO company VALUES('%s','%s', '%s','%s')", user_id, user_name, user_adress, user_contact);
            if (mysql_query(con, query1)) {
            finish_with_error(con);
            }
        } else if (type == DRUGSTORE) {
            sprintf(query1,"INSERT INTO drugstore VALUES('%s','%s', '%s','%s')", user_id, user_name, user_adress, user_contact);
            if (mysql_query(con, query1)) {
            finish_with_error(con);
            }


        }

}

// company queries

bool addNewMedicine(char *med_id, char *med_name, char *description, double price, char *comp_id){
    MYSQL *con =connectToDB();
    if(!isExistAlready(med_id, "medicine", "med_id")) {
        char query[1024];
        sprintf(query,"INSERT INTO medicine VALUES('%s', '%s', '%s', %f, '%s')",med_id, med_name, description, price, comp_id);
        if (mysql_query(con, query)) {
            finish_with_error(con);
        }
        return TRUE;
    }
    
    return FALSE;

}
void *searchFromTable(char *id, char *tablename, char *colname){
    MYSQL *con =connectToDB();
    char query[1024];
    sprintf(query,"SELECT * FROM %s WHERE %s='%s'", tablename, colname, id);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
    MYSQL_RES *result = mysql_store_result(con);
    return object_parser(tablename, result);
}
void *viewCompInventory(char *id){
    return searchFromTable(id,"company","id" );
}

void *viewInventory(char *id) {
    return searchFromTable(id, "medicine", "comp_id");
}
void *viewOrders(char *id){
    return searchFromTable(id, "journal", "comp_id");
}

// Store queries
void *viewMedicine(){
    MYSQL *con =connectToDB();
    char query[1024];
    sprintf(query,"SELECT * FROM medicine");
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
    MYSQL_RES *result = mysql_store_result(con);
    return object_parser("medicine", result);
}

void *viewStoreInventory(char *id){
    return searchFromTable(id, "inventory","store_id" );
}
void *searchByName(char *med_name){
    return searchFromTable(med_name, "medicine", "med_name");
}
void *searchById(char *med_id){
    return searchFromTable(med_id, "medicine", "med_id");
}
void *orderRegister(char *med_name, char *store_id, int quantity){
    MYSQL *con=connectToDB();
    char query[1024];
    sprintf(query,"SELECT id, med_id FROM medicine WHERE med_name='%s'", med_name);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
    MYSQL_ROW  row;
    MYSQL_RES *result = mysql_store_result(con);
    char *comp_id = (char *)malloc(sizeof(char) * mysql_num_rows(result));
    char *med_id = (char *)malloc(sizeof(char) * mysql_num_rows(result));

    while ((row = mysql_fetch_row(result))){
        strcpy(comp_id, row[0]);
        strcpy(med_id, row[1]);
    }

    sprintf(query,"INSERT INTO journal(comp_id, store_id, med_id, quantity, status) VALUES ('%s', '%s', '%s', %d, %d)",
            comp_id, store_id, med_id, quantity, 0 );
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
    sprintf(query,"Select * from journal where comp_id='%s' and store_id = '%s' and"
                    " med_id='%s' and quantity=%d and status=0", comp_id, store_id, med_id, quantity );
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
    result = mysql_store_result(con);
    toClient *client_answer = (toClient *)malloc(sizeof(toClient));
    while ((row = mysql_fetch_row(result))){
        client_answer->purchase.success = TRUE;
        strcpy(client_answer->purchase.trans_id, row[0]);
        strcpy(client_answer->purchase.trans_date, row[1]);
        strcpy(client_answer->purchase.comp_id, row[2]);
        strcpy(client_answer->purchase.store_id, row[3]);
        strcpy(client_answer->purchase.med_id, row[4]);
        client_answer->purchase.quantity = atoi(row[5]);
        client_answer->purchase.status = atoi(row[6]);
    }
    return client_answer;
}
void medDelivered(char *trans_id, char *med_id){
    MYSQL *con=connectToDB();
    char query[1024];

    sprintf(query,"UPDATE journal set status=1 where trans_id=trans_id");
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }

    sprintf(query,"SELECT * from inventory where  med_id=med_id");
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
    MYSQL_RES *result = mysql_store_result(con);
    int num = (int) mysql_num_rows(result);
    if (num == 0) {

    }
}

//DELETION
void delete(char *id, char *tname, char *cname){
    MYSQL *con=connectToDB();
    char query[1024];

    sprintf(query,"DELETE from %s  where %s='%s'", tname, cname, id);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}
void deleteMedicine(char *id){
    delete(id, "medicine", "med_id");
}
void deleteStore(char *id){
    delete(id, "drugstore", "id");
}
void deleteCompany(char *id){
    delete(id, "company", "id");
}

