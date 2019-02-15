/*************************************************************************
    > File Name: copyfile_stdio.c
    > Author: NitokrisAlpha
    > Mail: d2837965115@outlook.com
    > Created Time: 2019年02月15日 星期五 15时35分23秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int c;
	FILE *in,*out;

	in = fopen("file.in","r");
	out = fopen("file.out","w");

	while((c = fgetc(in)) != EOF)
		fputc(c,out);
	printf("复制成功，请查看文件\n");
	return 0;
}
