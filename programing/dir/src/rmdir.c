/*************************************************************************
    > File Name: rmdir.c
    > Author: NitokrisAlpha
    > Mail: d2837965115@outlook.com
    > Created Time: 2019年02月25日 星期一 21时22分59秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>

int main()
{
	int flag;
	flag = rmdir("testDir");
	if(flag == 0)
	{
		printf("目录删除成功");
	}
	return 0;
}
