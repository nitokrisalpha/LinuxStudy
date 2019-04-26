# 主机信息

* 前面的程序可以查找用户信息，我们一样可以摸到主机信息，uname命令典型代表，获取主机信息可能是为了希望限制程序只能在一台计算机上运行。

* 如果系统安装了网络组件，可以通过 gethostname函数来获取它的网络名

```c
    #include <unistd.h
    int gethostname(char *name, size_t namelen);
```

* 注意：这个函数的namelen最好长一点，短了就读取不完主机名

> 更加详细的主机信息

* 有些时候我们需要获取更加详细的主机信息，这个时候可以通过uname系统调用来获取关于主机更加详细的信息

```c
    #include <sys/utsname.h>
    int uname(struct ustname *buf);

    /*ustname 定义在头文件utsname.h中*/
```

* 我们还可以通过gethostid来获取主机的唯一标识符

```c
    #include <unistd.h>
    long gethostid();
    int sethostid(long hotid);
```
