/*************************************************************************
    > File Name: chdir.c
    > Author: NitokrisAlpha
    > Mail: d2837965115@outlook.com
    > Created Time: 2019年02月25日 星期一 21时27分16秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int flag;
	flag = mkdir("testdir",S_IRWXU);
	if(flag == 0)
	{
		printf("创建文件夹失败");
	}
	chdir("testdir");
	
	open("testfile",O_CREAT,S_IRWXU);
	return 0;
}
