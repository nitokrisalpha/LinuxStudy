# Linuz账号管理与ACL权限设置

## Linux的账户与用户组

    linux是多用户操作系统，非管理员用户想使用计算机资源需要向管理员处得到一个账户，故需要对用户进行管理，那Linux又是如何辨别每一个用户的呢?

### 用户标识符 UID GID

    虽然我们登陆Linux时输入的是用户名，但其实Linux系统识别的不是用户名，识别的是用户名对应的ID, 而ID与账号的对应关系保存在 /etc/passwd 当中

### 用户账户

    Linux系统上面的用户登陆主机以取得shell的环境来工作时，它经过了哪些步骤呢？ 首先，它必须在计算机前面利用tty1~tty7的终端机提供的login接口，并输入账号与密码后才能够登陆，那输入了用户名和密码后，系统帮你处理了什么呢?
        1.先在 /etc/passwd 里面搜寻是否有你输入的账号，，如果没有则跳出，如果有的话将该账户对应的UID GID读出，另外，该账号的主文件夹与shell设置也一并读出
        2.核对密码表，这时候系统会进入 /etc/shadown 里面找出对应账号与UID，然后核对一下你刚才输入的密码与里面的密码是否相符
        3.如果一切ok就进入shell管控

>/etc/passwd 文件结构

```shell
root:x:0:0:root:/root:/bin/bash
bin:x:1:1:bin:/bin:/sbin/nologin
daemon:x:2:2:daemon:/sbin:/sbin/nologin
adm:x:3:4:adm:/var/adm:/sbin/nologin
```

        这个文件的构造为:每一行代表一个账号，有几行就代表有几个账号在你的系统中，特别注意：里面有很多账号本来就是系统正常运行所必须要要的所以这个文件不要去随意修改和删除
    UID的范围:
        0       系统管理员，当UID是0时，代表这个账号是“系统管理员”
        1-499   系统账号，保留给系统使用的ID
        500-65535 给一般用户使用的，新内核支持更大的ID
    GID
        这个与 /etc/group 文件有关，和 /etc/passwd 差不多，只是它是用来规定组名与GID的对应而已
    主文件夹
        如果想让账户的主文件夹移动到其他位置需要在里面更改
    shell
        用户登陆系统之后会取得一个shell来与系统内核建立通信，默认的shell就是最后那个字段指定的如果想让某个账号无法取得shell环境的登陆操作，那就可以把这个字段设置为 /sbin/nologin

>/etc/shadow 文件结构

``` C
root:密码段，存储的是加密的密码，为了方便我把它改成了文字::0:99999:7:::
bin:*:17834:0:99999:7:::
daemon:*:17834:0:99999:7:::
adm:*:17834:0:99999:7:::
```

    以上面的为例，我们可以看到，这个文件也是用引号(:)来作为分隔符，分成了9个字段，这9个字段的意义如下(从左到右排序)
    1.账户名称
    2.密码，这里存储的是加密过后的密文，基本不会被破解，但是仍然可能被暴力破解，所以 /etc/shadow 这个文件的权限一般设置为 000 只有root才能对其进行操作
    3.最近变动密码的日期 注意：Linux的时间是以1970/1/1 作为1而累加的日期
    4.密码不可被变动的天数
    5.密码需要重新更改的天数
    6.密码需要更改期限前的警告天数
    7.密码过期后账号的宽限时间
    8.账号失效日期
    9.保留字段

>root密码找回

        1.进入单用户维护模式，系统会主动给予root权限的bash接口，然后利用passwd修改密码即可
        2.以LiveCD开机后挂载系统根目录去修改 /etc/shadow 将里面的root密码字段清空就好了

### 有效与初始用户组：groups，newgrp

>/etc/group 文件结构

``` C
root:x:0:
bin:x:1:
daemon:x:2:
sys:x:3:
```

    这个文件就是记录GID与组名的对应，和 shadow 文件类似，也是以引号作为分隔符，共分为四列，每一字段的意义是：
    1.用户组名称
    2.用户组密码(密文保存在 /etc/gshadow 中)
    3.GID 用户组ID
    4.此用户组支持的账户名称(因为一个账户可以加入多个组)

>有效用户组与初始用户组

    每个用户在他的/etc/shadow 里面的第四列有个GID，这个GID指的是初始用户组。也就是说，当用户登陆系统，就拥有这个用户组的相关权限。初始用户组不需要在/etc/group 中额外设置，但是非初始用户组的其他用户组就不一样了，需要在用户组后面添加支持的账号名称

## 账户管理

>新增用户

    useradd [-u UID] [-g 初始用户组] [-G 次要用户组] [-m 强制创建主文件夹] [-d 指定主文件夹] username
    useradd 参考的文件: /etc/default/useradd 以测试机为例

