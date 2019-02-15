# 标准IO库

    标准IO库(stdio)及其头文件为底层IO系统提供了一个通用的接口，我们要学习IO库中的一些函数

## fopen函数

    函数原型
    FILE *fopen(const char *filename,const char *mode);
    *mode的可用列表
        r/rb            只读
        w/wb            只写，文件长度截取为0
        a/ab            只写，追加到文件末尾
        r+/rb+/r+b      读写方式打开
        w+/wb+/w+b      读写方式打开,文件长度截取为0
        a+/ab+/a+b      读写方式打开，追加到文件末尾
    fopen类似于系统底层的open调用。主要用于文件和终端的输入输出，如果要明确的控制，还是底层调用比较稳，可以避免潜在问题 FILE fopen(const char *filename,const char *mode); 打开由filename参数指定的文件，并把它与一个文件流关联起来

## fread函数

    函数原型
    size _t fread(void *ptr,size_t size,size_t nitems,FILE *stream)
    fread函数用于从一个文件流里读取数据，数据从文件流stream读到由ptr指向的数据缓冲区里,size参数指定每个数据记录的长度，计数器nitems给出要传输的记录个数。它返回值是成功读到数据缓冲区里的记录个数,当它达到文件尾时返回值会小于nitems,甚至可以是0

## fwrite函数

    fwrite函数从指定的数据缓冲区取出数据揭露，返回值是成功写入的记录个数

## fclose函数

    fclose函数关闭指定的文件流stream，使所有尚未写出的数据都写出

## fflush函数

    fflush函数的作用是立即把未写出的数据写出，fclose函数隐含调用了fflush函数，不必在fclose函数前调用fflush

## fseek函数

    fseek函数函数是与lseek系统调用对应的文件流函数，它在文件流里为下一次读写操作指定位置

## fgetc getc getchar函数

    fgetc函数从文件流取出下一个字节并把它作为一个字符返回。当它达到文件尾或出现错误时返回EOF。必须通过ferror或feof来区分这两种情况

## fputc,putc和putchar函数

    fputc函数把一个字符写道一个输出文件流中，它返回写入的值，如果失败则返回EOF

## fgets 和 gets函数
    
    函数原型
    char *fgets(char *s,int n,FILE *stream)
    char *fgets(char *s)

    fgets函数从文件流中读取一个字符串，并把字符串写到s指定的字符串里

## 文件流错误

    为了表明错误，许多stdio库函数都会返回一个超出范围的值，比如空指针或EOF常数，此时，错误由外部变量errno指出
