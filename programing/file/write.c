#include <unistd.h>

int main(int argc, char const *argv[])
{
    if((write(1,"Here is some data\n",18)) != 18)
        write(2,"A write error has occurred on file descriptor 1\n",46);
    return 0;
}