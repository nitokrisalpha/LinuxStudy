#include <stdio.h>
#include <stdlib.h>

int main(){
    char tmpname[L_tmpnam];
    char *filename;
    FILE *tmpfp;

    filename = tmpnam(tmpname);
    printf("临时文件名是:%s\n", filename);
    tmpfp = tmpfile();
    if(tmpfp){
        printf("成功打开一个临时文件\n");
    }else
    {
        perror("tmpfile");
    }

    return 0;
}