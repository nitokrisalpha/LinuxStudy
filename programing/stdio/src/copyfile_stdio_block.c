/*************************************************************************
    > File Name: copyfile_stdio_block.c
    > Author: NitokrisAlpha
    > Mail: d2837965115@outlook.com
    > Created Time: 2019年02月15日 星期五 15时45分16秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	FILE *in, *out;
	in = fopen("file.in","r");
	out = fopen("file.out","w");
	char str[1024];
//	int nread = 0;
	fgets(str,strlen(str),in);
	fprintf(out,"%s",str);
	printf("程序运行成功");
	return 0;
}
