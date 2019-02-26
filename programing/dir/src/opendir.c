/*************************************************************************
    > File Name: opendir.c
    > Author: NitokrisAlpha
    > Mail: d2837965115@outlook.com
    > Created Time: 2019年02月26日 星期二 13时23分49秒
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#define MAX_LENG 1024

int main(int argc,char *argv[],char **env)
{
	DIR *curr_dir;
	curr_dir = opendir(argv[1]);
	char cur[MAX_LENG];
	if(curr_dir != NULL)
	{
		printf("打开目录成功\n");
	}
	
	chdir(argv[1]);
	getcwd(cur,MAX_LENG);
	printf("当前目录是:%s\n",cur);
	return 0;
}
