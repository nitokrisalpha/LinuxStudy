#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    time_t tim;
    time(&tim);
    printf("当前日期：%s\n",ctime(&tim));
    return 0;
}

