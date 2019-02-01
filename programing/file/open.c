#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
/*
    file name open.c
    创建了一个myfile文件，只允许所有者读写
 */ 
int main(int argc, char const *argv[])
{
   open("myfile",O_CREAT,S_IRUSR|S_IWUSR);
    return 0;
}