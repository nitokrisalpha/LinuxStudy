#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    struct tm *tmv;
    time_t timeval;
    time(&timeval);
    tmv = gmtime(&timeval);
    printf("time is %s\n",asctime(tmv));
    return 0;
}

