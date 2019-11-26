# Logger_v1
## 设计说明
初步实现一个能够满足基本条件的日志的工具库。
- 有效整合：只需要一个头文件
- 提供了不同颜色的终端输出，支持UTF-8编码的文件输出。
![image](https://s2.ax1x.com/2019/11/26/QS4WVJ.png)
- 堆栈跟踪：堆栈跟踪会显示一个方法列表，这些方法表示测试运行期间的执行链。显示在堆栈跟踪底部的方法是测试运行期间遇到的第一种方法，通常为测试方法本身。
- 格式化输出：支持格式化字符串的参数

## 日志级别：
- 调试：HSTLOG_LEVEL_DEBUG
- 信息: HSTLOG_LEVEL_INFO
- 警告: HSTLOG_LEVEL_WARNING
- 错误: HSTLOG_LEVEL_ERROR
- 严重: HSTLOG_LEVEL_FATAL
- 未知: HSTLOG_LEVEL_UNKOWN
