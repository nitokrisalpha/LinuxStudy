/*************************************************************************
    > File Name: unlink.c
    > Author: NitokrisAlpha
    > Mail: d2837965115@outlook.com
    > Created Time: 2019年02月15日 星期五 21时16分01秒
 ************************************************************************/

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc,char *argv[],char **env)
{
	open("./testfile",O_CREAT|O_EXCL,S_IRUSR|S_IWUSR);
	if(0 != unlink("./testfile"))
	{
		printf("临时文件创建失败");
		exit(-1);
	}
	getchar();
	
	return 0;
}
