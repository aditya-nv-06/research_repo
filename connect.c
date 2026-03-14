// PostgreSQL C connection example
#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include "./select.c"

int create_table(PGconn * conn,const char * table_name){
    char query[512];
    snprintf(query,sizeof(query),"CREATE TABLE IF NOT EXISTS %s ("
            "id SERIAL PRIMARY KEY,"
            "name VARCHAR(100),"
                "age INTEGER"
               " )",table_name);

    PGresult * res = PQexec(conn,query);

    if(PQresultStatus(res)!= PGRES_COMMAND_OK){
        fprintf(stderr,"Table not created %s\n",PQerrorMessage(conn));
        PQclear(res);
        return -1;
    }
    
    printf("Table created successfully %s \n",table_name);
    PQclear(res);
    return 0;
}

int insert_data(PGconn * conn,char*name,int age){
    char query[512];
    snprintf(query,sizeof(query),
    "INSERT INTO DATAUSER(name,age) VALUES('%s',%d)",name,age);

    PGresult *res = PQexec(conn,query);

    if(PQresultStatus(res)!= PGRES_COMMAND_OK){
        fprintf(stderr,"Insert failed: %s\n",PQerrorMessage(conn));
        PQclear(res);
        exit(1);
    }

    printf("\nInserted Sucessfully");
    PQclear(res);
    return 0;
}


int main() {
    // Connection string
    char *connUrl = "dbname=research_db user=postgres password=root host=localhost port=5432";
    
    // Create connection instance
    PGconn *pg = PQconnectdb(connUrl);
    
    // Check connection status (fix: PGconn* -> ConnStatusType)
    if (PQstatus(pg) != CONNECTION_OK) {
        printf("Connection failed: %s", PQerrorMessage(pg));
        PQfinish(pg);
        exit(1);
    }
    
    printf("Connected successfully to PostgreSQL!\n");

    if(create_table(pg,"datauser")==0){
        printf("Done creating the table\n");
    }

    //insert_data(pg,"Joe",20);

    select_all_data(pg,"datauser");

    PQfinish(pg);
    return 0;
}

