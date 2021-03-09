# Operating System 

[toc]

# C++中函数的说明及介绍

## 变量类型

### LPCWSTR

LPCWSTR是一个指向unicode编码字符串的32位指针，所指向字符串是wchar型，而不是char型



### STARTUPINFO

STARTUPINFO用于指定新进程的主窗口特性的一个结构。

```c++
typedef struct _STARTUPINFO {
    DWORD cb;
    LPTSTR lpReserved;
    LPTSTR lpDesktop;
    LPTSTR lpTitle;
    DWORD dwX;
    DWORD dwY;
    DWORD dwXSize;
    DWORD dwYSize;
    DWORD dwXCountChars;
    DWORD dwYCountChars;
    DWORD dwFillAttribute;
    DWORD dwFlags;
    WORD wShowWindow;
    WORD cbReserved2;
    LPBYTE lpReserved2;
    HANDLE hStdInput;
    HANDLE hStdOutput;
    HANDLE hStdError;
} STARTUPINFO, *LPSTARTUPINFO;
```

```
DWORD cb; //包含STARTUPINFO结构中的字节数.如果Microsoft将来扩展该结构,它可用作版本控制手段，应用程序必须将cb初始化为sizeof(STARTUPINFO)。

LPSTR lpReserved; //保留。必须初始化为NULL。

LPSTR lpDesktop; //用于标识启动应用程序所在的桌面的名字。如果该桌面存在，新进程便与指定的桌面相关联。如果桌面不存在，便创建一个带有默认属性的桌面，并使用为新进程指定的名字。如果lpDesktop是NULL（这是最常见的情况),那么该进程将与当前桌面相关联。

LPSTR lpTitle; //用于设定控制台窗口的名称。如果lpTitle是NULL，则可执行文件的名字将用作窗口名

DWORD dwX; //用于设定应用程序窗口在屏幕上应该放置的位置的x和y坐标（以像素为单位）。

DWORD dwY; 只有当子进程用CW_USEDEFAULT作为CreateWindow的x参数来创建它的第一个重叠窗口时,
才使用这两个坐标。若是创建控制台窗口的应用程序，这些成员用于指明控制台窗口的左上角

DWORD dwXSize; //用于设定应用程序窗口的宽度和长度（以像素为单位）只有dwYsize

DWORD dwYSize; 当子进程将CW_USEDEFAULT用作CreateWindow的nWidth参数来创建它的第一个重叠窗口时，才使用这些值。

DWORD dwXCountChars; //用于设定子应用程序的控制台窗口的宽度和高度（以字符为单位）

DWORD dwYCountChars;

DWORD dwFillAttribute; //用于设定子应用程序的控制台窗口使用的文本和背景颜色

DWORD dwFlags; //请参见下一段和表4 - 7 的说明

WORD wShowWindow; //用于设定如果子应用程序初次调用的ShowWindow将SW_SHOWDEFAULT作为nCmdShow参数传递时，该应用程序的第一个重叠窗口应该如何出现。

本成员可以是通常用于ShowWindow 函数的任何一个SW _ *标识符

WORD cbReserved2; //保留。必须被初始化为0

PBYTE lpReserved2; //保留。必须被初始化为NULL

HANDLE hStdInput; //用于设定供控制台输入和输出用的缓存的句柄。按照默认设置，hStdInput用于标识键盘缓存，hStdOutput和hStdError用于标识控制台窗口的缓存
```



### PROCESS_INFORMATION

创建进程时相关的数据结构之一，该结构返回有关新进程及其主线程的信息

```c++
typedef struct_PROCESS_INFORMATION{
HANDLE hProcess;
HANDLE hThread;
DWORD dwProcessId;
DWORD dwThreadId;
}PROCESS_INFORMATION;

其中成员含义如下。
① hProcess：返回新进程的句柄。
② hThread：返回主线程的句柄。
③ dwProcessId：返回一个全局进程标识符。该标识符用于标识一个进程。从进程被
创建到终止，该值始终有效。
④ dwThreadId：返回一个全局线程标识符。该标识符用于标识一个线程。从线程被创
建到终止，该值始终有效。
```



### HANDLE

