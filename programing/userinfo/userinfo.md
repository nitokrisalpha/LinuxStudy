# 用户信息

* 在linux中，除了init程序以外，其他所有的程序都是由其他程序或用户启动的。用户通常是在一个响应他们命令的shell中启动程序，在linux内部，用户有一个唯一的标识符，linux运行的每个程序都以某个用户的名义来运行的，所以都有一个关联的UID

* UID有它自己的类型 -- uidx_t ,它定义在 sys/types.h 中。通常是一个小整数，有些UID是系统预定义的，其他的是管理员创建的，通常情况下用户的UID都大于100(现在的桌面发行版普遍是1000)

    ```c
        #include <sys/types.h>
        #include <unistd.h>
        uid_t getuid(void);
        char *getlogin(void);
    ```
* getuid函数返回程序关联的UID，它通常是启动程序的用户UID

* getlogin函数返回的是当前用户关联的登录名

## 标准又有效的获取用户信息的编程借口

* 上面的方法在现代的linux发行版中不推荐使用，因为为了提高系统的安全性，现代的类UNIX系统都不再使用简单的密码文件，现在使用的都是shadow密码文件来保存用户密码

```c
    #include <sys/types.h>
    #include <pwd.h>

    struct passwd *getpwuid(uid_t uid);
    struct passwd *getpwnam(const char *name);
```
