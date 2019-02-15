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