在[程序设计](https://zh.wikipedia.org/wiki/程序设计)中，**句柄**（**handle**）是[Windows操作系统](https://zh.wikipedia.org/wiki/Windows操作系统)用来标识被应用程序所建立或使用的对象的整数。**其本质相当于带有引用计数的[智能指针](https://zh.wikipedia.org/wiki/智能指针)**。当一个[应用程序](https://zh.wikipedia.org/wiki/应用程序)要引用其他系统（如[数据库](https://zh.wikipedia.org/wiki/数据库)、[操作系统](https://zh.wikipedia.org/wiki/操作系统)）所管理的[内存](https://zh.wikipedia.org/wiki/内存)块或[对象](https://zh.wikipedia.org/wiki/对象_(计算机科学))时，可以使用句柄。



### LPVOID

**LPVOID是一个没有类型的指针**，也就是说你可以将LPVOID类型的[变量赋值](https://baike.baidu.com/item/变量赋值/23729660)给任意类型的指针，比如在参数传递时就可以把任意类型传递给一个LPVOID类型为参数的方法，然后在方法内再将这个“任意类型”从传递时的“LPVOID类型”转换回来。具体请看下面的示例程序，其中LPVOID lParam即为空类型指针，而CMyClass即为任意类型指针



## 函数/方法

### ZeroMemory

- 声明

  void ZeroMemory( PVOID Destination,SIZE_T Length );

- 参数

  Destination :指向一块准备用0来填充的内存区域的开始地址。

  Length :准备用0来填充的[内存](https://baike.baidu.com/item/内存/103614)区域的大小，按[字节](https://baike.baidu.com/item/字节)来计算。

- 返回值

  无

- 作用

  **ZeroMemory只是将指定的内存块清零**。

  使用结构前清零，而不让结构的成员数值具有不确定性，是一个好的编程习惯。



# 操作系统的功能和目标

![image-20210223185732441](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223185732441.png)

![image-20210223185857487](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223185857487.png)

操作系统的概念：

![image-20210223185933609](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223185933609.png)

![image-20210223190028292](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223190028292.png)

![image-20210223190106822](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223190106822.png)

![image-20210223190324900](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223190324900.png)

![image-20210223190445653](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223190445653.png)

![image-20210223191004470](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223191004470.png)

![image-20210223190522162](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223190522162.png)

联机命令接口实例（Windows）- 联机命令接口 = **交互式**命令接口，例如cmd

![image-20210223190740248](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223190740248.png)

![image-20210223190829190](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223190829190.png)

![image-20210223191108797](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223191108797.png)

![image-20210223191130211](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223191130211.png)

# 操作系统的四个特征

- 并发
- 共享
- 虚拟
- 异步

其中，**并发和共享是两个基本特征，二者互为存在条件**

## 并发 (Параллельные вычисления 并发计算)

并发：指的是**两个或多个事件**在同一时间**间隔**发生。这些事件**宏观上是同时发生**的，但**微观上是交替发生**的。

并行：并行指的是，两个或多个事件在**同一时刻同时发生**

并发计算：Параллельные вычисления - **concurrent computing**

并行计算：Параллельные вычислительные системы - **parallel computing**

![image-20210223191605582](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223191605582.png)

![image-20210223191807629](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223191807629.png)

## 共享

![image-20210223192002297](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223192002297.png)

 ## 并发和共享的关系

![image-20210223192204986](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223192204986.png)

## 虚拟

![image-20210223192449830](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223192449830.png)

![image-20210223192541488](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223192541488.png)

![image-20210223192645107](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223192645107.png)

## 异步

 ![image-20210223193154196](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223193154196.png)

![image-20210223193442962](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223193442962.png)

# 操作系统的发展和分类

![image-20210223193507746](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223193507746.png)

## 手工操作阶段

使用打孔机在纸袋上打孔（打孔表示1，不打代表0），再交由计算机处理

计算机处理完，再将结果通过打孔纸带机输出

暴露的缺点：用户独占全机、人机速度矛盾导致资源利用率极低

## 批初级阶段

### 单道批处理系统

![image-20210223194028277](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223194028277.png)

### 多道批处理系统

![image-20210223194305906](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223194305906.png)

![image-20210223194347979](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223194347979.png)

![image-20210223194514184](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223194514184.png)

## 分时操作系统

![image-20210223194647265](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223194647265.png)

## 实时操作体统

![image-20210223194759199](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223194759199.png)

## 其他几种操作体统

![image-20210223194835727](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223194835727.png)

## 总结

![image-20210223194918014](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223194918014.png)

# 操作系统的运行机制和体系结构

![image-20210223194950773](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223194950773.png)

## 指令

指令其实就是一个二进制文件（Linux中的bin）

![image-20210223195209807](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223195209807.png)

![image-20210223195312990](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223195312990.png)

![image-20210223195409518](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223195409518.png)

![image-20210223195505794](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223195505794.png)

![image-20210223195625161](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223195625161.png)

## 操作系统的内核

![image-20210223195758554](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223195758554.png)

![image-20210223195918517](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223195918517.png)

![image-20210223200006146](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223200006146.png)

![image-20210223200239732](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223200239732.png)

## 总结

![image-20210223200556571](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223200556571.png)

# 中断和异常

## 中断

![image-20210223200613337](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223200613337.png)

**中断机制，实现了多道程序并发执行**

本质：发生中断就意味着需要操作系统介入，开展管理工作

比如：

- 两个进程并行执行使用完各自的时间片时，就会引发操作系统中断，**操作系统由用户态转换为内核态，权限移交到操作体统**，操作系统完成进程之间的转换
- 某个用户进程发出**系统调用（内中断信号）**，请求输出。CPU切换为**核心态**，对中断进行处理
- 某个进程的I/O操作完成，也可以引发系统中断

![image-20210223201746485](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223201746485.png)

![image-20210223202013819](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223202013819.png)

**快速区分中断的类型：**

- 通过中断的来源
  - 内中断：中断来自于CPU内部
  - 外中断：中断来自于CPU外部（比如：I/O操作完成信号）

![image-20210223202325256](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223202325256.png)

![image-20210223202934108](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223202934108.png)

## 总结

![image-20210223203041065](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223203041065.png)

# 系统调用

![image-20210223203058346](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223203058346.png)

![image-20210223203156815](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223203156815.png)

![image-20210223204121593](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223204121593.png)

![image-20210223204339654](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223204339654.png)

## 系统调用和库函数的区别

库函数就是我们编程时候用的库

![image-20210223205020129](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223205020129.png)

## 系统调用背后的过程

![image-20210223205328635](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223205328635.png)

![image-20210223205343227](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223205343227.png)

![image-20210223205527497](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223205527497.png)

## 总结

![image-20210223205729005](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223205729005.png)

# 进程

![image-20210223221618912](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223221618912.png)

![image-20210223221715653](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223221715653.png)

![image-20210223221916291](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223221916291.png)

![image-20210223222110307](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223222110307.png)

![image-20210223222153923](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223222153923.png)

![image-20210223222329823](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223222329823.png)

![image-20210223222410072](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223222410072.png)

![image-20210223222508976](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223222508976.png)

![image-20210223222651387](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223222651387.png)

![image-20210223222716003](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223222716003.png)

![image-20210223222843247](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223222843247.png)

## 总结

![image-20210223223058356](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210223223058356.png)

## 进程的状态和转换

![image-20210302201254833](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210302201254833.png)

![image-20210302201450917](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210302201450917.png)

![image-20210302201737342](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210302201737342.png)

![image-20210302202315958](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210302202315958.png)

![image-20210302202329686](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210302202329686.png)

## 进程控制

![image-20210302205715657](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210302205715657.png)

![image-20210302205817901](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210302205817901.png)

![image-20210302210017897](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210302210017897.png)

![image-20210302210224048](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210302210224048.png)

![image-20210302210416894](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210302210416894.png)

![image-20210302210518482](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210302210518482.png)

![image-20210302210626800](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210302210626800.png)

![image-20210302210701999](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210302210701999.png)

![image-20210302210729171](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210302210729171.png)

## 进程通信

![image-20210302210743089](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210302210743089.png)

![image-20210302210938669](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210302210938669.png)

![image-20210302211119421](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210302211119421.png)

![image-20210302211333423](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210302211333423.png)

![image-20210302211558271](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210302211558271.png)

![image-20210302211642745](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210302211642745.png)

# 线程

![image-20210302225616050](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210302225616050.png)

![image-20210302225721748](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210302225721748.png)

![image-20210302225957875](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210302225957875.png)

![image-20210302230114869](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210302230114869.png)

![image-20210302230301583](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210302230301583.png)

![image-20210302230450192](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210302230450192.png)

- **在计算机中，透明指的是看不到，不透明指的是能看到。可以理解为 透明 == 隐形 == 看不到**

![image-20210302230814728](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210302230814728.png)

![image-20210302230948039](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210302230948039.png)

![image-20210302231722383](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210302231722383.png)

![image-20210302233039347](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210302233039347.png)

![image-20210302233147051](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210302233147051.png)

![image-20210302233229607](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210302233229607.png)

![image-20210302233725317](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210302233725317.png)

# 处理机调度

## 处理机调度的基本概念和层次

![image-20210306154403007](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210306154403007.png)

![image-20210306154557264](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210306154557264.png)

![image-20210306154704576](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210306154704576.png)

![image-20210306155015239](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210306155015239.png)

![image-20210306155222949](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210306155222949.png)

![image-20210306155334229](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210306155334229.png)

![image-20210306155529719](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210306155529719.png)

![image-20210306155627184](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210306155627184.png)

## 进程调度的时机切换与过程调度方式

![image-20210306160310821](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210306160310821.png)

![image-20210306160518722](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210306160518722.png)

![image-20210306161041786](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210306161041786.png)

![image-20210306161051919](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210306161051919.png)

![image-20210306161433412](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210306161433412.png)

![image-20210306161606132](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210306161606132.png)

![image-20210306161818629](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210306161818629.png)

![image-20210306161932623](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210306161932623.png)

## 调度算法的评价指标

![image-20210306162011723](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210306162011723.png)

![image-20210306162138991](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210306162138991.png)

![image-20210306162226926](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210306162226926.png)

![image-20210306162357184](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210306162357184.png)

![image-20210306162543847](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210306162543847.png)

![image-20210306162758781](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210306162758781.png)

![image-20210306162831876](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210306162831876.png)

![image-20210306162905075](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210306162905075.png)

## 调度算法

![image-20210308123701274](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308123701274.png)

![image-20210308124108536](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308124108536.png)

![image-20210308135051434](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308135051434.png)

![image-20210308135608174](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308135608174.png)

![image-20210308135836255](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308135836255.png)

![image-20210308140015369](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308140015369.png)

![image-20210308140509967](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308140509967.png)

![image-20210308140414676](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308140414676.png)

![image-20210308140532158](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308140532158.png)

![image-20210308140715141](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308140715141.png)

![image-20210308141821645](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308141821645.png)

![image-20210308142610114](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308142610114.png)

![image-20210308142535737](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308142535737.png)

![image-20210308142648369](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308142648369.png)

![image-20210308143113276](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308143113276.png)

![image-20210308143305537](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308143305537.png)

![image-20210308143457696](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308143457696.png)

# 进程同步、互斥

![image-20210308192538183](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308192538183.png)

![image-20210308193041381](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308193041381.png)

![image-20210308193209194](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308193209194.png)

![image-20210308194756929](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308194756929.png)![image-20210308194836303](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308194836303.png)

![image-20210308195239102](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308195239102.png)

![image-20210308195336651](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308195336651.png)

![image-20210308195723213](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308195723213.png)

![image-20210308195934960](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308195934960.png)

![image-20210308200348172](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308200348172.png)

![image-20210308200439632](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308200439632.png)

![image-20210308200534114](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308200534114.png)

![image-20210308200635179](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308200635179.png)

![image-20210308200725475](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308200725475.png)

## 进程互斥的硬件实现方法

![image-20210308200929616](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308200929616.png)

![image-20210308201313007](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308201313007.png)![image-20210308201505003](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308201505003.png)

## 信号机制

![image-20210308202504310](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308202504310.png)

![image-20210308202717299](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308202717299.png)

![image-20210308203331771](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308203331771.png)

![image-20210308203754576](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308203754576.png)

![image-20210308204206445](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308204206445.png)

![image-20210308204414409](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308204414409.png)

![image-20210308204503072](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308204503072.png)

## 信号量机制实现进程互斥

![image-20210308205604041](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308205604041.png)

![image-20210308205717733](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308205717733.png)

![image-20210308210236508](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308210236508.png)

![image-20210308210611305](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308210611305.png)

![image-20210308210737911](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210308210737911.png)

# 生产者-消费者问题

**临界资源：同一时间只能有一个进程能够访问的资源**

![image-20210309000752769](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210309000752769.png)

# 管程

![image-20210309001721157](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210309001721157.png)

![image-20210309001813561](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210309001813561.png)

![image-20210309002143828](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210309002143828.png)

![image-20210309002522896](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210309002522896.png)

![image-20210309002829385](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210309002829385.png)

![image-20210309002943471](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210309002943471.png)

![image-20210309003032545](C:\Users\mi\AppData\Roaming\Typora\typora-user-images\image-20210309003032545.png)