```C
GROUP=100
HOME=/home
INACTIVE=-1
EXPIRE=
SHELL=/bin/bash
SKEL=/etc/skel
CREATE_MAIL_SPOOL=yes
```

    GROUP=100 新建账号的初始用户组GID为100，但是不同的发行版有不同的策略这个不一定
    HOME=/home 用户主文件夹的基准目录
    INACTIVE=-1：密码过期后是否会失效的设置值，-1表示永不失效
    EXPIRE= 账户失效日期
    SHELL=/bin/bash 默认使用的shell程序文件名
    SKEL=/etc/skel 用户主文件夹参考基准目录 这个就是指定用户主文件夹的参考记住目录
    CREATE_MAIL_SPOOL=yes 创建用户的mailbox

>UID GID 参考 /etc/login.defs,建议还是自己去看看这个文件

>passwd

    使用useradd创建了账号之后，在默认的情况下，这个账号是被封锁了的，也就是说无法登陆这时候就需要使用passwd为用户设置密码

    passwd [-luSnxwi] username (root 使用,普通用户只能passwd来改密码，没法设置其他的)
    -l : 锁定密码
    -u : 解锁密码
    -S : 列出密码相关参数
    -n : 密码不可修改天数
    -x : 多久内必须改动密码
    -w : 密码过期前的警告天数
    -i : 密码失效日期
    -e : 使账户密码失效，可用于第一次登陆系统时，强制让用户修改密码

>usermod 用于对账户微调

    有时候useradd之后，发现账户有些地方配置出错，这时候就可以使用usermod来微调账户
    usermod [-cdegGlsuLU] username
    -c : 后面接账户说明
    -d : 后面接账户主文件夹
    -e : 后面接日期(让账户失效 -1是让账户永不失效，0是让账户立即失效)
    -f : 后面接天数
    -g : 接初始用户组
    -G : 后面接次要用户组
    -a : 与-G合用可增加次要用户组的支持
    -l : 后面接账户名称，用来修改账户名称
    -s : 后面接Shell的实际文件
    -u : 后面接UID数字
    -L : 暂时将用户密码冻结(passwd -l 幻视)
    -U : 将 /etc/shadow 密码列的!去掉(解锁密码，允许用户登陆)

>userdel 删除用户账户

    userdel [-r] username 删除用户， -r参数表示联通用户主文件夹一起删除

## 用户功能

    不论是 useradd,usermod,还是userdel，那都是系统管理员所能用的命令，普通用户也可以自定义一些数据

>finger 可以用于查阅用户信息

    finger [-sm] username
    -s : 仅列出用户的账号，全名，终端机代号，登陆时间
    -m : 列出与后面接的账号相同者
    不过这个命令我测试的时候系统上面没有，需要手动安装，可能是觉着不怎么用了系统就没默认安装

>chfn 修改信息

    chfn [-foph] 账户名
    -f : 完整名字
    -o : 办公室房间号码
    -p : 办公室电话号码
    -h : 家里的电话号码

>chsh 修改登陆系统后默认的shell

    chsh [-ls]
    -l : 列出目前系统上可用的shell，其实就是 /etc/shells 的内容
    -s : 修改自己的shell

>id 查询某人或自己的UID/GID等信息

    id username
    其他还有啥参数请使用man id 查看

## 新增与删除用户组

>groupadd

    groupadd [-g gid] [-r] groupname
    -g : 接某个特定的GID，用来直接给予某个GID
    -r : 新建系统用户组。与 /etc/login.defs 内的GID_MIN有关

>groupmod

    groupmod [-g gid] [-n group_name] group_name
    -g : 修改既有的GID数字
    -n : 修改既有的组名

>groupdel

    groupdel [groupname]

>gpasswd : 用户组管理员功能

    gpasswd [-AMrR] groupname
    无参数 : 给予groupname 一个密码
    -A : 将groupname 的主控权交由后面的用户(改组组长)
    -M : 将某些账号加入这个用户组中 (修改/etc/gshadow最后一个字段)
    -r : 删除指定groupname的密码
    -R : 让groupname的密码栏失效

## ACL的使用

>1.什么是ACL

    ACL是Access Control List 的缩写，主要提供传统的owner,group,others的read,weite,execute 权限之外的具体权限设置。ACL可以针对单一用户，单一文件或目录来进行r，w，x的权限设置，ACL主要可以针对一下几个项目来设置:
        用户 (user)        : 可以针对用户来设置权限
        用户组 (group)     : 针对用户组来设置权限
        默认属性 (mask)    : 设置在改目录下新建文件/目录时设置新数据的默认权限

