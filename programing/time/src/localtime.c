#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    struct tm *localtimet;
    time_t currtime;
    time(&currtime);
    localtimet = localtime(&currtime);
    printf("%02d/%02d/%02d",localtimet->tm_year, localtimet->tm_mon, localtimet->tm_mday);
    return 0;
}

