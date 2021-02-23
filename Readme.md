# Operating System 

[toc]

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

## 并发

并发：指的是**两个或多个事件**在同一时间**间隔**发生。这些事件**宏观上是同时发生**的，但**微观上是交替发生**的。

并行：并行指的是，两个或多个事件在**同一时刻同时发生**

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