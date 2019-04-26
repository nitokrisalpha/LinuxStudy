# 资源和限制

* Linux 系统上运行的程序会受到资源限制的影响。他们可能是硬件方面的物理限制(RAM)，系统策略的限制，或具体实现的限制，下表是limits.h中定义的许多代表操作系统方面限制的显示常量

```C
    NAME_MAX    //文件名中的最大字符数
    CHAR_BIT    //char类型值的位数
    CHAR_MAX    //char类型的最大值
    INT_MAX     //int类型的最大值
```

* 头文件 sys/resource.h提供了资源操作方面的定义，其中包括对程序长度，执行优先级和资源等方面限制进行查询和设置的函数。

```C
    #include <sys/resource.h>
    int getpriorty(int which, id_t who);
    int getpriority(int wich, id_t who, int priority);
    int getrlimit(int resource, struct rlimit *r_limit);
    int gettrlimit(int resource, const struct rlimit *r_limit);
    int getrusage(int who, struct rusage *r_usage);
```

* 头文件resource.h中定义的rusage结构用来确定当前程序耗费类多少CPU时间，它至少包两个成员

```c
    struct timeval ru_utime     //使用的用户时间
    struct timeval ru_stime     //使用的系统时间
    /**2**/
    RUSAGE_SELF         //仅返回当前程序的使用信息
    RUSAGE_CHILDREN     //包括子进程的使用信息
```

* getrusage函数将CPU时间信息写入参数 r_usage指向的rusage结构中，参数who可以是上面的常量之一

## 用户和程序优先级

* 普通用户只能降低程序优先级，不能升高

* 应用程序可以用 getpriority和setpriority函数确定和更改它们的优先级，被优先级函数检查或更改的进程可以用进程标识符，组标识符，或用户来确定。which参数制定了对待who参数的方式