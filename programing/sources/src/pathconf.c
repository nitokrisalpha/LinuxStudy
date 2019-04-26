#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(){
    printf("链接数目限制:%d\n", pathconf("/usr", _PC_LINK_MAX));
}