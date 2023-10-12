# 东南大学数据结构与算法实践 Project 2
## 项目结构
* .vscode 中是个人的vscode配置文件，可忽略
*  exe 中存放着可执行文件 （FinalTest.exe）
*  header中存放着所有的.hpp文件
*  source中存放着所有的.cpp文件
## 附加说明
* 所有的.hpp都是对应.cpp的头文件 声明在.hpp中 定义在.cpp中
* Buffer.cpp 是自定义Buffer数据结构 有判满 判空 以及 判断当前MergeLoction
* BufferBoundery.cpp 是Buffer需读取文件的位置信息，包含从文件的哪一位置开始读，从哪一位置结束读，以及当前读到了哪一位置
* FileOperator.cpp 封装着服务与Buffer 以及 文件之间数据传输以及 其它有关文件操作的函数
* Timer.cpp 是自己封装的chrono 计时器
* FinalTest.cpp 是程序入口，输入 k(Merge ways) 和 m(num of Initial runs) 进行测试
## 使用说明
* 首先运行DataProducer.py 随机生成一定量数据的数据并写入到文件中
* 然后你就可以运行FinalTest.cpp 自己输入 k 以及 m 进行测试了
## 补充说明
* 本次实验的重心是对外部排序性能的模拟，所以在实验时仅考虑了特定情况，对于复杂情况并没有做处理。
* 测试数据应满足: 
$$dataSize\mod m=0 $$
$$log_k m 应为整数$$
当然也可以动态追踪 解决复杂情况 因时间限制 本项目并未实现 
* 输入数据在 Input.txt中，最终排序好的数据在 Output.txt 中