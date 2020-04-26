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





数据结构

网络模型（epool模型、）

数据库

中间件（Nginx、zookeeper、zeromq、libevent、libev）

算法（分布式一致性hash）

系统架构（上下分层：接入层（gateway）、路由层（router、relay）、业务层（business）、数据层（datebase））研究下，面试好装逼使用

线程协程

同步异步（对于回调函数而言）

阻塞非阻塞（对于内核而言）

微服务

处理问题的复盘总结（1.分析问题 2.定位排查问题能力。）



