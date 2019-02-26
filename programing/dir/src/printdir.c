/*************************************************************************
    > File Name: printdir.c
    > Author: NitokrisAlpha
    > Mail: d2837965115@outlook.com
    > Created Time: 2019年02月26日 星期二 13时53分21秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

void printdir(char *dir,int depth);

int main()
{
	printf("Directory scan of /home:\n");
	printdir("/home",0);
	printf("done.\n");
	return 0;
}

//打印目录数据
void printdir(char *dir,int depth)
{
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;

	if((dp=opendir(dir)) == NULL)
	{
		fprintf(stderr,"无法打开目录:%s\n",dir);
		return;
	}
	chdir(dir);
	while((entry = readdir(dp)) != NULL)
	{
		//获取文件信息
		lstat(entry->d_name,&statbuf);
		//判断是否为目录
		if(S_ISDIR(statbuf.st_mode))
		{
			if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0)
				continue;
			printf("%*s%s/\n",depth,"",entry->d_name);
		}
		else printf("%*s%s\n",depth,"",entry->d_name);
	}
	chdir("..");
	closedir(dp);
}
