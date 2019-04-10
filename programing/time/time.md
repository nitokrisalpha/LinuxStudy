# Linux时间处理

* 时间这个词并不陌生，我们每天都可能在浪费时间，在计算机中，基本上的程序都会用到时间，所有的UNIX时间都使用同一个时间和日期的起点：格林尼治时间（GMT）Linux也不例外，Linux系统中所有时间都从那时起记过的秒数来衡量，时间通过一个预定义的类型time_t来处理

> 实验1 time函数

* 源码见 time.c

> 实验2 difftime函数

* 源码见difftime.c

> 实验3 gmtime函数

* 源码见 gmtime.c

> 实验4 mktime函数

* mktime函数是把一个tm结构体转换回time_t值，如果tm结构不能被表示为time_t值，则回返回-1

> 更友好的时间日期表示 asctime函数和ctime函数

* asctime函数返回一个字符串，它表示由tm结构timeptr所给出的时间和日期

* ctime函数和asctime函数一样返回一个字符串，但是ctime传入的参数直接是底层时间值，ctime为你处理好了很多，然后返回一个表示当前时间的字符串

> 更加现代化的格式 strftime函数

* Linux和现代类Unix系统提供了strftime函数，他很像一个针对时间和日期的sprintf函数，工作方式也是类似的
