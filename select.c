#include<stdio.h>
#include<stdlib.h>
#include<libpq-fe.h>

int select_all_data(PGconn * conn,const char *table_name)
{
    char query[512];
    snprintf(query,sizeof(query),
    "SELECT * FROM %s",table_name);

    PGresult * res = PQexec(conn,query);
    
    if(PQresultStatus(res)!= PGRES_TUPLES_OK ){
        fprintf(stderr,"Error in selecting the data %s \n",PQerrorMessage(conn));
        PQclear(res);
        exit(1);
    }

    int rows = PQntuples(res);
    if(rows == 0){
        printf("There is no errors in the Database");
    }else{
        printf("\n📋 %d Employee(s):\n", rows);
        printf("%-4s | %-20s | %s\n", "ID", "Name", "Age");
        printf("----|--------------------|----\n");
        for (int i = 0; i < rows; i++) {
            printf("%-4s | %-20s | %s\n", 
                   PQgetvalue(res, i, 0), 
                   PQgetvalue(res, i, 1), 
                   PQgetvalue(res, i, 2));
        }
    }
    printf("SELECTED PROPERLY");
    PQclear(res);
    return 0;
}

int delete_record(PGconn * conn,const char * condition,const char* table_name){
    char query[512];
    snprintf(query, sizeof(query), "DELETE FROM %s %s", table_name, condition);
    

    PGresult * res = PQexec(conn,query);
    return 0;
}