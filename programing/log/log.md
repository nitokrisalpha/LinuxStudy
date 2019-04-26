# 日志

* 许多应用程序需要记录它们的活动。系统程序经常需要想控制台或日志文件写消息。这些消息可能是指示错误等等信息。

* 通常这些日志信息被记录在系统文件中可能是 /usr/adm 或者 /var/log 目录

* 但是有些UNIX系统并不是像上面那样提供日志文件，而是提供一些工具来读取系统事件的数据库

* UNIX规范通过syslog函数为所有程序产生日志信息提供了一个接口是 syslog函数

```c
    #include <syslog.h>

    void openlog(const char *ident, int option, int facility);
    void syslog(int priority, const char *format, ...);
    void closelog(void);

    void vsyslog(int priority, const char *format, va_list ap);
```

* syslog 函数向系统的日志设施(facility) 发送一条日志信息：每条信息都有一个priority参数，该参数是一个严重级别与一个设施值的按位或，严重级别控制日志信息的处理方式，设施值记录日志信息的来源

* syslog.h中还定义了一些能够改变日志记录行为的其他函数，如下

```c
    #include <syslog.h>
    void closelog(void);
    void openlog(const char *ident, int logopt, int facility);
    int setlogmask(int maskpri);
```

* 可以通过调用openlog函数来改变日志信息的表示方式。它可以设置一个字符串ident，该字符串会添加在日志信息的前面。你可以通过它来指明是那个程序创建了这条信息。facility参数会记录一个将被用于后续syslog调用的默认设施值，其默认值是LOG_USER。