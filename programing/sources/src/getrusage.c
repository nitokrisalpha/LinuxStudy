#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int j = 10000;
    for (int i = 0; i < 1000; i++)
    {
        j--;
    }

    struct rusage *usage;
    getrusage(RUSAGE_SELF, usage);
    printf("%s\n", ctime((time_t *)usage->ru_utime.tv_usec));
}