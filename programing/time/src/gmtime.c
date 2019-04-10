/*
 * file name : gmtime.c
 * 原理:
 *  调用time函数得到系统底层时间值
 *  利用gmtime函数处理得到的底层时间值，得到一个tm类型的结构体，然后读取结构体内相应数据就能得到适合人类阅读的时间
 * 小问题:
 *  这里输出的时间不太对，因为gmtime函数返回的是GMT时间，要看本地时间需要使用localtime函数
 * */
#include <time.h>
#include <stdio.h>
#include <stdlib.h>


int main()
{
    struct tm *tm1;
    time_t the_time;
    time(&the_time);
    tm1 = gmtime(&the_time);
    printf("Raw time is %ld\n",the_time);
    printf("gmtime gives:\n");
    printf("date:%02d/%02d/%02d\n",tm1->tm_year, tm1->tm_mon, tm1->tm_mday);

    return 0;
}