>2.如何启动ACL

    ACL是传统UNIX-like 操作系统权限的额外支持项目，因此要使用ACL必须要有文件系统的支持，一般默认是支持ACL的(但是在我的测试机上面无法查询ACL支持，应该是我安装时出现的问题)

>3.ACl的设置技巧：getfcal，setfacl

    getfacl：取得某个文件/目录的ACL设置项目
    setfacl：设置某个目录/文件的ACl

>setfacl的用法

    setfacl [-bkRd] [{-m|-x} acl 参数] 目标文件名
    参数:
        -m : 设置后续的acl参数给文件使用，不能与-x合用
        -x : 删除后续的acl参数，不可以与-m合用
        -b : 删除所有的ACL设置参数
        -R : 递归设置ACL
        -d : 设置默认ACL参数，只针对目录，在改目录新建的数据都会引用此默认值

>取得ACL设置信息,具体看书

    getfacl filename

>用户身份切换

    在linux中有以下三类账号
    管理员账号 : root 用于管理系统
    系统账号   : 用于执行某些任务
    用户账号   : 普通用户使用计算机资源的账号

* 一般情况下时使用一般账号登陆系统，主要时为了安全，避免执行某些操作将系统损坏，等到需要设置某些系统环境时，才会变换身份成为root来管理系统

* 用较低权限驱动系统服务: 为了系统安全，有些时候，我们必须要以某些系统账号来进行程序的执行，比如说我那个网站使用的apache，我们可以新建一个名为apache的用户来启动apache软件，如果这个程序被攻破，至少不会损坏系统

>su

    su是最简单的切换身份的命令，可以进行任何身份的切换。方法如下:
        su [-lm] [-c 命令] [username]
        - : 单纯使用 - 如" su - ",代表使用login-shell 的标量文件读取方式来登陆系统；
        -l : 与 - 类似，后面需加想切换的用户账号，也是login-shell的方式
        -m : -m与-p是一样的，表示使用目前的环境设置
        -c : 仅进行一次命令

>sudo

    为了保护root账户密码的安全，但有些时候又需要以root身份执行一些命令吗，这个时候sudo就派上了用场

* sudo的命令用法

    由于一开始系统默认仅有root可以执行sudo(ubuntu不是，这里是以centos为准)

> sudo命令的执行流程

* 1.当用户执行sudo时，系统会去 /etc/sudoers 文件中查找该用户是否有权限执行sudo

* 2.若用户具有可执行sudo的权限后，便让用户输入自己的密码来确认

* 3.若密码输入成功，便开始进行sudo后接的命令

* 4.若欲切换的身份与执行者身份相同,那也不需要输入命令

>配置sudo命令 visudo /etc/sudoers

    visud 其实就是用vi 打开/etc/udoers 修改这个文件但是由于 /etc/sudoers这个配置文件有自己的语法，如果直接改可能会出问题，所以用visudo 这条指令会在离开修改界面时检验 /etc/sudoers 文件语法

* 计入我们想让某个账号可以使用root的任何命令,那么可以像下面这么修改

```c
    //从左到右是:用户账号 登陆者的来源主机名=(可切换的身份) 可执行的命令
    root ALL=(ALL)          ALL
    username ALL=(ALL)      ALL
```

* 文件语法分析

    用户账号:系统的那个账号可以使用这个sudo 默认为root这个账号

    登陆者的来源主机名: 这个设置由哪台主机连接到本Linux主机

    可切换的身份:这个账号可以切换成什么身份来执行后续的命令

    可执行的命令：这里的命令必须使用绝对路径来编写，默认root可以切换任何身份且进行任何命令

    注意: ALL是个关键字，代表任何身份，主机或命令的意思

* 利用用户组以及免密码的功能处理visudo(建议使用这种方式)

    当以系统中由很多个用户，和多个用户组，我们想让某个用户组的用户可以管理系统改怎么做呢?

```c
// /etc/sudoers 文件里有下面这一行(wheel前的 % 表示这是一个用户组)
// 这句话的意思是 wheel用户组里面的用户可以使用sudo 命令，那么我们只需要把用户添加进wheel就行了嘛
    %wheel ALL=(ALL) ALL
```

```c
    usermod -a -G wheel username
```

## 用户的特殊shell 和PAM模块

* 特殊的shell,/sbin/nologin

    我们之前提到过系统账号，系统账号使用的shell就是 /sbin/nologin，重点在于系统账号是不需要登陆的，所以我们就给他这个无法登陆的合法shell，使用这个shell的用户即使有了密码，你想让他登陆时也无法登陆(无法登陆主机)

    另外,我们想让某个具有 /sbin/nologin 的用户知道，他们不能登陆主机时，我们可以配置 /etc/nologin.txt 这个文件，在这里面说明为什么不能登陆

* PAM模块简介