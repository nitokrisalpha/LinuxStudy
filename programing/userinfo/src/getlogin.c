#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
    char usrname[10];
    strcpy(usrname,getlogin());
    printf("%s\n",usrname);
    return 0;
}

