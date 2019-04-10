/*
    使用diff函数计算两个时间差
*/ 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    time_t time1, time2;
    time1 = time((time_t *)0);
    for(int i=0; i<3; i++)
    {
        sleep(2);
    }
    time2 = time((time_t *)0);

    double diff = difftime(time2,time1);
    printf("%lf\n",diff);    
}
