## 后台知识复习整理

### 1.paxos一致性算法

在一个分布式系统中，由于节点故障、网络延迟等各种原因，根据CAP理论，我们只能保证**一致性（Consistency）、可用性（Availability）、分区容错性（Partition Tolerance）** 中的两个。

![图1](https://user-gold-cdn.xitu.io/2019/4/12/16a0fa27901a1597?imageView2/0/w/1280/h/960/format/webp/ignore-error/1)

一致性问题，可以根据是否存在恶意节点分类两类。无恶意节点，是指节点会丢失、重发、不响应消息，但不会篡改消息。而恶意节点可能会篡改消息。有恶意节点的问题称为拜占庭将军问题，不在今天的讨论范围。Paxos很好地解决了无恶意节点的分布式一致性问题。



分布式一致性与共识算法：https://draveness.me/consensus





### 2.幂等问题

在计算机网络中，对于多次请求得到的结果跟一次请求产生的结果一样，不会产生多个副本，称之为幂等。





### 3.双花

双花又称 双重支付（double pay）。



### 4.旁路路由模式与代理路由模式

旁路路由：通过请求一个服务注册发现服务，发现服务返回真正server的IP+Port信息返回给client。如：zookeeper

代理路由：通过将信息发送给一个路由服务，由它进行路由规则发送到指定的server进行交易。





### 5.C++模板类编译问题

在C++中。编译器在看到模板的定义的时候。并不马上产生代码，仅仅有在看到用到模板时，比方调用了模板函数 或者 定义了类模板的对象的时候。编译器才产生特定类型的代码。



一般而言，在调用函数的时候，仅仅须要知道函数的声明就可以；

在定义类的对象时，仅仅须要知道类的定义，不须要成员函数的定义。



**可是，这对于模板编译是不奏效的。模板要进行实例化，则必须可以訪问定义模板的源码。当调用函数模板以及类模板的成员函数的时候，须要知道函数的定义。**





### 6.C++中 begin()与cbegin()区别

begin是迭代器指针开始位置。

cbegin()是C++11中返回一个const的迭代器,不能用于修改元素。





### 7.C++异常类

C++异常提供了一种转移程序控制权的方式。C++ 异常处理涉及到三个关键字：**try、catch、throw**。

- **throw:** 当问题出现时，程序会抛出一个异常。这是通过使用 **throw** 关键字来完成的。
- **catch:** 在您想要处理问题的地方，通过异常处理程序捕获异常。**catch** 关键字用于捕获异常。
- **try:** **try** 块中的代码标识将被激活的特定异常。它后面通常跟着一个或多个 catch 块。

```c++
try
{
   // 保护代码
}catch( ExceptionName e1 )
{
   // catch 块
}catch( ExceptionName e2 )
{
   // catch 块
}catch( ExceptionName eN )
{
   // catch 块
}
```

C++ 提供了一系列标准的异常，定义在 <exception> 中。

可以通过继承和重载 **exception** 类来定义新的异常。下面的实例演示了如何使用 std::exception 类来实现自己的异常：

```c++
#include <iostream>
#include <exception>
using namespace std;
 
struct MyException : public exception
{
  const char * what () const throw ()
  {
    return "C++ Exception";
  }
};
 
int main()
{
  try
  {
    throw MyException();
  }
  catch(MyException& e)
  {
    std::cout << "MyException caught" << std::endl;
    std::cout << e.what() << std::endl;
  }
  catch(std::exception& e)
  {
    //其他的错误
  }
}
```





### 8.map中插入insert与[]区别

inser(pair<int,string>(1,"one"));

insert(make_pair(1,"one"));

如果键存在，insert不会更新value，而是跳过。[]则会对有key进行更新value，没有对应的key则进行插入。



### 9.assert用法

ASSERT ()是一个调试程序时经常使用的宏，在程序运行时它计算括号内的表达式，如果表达式为FALSE (0), 程序将报告错误，并终止执行。如果表达式不为0，则继续执行后面的语句。这个宏通常原来判断程序中是否出现了明显非法的数据，如果出现了终止程序以免导致严重后果，同时也便于查找错误。

ASSERT 只有在 Debug 版本中才有效，如果编译为 Release 版本则被忽略。





### 10.负载均衡的几种方案

​	轮询式、

```c++
vector<Server*> vecServer;
while(1)
{
    Server* server = vecServer[curIndex % vecServer.size()];
    curIndex ++;
}
```

如上代码，一个简单的轮询式分配方法，这种方法简单，cpu计算少，缺点是无法动态判断server的状态，当一台server挂掉，会至少1/vecServer.size()的请求。这种分配方法有个bug,就是当每次请求结束就释放内存，那么curindex永远都是会是0，即每次请求第一个server.

   定死权重式、

这种方案适用于那种需要实现就规定后端server的权重，比如A比B server的响应速度快，我们希望A接受的请求比B多。

```c++
//假设A,B,C server权重分别为10 5 2
typedef struct _serverinfo
{
	//server指针
    Server *server;
    //权重
    int weight；

}ServerInfo;
vector<ServerInfo *> vecServer;
vecServer.push_back(A);
vecServer.push_back(B);
vecServer.push_back(C);

vector<int> vecWeight;
for(unsigned i = 0; i<vecServer.size();i++)
{
    vecWeight.insert(vecWeight.end(),vecServer[i]->weight,i);
    
}
while(1)
{
    index = vecWeight[random() % vecWeight.size()];
    Server *server = vecServer[index].server;
}
```

上面的代码比较好理解，一共有两个数组，一个是server信息数组vecServer,一个是权重数组vecWeight。在分配server时，先通过权重数组vecWeight获取到server信息数组的下标，然后分配server。

这样做的cpu消耗也不高，但是缺点也是显而易见，就是还是没有办法动态调整权重，需要人为去修改。



动态调整权重

​	在讨论前，我们要明确几个希望使用它的原因：

```
1.我们希望server能够自动按照运行状态进行按照权重的选择
2.我们不希望手工去配置权重变化
```

很显然，我们需要一个基准来告诉我们这台server是否正常。这个基准是什么，是历史累计的平均值。比如如果是按照响应时间分配权重 ，那么就是所有后端server历史积累的平均响应时间，如果是错误率也是如此。

那么一旦调整了权重，我们什么时候来调整权重呢？调整比例是怎样的呢？按照我的经验，一般是隔一段固定时间才进行调整，如果正常但是权重过低，那么就按照20%的比例恢复；如果server不正常，那么直接按照当前server响应时间/历史平均响应时间进行降权。这里的逻辑之所以不一样是有原因的，因为服务出现问题的时候，我们能够知道这坏的程度有多少，就是当前server响应时间/历史平均响应时间进行降权；但是恢复的时候，你并不能保证server能够支撑多大的访问量，所以只能按照20%放量来试。也避免滚雪球效应的发生。

```c++
typedef struct _serverinfo
{
    unsigned _svr_ip;	//目标主机
    float    _cfg_wt;   //配置的权重
    float    _cur_wt;	//当前实际权重
    int		 _req_count;//请求数
    float    _rsp_time; //请求总响应时间
    float    _rsp_avg_time;//请求平均响应时间
    int      _rsp_error;	//请求错误数
}ServerInfo;

vector<ServerInfo *> vecServer;
int total_rsp_time = 0;
int total_req_count = 0;

unsigned int comWeight = 100;
unsigned int MaxWeight = 1000;
while(1)
{
    //按照文中第二种方式进行server分配
    serverInfo._req_count++;
    serverInfo._rsp_time+=rsp_time;
    
    total_req_count++;
    total_rsp_time += rsp_time;
    
    if(!需要重建权限)
    {
        continue；
    }
    
    float total_rsp_avg_time = (float)total_rsp_time / (float)total_req_count;
    for(vector<ServerInfo *>::iterator it = vecServer.begin();it!=vecServer.end();it++)
    {
        it->_rsp_avg_time = (float)it->_rsp_time / (float)it->_req_count;
        if(it->_rsp_avg_time > total_rsp_time)
        {
            it->_cur_wt = int(comWeight*total_rsp_avg_time / it->_rsp_avg_time);
        }
        else
        {
            it->_cur_wt *= 1.2;
        }
        it->_cur_wt = it->_cur_wt < MaxWeight ? it->_cur_wt : MaxWeight;
    }
    //按照第二种方法重建权重数组
}
```





### 11.分布式事务

 	 两阶段提交协议：第一个阶段，事务的发起方（协调者，只有一个）向所有参与者发送准备请求，事务的执行方（多个）进行资源检查，返回结果；若其中一个检查不通过，则事务进行终止；第二个阶段，协调者发起提交请求，参与者收到后，执行相应的提交操作。

​     为了保证第二个阶段，参与者一定能提交成功，一般需要在第一个阶段进行资源检查后，锁定相应数据，称为资源锁定。

三阶段提交协议：CanCommit阶段、PreCommit阶段、doCommit阶段。



### 12.读写分离

​	为了确保数据库产品的稳定性，很多数据库拥有双机热备功能。也就是第一台数据服务机为主机，对外提供

增删改业务的生产服务器，第二台数据服务机为备机，主要进行读的操作。



### 13.冷备/热备

   冷备：两个服务机，一台运行，一台不运行作为备份。这样一旦运行的服务器宕机,就把备份的服务器运行起来。冷备的方案比较容易实现，但是冷备的缺点是主机出现故障时备机不会自动接管，需要主动切换服务。

 热备：即是通常所说的active/standby方式，服务器数据包括数据库数据同时往两台或多台服务器写。当active服务器出现故障的时候，通过软件侦测（一般通过心跳诊断）将standby机器激活，保证应用再短时间内完全恢复正常使用。当一台服务器宕机后，自动切换到另一台备用机使用。

https://cloud.tencent.com/developer/news/316050



### 14.异地多活

​	https://www.cnblogs.com/jaychan/p/9242325.html



### 15.负载均衡（load balance）

​	https://www.cnblogs.com/xybaby/p/7867735.html



### 16.动静分离

​	https://blog.csdn.net/xuxiaopang0417/article/details/80003044



### 17.集群

 单台服务器的并发能力总是有限的，当单台服务器处理能力达到性能瓶颈的时候，将多台服务器组合起来提供服务，这种组合方式称之为集群。每个节点提供相同的服务。消除单点故障。



### 18.分布式

分布式系统就是将一个完整的系统按照业务功能拆分成很多独立的子系统，每个子系统就被称为“服务”，分布式系统将请求分拣和分发到不同的子系统，让不同的服务来处理不同的请求。分布式系统中，子系统独立运行，它们之间通过网络通信连接起来实现数据互通和组合服务。

### 19.CAP理论

​	一个分布式系统中，consistency（一致性）、Availability（可用性）、Partition Tolerance(分区容错性),不能同时成立。

一致性：它要求在用一时刻点，分布式系统中所有数据备份都相同或者处于同一状态。

可用性：在系统集群的一部分节点宕机后，系统依然能够正确的响应用户的请求。

分区容错性：系统能够容忍节点之间的网络通信故障。



显然分布式注定我们必然要进行分区，因此我们只能在一致性和可用性去作选择。

我们往往追求的是可用性，它的重要性比一致性要高，那么如何实现高可用，这里又有一个理论，就是base理论。

### 20.BASE理论

basically available（基本可用）

soft state(软状态)

eventually consistent（最终一致性）

BASE理论是对CAP中的中的一致性和可用性进行一个权衡的结果，理论核心思想就是：我们无法做到强一致，但每个应用都可以根据自身的业务特点，采用适当的方式来使系统达到最终一致性。

### 21.流量控制/拥塞控制

https://blog.csdn.net/dangzhangjing97/article/details/81008836

### 22.惊群效应

惊群就是多进程（多线程）正同时阻塞等待同一个事件的时候（休眠状态），如果等待的这个事件发生，那么他就会唤醒等待的所有进程（线程），但是最终却只可能有一个进程（线程）获得这个时间的“控制权”，对该事件进行处理，而其他进程获取控制权失败，只能重新进入休眠状态，这种现象和性能浪费就叫做惊群。

https://www.cnblogs.com/zafu/p/8251849.html

### 23.缓存穿透、击穿、雪崩

穿透：指查询一个不存在的数据，由于缓存是不命中时需要从数据库查询，查不到数据则不写入缓存，这将导致这个不存在的数据每次请求都要到数据库去查询，进而给数据库带来压力。



击穿：指热点key在某个时间点过期的时候，而恰好在这个时间点对这个key有大量的并发请求过来，从而大量的请求打到DB。



雪崩：指缓存中数据大批量到过期时间，而查询数据量巨大，引起数据库压力过大甚至down机。

与缓存击穿不同的是：存击穿是热点key失效；缓存雪崩是大量的key同时失效。

### 24.微服务

 https://www.jianshu.com/p/009d98e30b2a

### 25.服务发现

https://blog.csdn.net/u011714033/article/details/94395175

### 26.流量消峰

https://www.jianshu.com/p/6746140bbb76

### 27.服务限流

https://blog.csdn.net/jek123456/article/details/79901035

### 28.环境分类DEV/FAT/UAT/PRO

https://www.cnblogs.com/chengkanghua/p/10607239.html

### 29.灰度发布

灰度发布是指在升级版本过程中，通过分区控制，白名单控制等方式对一部分用户先升级产品特性，而其余用户则保持不变，当一段时间后产品特性的用户没人反馈问题，就逐步扩大范围，最终向所有用户开放新版本特性，灰度发布可以保证整体系统的稳定，在初始灰度的时候可以发现，修改问题，以保证其影响度。



数据结构



### 31.网络模型（epoll模型、）

epoll模型分为水平触发和边缘触发。边缘触发，它只告诉进程哪些fd刚刚变为就绪状态，并且只会通知一次。

**epoll****对文件描述符的操作有两种模式**：`LT``（level trigger）和ET（edge trigger）`。LT模式是默认模式，LT模式与ET模式的区别如下：

**1****）LT模式：**当epoll_wait检测到描述符事件发生并将此事件通知应用程序，`应用程序可以不立即处理该事件`。下次调用epoll_wait时，会再次响应应用程序并通知此事件。

**2****）ET模式：**当epoll_wait检测到描述符事件发生并将此事件通知应用程序，`应用程序必须立即处理该事件`。如果不处理，下次调用epoll_wait时，不会再次响应应用程序并通知此事件。

 

`**LT(level triggered)**``是缺省的工作方式，并且同时支持block和no-block socket`。在这种做法中，内核告诉你一个文件描述符是否就绪了，然后你可以对这个就绪的fd进行IO操作。`如果你不作任何操作，内核还是会继续通知你的`。

`　　**ET(edge-triggered)**是高速工作方式，只支持no-block socket`。在这种模式下，当描述符从未就绪变为就绪时，内核通过epoll告诉你。然后它会假设你知道文件描述符已经就绪，并且不会再为那个文件描述符发送更多的就绪通知，直到你做了某些操作导致那个文件描述符不再为就绪状态了(比如，你在发送，接收或者接收请求，或者发送接收的数据少于一定量时导致了一个EWOULDBLOCK 错误）。`但是请注意，如果一直不对这个fd作IO操作(从而导致它再次变成未就绪)，内核不会发送更多的通知(only once)`。

`ET``模式在很大程度上减少了epoll事件被重复触发的次数，因此效率要比LT模式高`。epoll工作在ET模式的时候，`必须使用非阻塞套接口`，以避免由于一个文件句柄的阻塞读/阻塞写操作把处理多个文件描述符的任务饿死。

 

**在select/poll中，**`进程只有在调用一定的方法后，内核才对所有监视的文件描述符进行扫描`，而epoll事先通过epoll_ctl()来注册一个文件描述符，`一旦基于某个文件描述符就绪时，内核会采用类似callback的回调机制`，迅速激活这个文件描述符，当进程调用epoll_wait()时便得到通知。(`此处去掉了遍历文件描述符，而是通过监听回调的的机制。这正是epoll的魅力所在。`)

**注意：**如果没有大量的idle-connection或者dead-connection，epoll的效率并不会比select/poll高很多，但是当遇到大量的idle-connection，就会发现epoll的效率大大高于select/poll。

https://blog.csdn.net/woxiaohahaa/article/details/51498951



32.分布式架构设计和中间件

**接入层**

- 反向代理
  - Nginx异步非阻塞IO密集型，适合做反向代理。Apache每个请求独占一个线程，适合做webserver。
  - webserver中间件：Nginx（c）、OpenResty（lua）、apache、Tomcat、jetty
- 负载均衡（一般互联网公司使用DNS做一级负载均衡，后端服务器用Nginx或者LVS等作为二级负载均衡。）
  - lvs:linux virtual server
  - F5:硬件设备
  - DNS:DNS服务商配置。多级缓存，更新慢
  - Nginx：自带多种负载均衡策略：轮询、最少连接、最少耗时、会话保持、权重
- 限流
  - 简单计数法
  - 滑动窗口法
  - 令牌桶算法
  - 漏桶算法
- 降级
- 熔断：快速失败，不会真正去请求外部资源。
- 超时
- 防雪崩

**逻辑层**

- 可扩展
  - 水平扩展（冗余部署，防单点）
  - 垂直扩展（提升处理能力，增加内存磁盘等）
- 隔离：避免单一业务占用全部资源；避免业务之间的相互影响。
- 解耦：剥离非核心业务。如用异步消息解耦
- RPC
- 同步、异步
- 消息队列
- 模块化

**数据层**

- 缓存

- 一致性

- 主从架构

- 唯一ID生成

- 一致性hash:确保在缓存服务器节点数量发生变化时大部分数据保持原地不动。

  





### 32.数据库

### 33.中间件（Nginx、zookeeper、zeromq、libevent、libev）

nginx:多进程，master+work。

zookeeper：分布式协调服务，包括服务注册发现，配置文件下发，分布式事务锁。节点叫做**Znode**，采用了**ZAB协议**，这种协议非常类似于一致性算法**Paxos**和**Raft**。

kafka：分布式消息系统，主要用于分布式日志收集等，raft协议。

etcd: 分布式高可用key-value数据库。用于服务发现，raft协议。，实现分布式系统数据的可用性和一致性。



算法（分布式一致性hash）

系统架构（上下分层：接入层（gateway）、路由层（router、relay）、业务层（business）、数据层（datebase））研究下，面试好装逼使用

线程协程

同步异步（对于回调函数而言）

阻塞非阻塞（对于内核而言）

微服务

处理问题的复盘总结（1.分析问题 2.定位排查问题能力。）



## 基础问答题

字节序：计算机硬件有两种储存数据的方式：大端字节序（big endian）和小端字节序（little endian）。就是大于一个字节类型的数据在内存中的存放顺序。

举例来说，数值`0x2211`使用两个字节储存：高位字节是`0x22`，低位字节是`0x11`。

> - 大端字节序：高位字节在前，低位字节在后，这是人类读写数值的方法。
> - 小端字节序：低位字节在前，高位字节在后，即以`0x1122`形式储存。

同理，`0x1234567`的大端字节序和小端字节序的写法如下图。

![img](http://www.ruanyifeng.com/blogimg/asset/2016/bg2016112201.gif)

为什么会有小端字节序？

答案是，计算机电路先处理低位字节，效率比较高，因为计算都是从低位开始的。所以，计算机的内部处理都是小端字节序。

但是，人类还是习惯读写大端字节序。所以，除了计算机的内部处理，其他的场合几乎都是大端字节序，比如网络传输和文件储存。

如果是大端字节序，先读到的就是高位字节，后读到的就是低位字节。小端字节序正好相反。

字节序的处理，就是一句话：

> "只有读取的时候，才必须区分字节序，其他情况都不用考虑。"

处理器读取外部数据的时候，必须知道数据的字节序，将其转成正确的值。然后，就正常使用这个值，完全不用再考虑字节序。

即使是向外部设备写入数据，也不用考虑字节序，正常写入一个值即可。外部设备会自己处理字节序的问题。



**字节序如何转换？？？**

​	在C++编程中，我们通过使用htonl、ntohl、htons、ntohs来进行转换的。





**为什么要字节对齐**

需要字节对齐的根本原因在于CPU访问数据的效率问题。



**可以让字节以1对齐么？**

可以， 但是不建议



**socket通信可以发1K的UDP数据包吗？TCP可以吗？**

UDP 包的大小就应该是 1500 - IP头(20) - UDP头(8) = 1472(Bytes)
TCP 包的大小就应该是 1500 - IP头(20) - TCP头(20) = 1460 (Bytes)

参考：https://blog.csdn.net/caoshangpa/article/details/51530685

可以，可以



**time_wait是什么？**

**TCP四次挥手的过程：**
[![wKioL1j4tHLgmHGJAAEh5DFpZvU805.png](https://s2.51cto.com/wyfs02/M01/91/DB/wKioL1j4tHLgmHGJAAEh5DFpZvU805.png)](https://s2.51cto.com/wyfs02/M01/91/DB/wKioL1j4tHLgmHGJAAEh5DFpZvU805.png)

TIME_WAIT: 表示收到了对方的FIN报文，并发送出了ACK报文，就等2MSL后即可回到CLOSED可用状态了。 如果FIN WAIT1状态下，收到了对方同时带FIN标志和ACK标志的报文时，可以直接进入到TIME_WAIT状态，而无须经过FIN_WAIT_2状态。 （主动方） CLOSED: 表示连接中断。

参考：https://blog.51cto.com/11859650/1917938



**TCP四次握手在哪一步骤真正断开了链接呢？**

![客户端主动关闭连接 —— TCP 四次挥手](https://cdn.jsdelivr.net/gh/xiaolincoder/ImageHost2/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/TCP-%E4%B8%89%E6%AC%A1%E6%8F%A1%E6%89%8B%E5%92%8C%E5%9B%9B%E6%AC%A1%E6%8C%A5%E6%89%8B/30.jpg)

- 服务器收到了 `ACK` 应答报文后，就进入了 `CLOSED` 状态，至此服务端已经完成连接的关闭。
- 客户端在经过 `2MSL` 一段时间后，自动进入 `CLOSED` 状态，至此客户端也完成连接的关闭。

强烈推荐参考：https://www.cnblogs.com/xiaolincoding/p/12638546.html



**为什么要创建索引呢？**这是因为，创建索引可以大大提高系统的性能。
第一，通过创建唯一性索引，可以保证数据库表中每一行数据的唯一性。
第二，可以大大加快 数据的检索速度，这也是创建索引的最主要的原因。
第三，可以加速表和表之间的连接，特别是在实现数据的参考完整性方面特别有意义。
第四，在使用分组和排序 子句进行数据检索时，同样可以显著减少查询中分组和排序的时间。
第五，通过使用索引，可以在查询的过程中，使用优化隐藏器，提高系统的性能。



**在浏览器输入[www.qq.com](http://www.qq.com/)，会打开[腾讯](https://www.nowcoder.com/jump/super-jump/word?word=腾讯)的首页，在这个操作中用了什么协议呢？经过了哪些步骤呢？**

链接：https://www.nowcoder.com/questionTerminal/f09d6db0077d4731ac5b34607d4431ee
来源：牛客网



**事件顺序**    

  (1) 浏览器获取输入的域名www.baidu.com 

  (2) 浏览器向DNS请求解析www.baidu.com的IP地址 

  (3) 域名系统DNS解析出百度服务器的IP地址 

  (4) 浏览器与该服务器建立TCP连接(默认端口号80) 

  (5) 浏览器发出HTTP请求，请求百度首页 

  (6) 服务器通过HTTP响应把首页文件发送给浏览器 

  (7) TCP连接释放 

  (8) 浏览器将首页文件进行解析，并将Web页显示给用户。 

​      **涉及到的协议**    

  (1) 应用层：HTTP(WWW访问协议)，DNS(域名解析服务) 

  (2) 传输层：TCP(为HTTP提供可靠的数据传输)，UDP(DNS使用UDP传输) 

  (3)      网络层：IP(IP数据数据包传输和路由选择)，ICMP(提供网络传输过程中的差错检测)，ARP(将本机的默认网关IP地址映射成物理MAC地址)



**两个浮点数如何比较大小？**

精度由计算过程中需求而定。比如一个常用的精度为1e-6.也就是0.000001.
所以对于两个浮点数a,b，如果要比较大小，那么常常会设置一个精度
如果fabs(a-b)<=1e-6，那么就是相等了。 fabs是求浮点数绝对值的函数。
类似的 判断大于的时候，就是if(a>b && fabs(a-b)>1e-6)。

判断小于的时候，就是if(a<b&&fabs(a-b)>1e-6)。



**C++腾讯后台开发工程师社招面经**

https://www.cnblogs.com/kks170716/p/9302105.html



**char arr[20]和char \*p = new char[20]的区别？初始化和未初始化的情况？放在内存的那个位置？**

　　char arr[20]定义的字符数组未初始化，存放在未初始化数据区（如果使用static关键字修饰，则会使用'\0'进行初始化，存放在静态数据区）

　　char *p = new char[20]定义的字符数组使用'\0'进行初始化，存放在堆中

　　**![img](https://images2018.cnblogs.com/blog/1200754/201807/1200754-20180721223500627-704600812.png)**

**C++内存分配有哪几种方式？画出C++内存布局图？**

　　（1）由new/malloc()在堆上分配空间，需要手动释放

　　（2）由系统在栈上分配空间，比如函数调用的参数信息等，不需要手动的释放

　　（3）在静态存储区分配空间，如staic变量

**![img](https://images2018.cnblogs.com/blog/1200754/201807/1200754-20180721172743898-2122024533.png)**



**整数、指针、布尔变量、浮点数值如何与0比较大小？**

https://developer.aliyun.com/article/570327



**已知进程名，使用命令查看当前进程打开的文件句柄？**

通过某个进程号显示该进行打开的文件

lsof -p 1

列出多个进程号对应的文件信息

lsof -p 123,456,789



lsof的用法：https://blog.csdn.net/kozazyh/article/details/5495532



**如何调试coredump文件？**

https://www.cnblogs.com/lysuns/articles/4311810.html