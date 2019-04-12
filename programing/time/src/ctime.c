/*
 *  file name : ctime.c
 *  测试ctime函数
 *  调用time函数得到底层时间值，并让ctime函数处理得到的底层时间值，把时间值转换为可读的字符串，然后答应它
 * */
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

