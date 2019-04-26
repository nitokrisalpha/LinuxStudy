#include <stdio.h>
#include <sys/utsname.h>

int main()
{
    struct utsname name;
    int i= uname(&name);
    printf("%d\n",i);
    printf("release is :%s\n",name.release);
    return 0;
}

