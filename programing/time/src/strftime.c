
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    struct tm *tm_ptr, timestruct;
    time_t the_time;
    char buf[256];
    char *result;

    time(&the_time);
    tm_ptr = localtime(&the_time);
    strftime(buf,256,"%A %d %B, %I:%S %p",tm_ptr);
    printf("strftime gives: %s\n",buf);
    
    printf("calling strptime with:%s\n",buf);
    

    
    return 0;
}

