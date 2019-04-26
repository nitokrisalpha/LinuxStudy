#include <unistd.h>
#include <stdio.h>

int main()
{
    char hostname[11];
    gethostname(hostname,10);
    printf("主机名是:%s\n",hostname);
    return 0;
}

