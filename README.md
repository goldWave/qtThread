----------
*Qt 使用多线程主要存在 下面几种方法*
1. 继承`QRunnable`类 并重写 `run()` 方法
2. 继承`QThread`类 并重写 `run()` 方法
3. 继承`QObject`类作为工作类，创建临时`QThread`，使用`moveToThread()` 来将`QObject`整体移入子线程
4. `QtConcurrent` 类直接在子线程调用 方法或 `lambda`表达式

下面就主要针对上面4种情况进行代码 demo。

根据实际情况 **方法3**和**方法4**是比较推荐的使用方法

------

更多详细信息请前往 [CSDN博客](https://blog.csdn.net/goldWave01/article/details/116303039)查看
