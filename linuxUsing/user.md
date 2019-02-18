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