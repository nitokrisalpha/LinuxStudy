/*************************************************************************
    > File Name: chcwd.c
    > Author: NitokrisAlpha
    > Mail: d2837965115@outlook.com
    > Created Time: 2019年02月26日 星期二 11时24分14秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#define MAX_LENG 100

int main()
{
	char dir[MAX_LENG];
	getcwd(dir,MAX_LENG);
	printf("当前目录是:%s",dir);
	return 0;
}
