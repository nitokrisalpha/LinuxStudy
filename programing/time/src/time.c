/*
    filename:time.c
    本程序会在20秒时间内没两秒钟打印一次底层的时间值
    使用的是 time函数
    
    #include <time.h>

    time_t time(time_t* timer)
*/
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int i;
    time_t the_time;
    for(i = 0; i <= 10; i++)
    {
        the_time = time((time_t *)0);
        printf("the time is %ld\n",the_time);
        sleep(2);
    }
    exit(0);
}
