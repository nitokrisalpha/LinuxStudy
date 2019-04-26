#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    long hostid;
    hostid = gethostid();
    printf("host id is:%ld\n",hostid);
    return 0;
}

