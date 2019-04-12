/**
 * 文件复制程序，第一版本不接受参数
 */
#include <stdio.h>

#define MAX 1024

int main(int argc,char *argv[])
{
    char buf[MAX];
    FILE *in, *out;
    in = fopen(argv[1],"r");
    if(in == NULL)
    {
        printf("没有找到那个文件\n");
        return -1;
    }
    fscanf(in, "%s",buf);
    out = fopen(argv[2],"w");
    if(out == NULL)
    {
        printf("文件名已存在，请更换\n");
        return -1;
    }
    fprintf(out,"%s", buf); 
    fclose(in);
    fclose(out);
    return 0;
}

