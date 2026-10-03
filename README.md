# ADTProject

项目包含一组基于现代 C++（模板 + 智能指针）实现的基础数据结构（抽象数据类型，ADT），用于学习与实验：顺序表、链表、双向链表、栈、队列、循环队列以及复数类型等。

特性
- 以模板与宏封装的ADT实现，风格统一，便于教学演示
- 使用 std::unique_ptr 管理内存，减少手动释放错误
- 提供遍历与基本操作（增删查改、排序、查找等）

主要文件
- ADTHelper.h：公共宏、工具与类型别名定义（ADTBEGIN/ADTEND、ASSIGNxxx 等）
- ADTComplex.h / ADTComplex.cpp：复数类型与相关运算
- ADTList.h：单链表实现（带排序、遍历、插入、删除等）
- ADTSqList.h：顺序表（动态数组）实现
- ADTDuexList.h：双向链表实现
- ADTStack.h：顺序栈（基于动态数组）实现
- ADTListQueue.h：链式队列实现
- ADTCircleQueue.h：循环队列实现
- ADTProject.cpp：示例程序，演示栈的基本用法
- ADTProject.vcxproj：Visual Studio 工程文件

依赖与要求
- Windows / Visual Studio（建议 2019 或 2022）或能编译 MSVC 项目的工具链
- C++11 及以上（代码使用了 std::unique_ptr 与模板）

构建与运行
1. 使用 Visual Studio 打开 ADTProject.vcxproj，然后编译并运行。
2. 使用 MSBuild（命令行）编译：
   - msbuild ADTProject.vcxproj /p:Configuration=Release

配置
- 默认缓冲/数组大小由宏 ADTMAXSIZE 定义（默认值为 10），可在编译前通过宏重定义调整，例如在工程编译选项中添加预处理宏：ADTMAXSIZE=100

示例（参考 ADTProject.cpp）

```cpp
#include <iostream>
#include "ADTStack.h"
using namespace ADT::ADTStack;

int main() {
	SqStack<int> S;
	InitSqStack(S);
	for (int i = 0; i < 10; ++i) PushStack(S, i);
	TranverseSqStack(S, [](auto v){ std::cout << v << '\n'; });
	int pad = 0; 
	for (int i = 0; i < 3; ++i) PopStack(S, pad);
	TranverseSqStack(S, [](auto v){ std::cout << v << '\n'; });
}
```

贡献
- 欢迎提交 issue 或 pull request。请保持实现风格一致，优先使用 std::unique_ptr 管理资源。

许可
- 当前仓库未包含许可证文件。如需开源发布，请在仓库根目录添加 LICENSE。
