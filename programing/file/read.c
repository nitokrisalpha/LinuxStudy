#include <unistd.h>

int main(int argc, char const *argv[])
{
    char arr[1024];
    int nread;

    nread = read(0,arr,1024);

    if (nread == -1) {
        write(1,"read error\n",12);
    }
    
    if ((write(1,arr,nread)) != nread) {
        write(1,"write error\n",12);
    }

    return 0;
}