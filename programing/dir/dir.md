# 文件和目录的维护

## chmod 系统调用

    你可以通过chmod系统调用来改变文件或目录的访问权限，他是shell程序chmod的基础，函数原型如下
    #include <sys/stat.h>
    int chmod(const char *path, mode_t mode);
    path 参数指定的文件被修改为具有mode参数给出的访问权限。参数mode的定义与open系统调用中的一样，也是对所要求的访问权限按位OR操作

## chown 系统调用

    超级用户可以使用chown系统调用来改变一个文件的属主
    #include <sys/types.h> 
    #include <unistd.h>
    int chown(const char *path,uid_t owner,gid_t group);
    这个调用使用的是用户ID和组ID的数字值(通过getuid和getgid调用获得)和一个用于限定谁可以修改用户属主的系统值。如果已经设置了适当的特权，文件的属主和所属组就会改变
    注意:这个系统调用一般只有root调用才能成功，因为root才能改文件权限一个用户到另一个用户，chmod则没有这个限制

## unlink,link和symlink系统调用

    可以使用unlink系统调用来删除一个文件
    unlink系统调用删除一个文件的目录项并减少他的链接数。他在成功时返回0，失败时返回-1，如果想通过这个函数来成功删除文件，你就必须拥有该文件所属目录的写和执行权限
    #include <unistd.h>
    
    int unlink(const char *path);
    int link(const char *path);
    int symlink(const char *path1,const char path2);
    如果一个文件的链接数减少到0，并且没有进程打开它，这个文件就会被删除。事实上，目录总是被立刻删除，但文件所占用的空间要等到最后一个进程(如果有的话)关闭它之后才会被系统回首，rm就是使用的这个系统调用

## mkdir和rmdir系统调用
    
    mkdir创建目录，rmdir用于删除目录 函数原型如下：
    
    ```c
    #include <sys/types.h>
    #include <sys/stat.h>

    int mkdir(const char *path,mode_t mode);
    ```
*  mkdir系统调用用于创建目录，相当于mkdir命令，参数path是被创建的文件夹名，mode参数是目录的权限，示例源码见mkdir.c

* rmdir系统调用用于删除目录，但是此调用要求目录为空

## chdir系统调用和getcwd函数

* 程序也可以像用户在文件系统里面浏览文件那样来浏览目录。就像使用cd命令一样，程序使用的是 chdir调用

```c
#include <unistd.h>

int chdir(const char *path);
char *getcwd(char *buf,size_t,size);
```

    getcwd 函数把当前目录的名字写道给定的缓冲区buf里。如果目录名的长度超过了参数size给定的缓冲区长度，他就返回NULL，如果成功它返回指针buf，示例代码见 getcwd.c

## 目录扫描

* 在liux上一个常见问题是扫描目录，确定一个特定目录下存放的文件，在shell程序设计中，这很容易做到，与目录操作有关的函数在 dirent.h 头文件中，它们使用一个名为DIR的结构作为目录操作的基础。有下面几个常用函数

    opendir
    readdir
    telldir
    seekdir
    closedir

> opendir 函数

    opendir函数的作用是打开一个目录并建立一个目录流。如果成功返回一个指向DIR结构的指针，该指针用于读取目录数据项,函数原型如下，示例代码见opendir.c

```c
#include <sys/types.h>
#include <dirent.h>

DIR *opendir(const char *name)
```

> readdir 函数

    readdir函数返回一个指针，该指针指向的结构里保存着目录流dirp中下一个目录项的有关资料，函数原型如下

```c
#include <sys/types.h>
#include <dirent.h>

struct dirent *readdir(DIR *dirp);
```

