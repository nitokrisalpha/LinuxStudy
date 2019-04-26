#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    struct passwd *mypass;
    mypass = getpwnam("nitokris");
    printf("你的密码是:%s\n",mypass->pw_passwd);
    return 0;
}

