/*************************************************************************
    > File Name: mkdir.c
    > Author: NitokrisAlpha
    > Mail: d2837965115@outlook.com
    > Created Time: 2019年02月25日 星期一 21时16分56秒
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
	int flag;
	flag = mkdir("testDir",S_IRWXU);
	if(flag == 0)
	{
		printf("程序执行成功");
	}
	return 0;
}
