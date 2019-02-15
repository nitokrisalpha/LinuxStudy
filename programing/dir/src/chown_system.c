/*************************************************************************
    > File Name: chown_system.c
    > Author: NitokrisAlpha
    > Mail: d2837965115@outlook.com
    > Created Time: 2019年02月15日 星期五 20时26分35秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc,char *argv[],char **env)
{
	uid_t cur_user = getuid();
	
	if(chown("../../dir/chowntest",cur_user,1001) != 0)
	{
		printf("调用失败");
		exit(-1);
	}
	return 0;
}
