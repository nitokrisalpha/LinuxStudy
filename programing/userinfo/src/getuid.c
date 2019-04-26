#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    uid_t curr_uid;
    curr_uid = getuid();
    if(curr_uid == 1000)
    {
        printf("当前用户是普通用户\n");
    }
    return 0;
}

