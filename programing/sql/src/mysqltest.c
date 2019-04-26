#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main()
{
    MYSQL *conn;
    conn = mysql_init(NULL);
    if(conn == NULL)
    {
        printf("mysql初始化失败\n");   
    }

    return 0;
}

