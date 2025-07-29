#include "logger.h"
#include <iostream>
// 基础功能测试
void basic_function_test() {
    std::cout << "=== 运行基础功能测试 ===" << std::endl;

    // 测试日志级别输出
    LOGTRACE << "跟踪信息：详细的调试内容";
    LOGDEBUG << "调试信息：变量x=100，y=3.14";
    LOGINFO  << "普通信息：程序启动完成，版本v1.0";
    LOGWARN  << "警告信息：内存使用率超过80%";
    LOGERROR << "错误信息：文件读取失败，错误码1001";
    LOGFATAL << "致命错误：数据库连接中断";
    LOGCRIT  << "紧急错误：系统即将崩溃，请立即处理";

    // 测试不同数据类型
    int int_val = -42;
    unsigned uint_val = 1000;
    long long ll_val = 9223372036854775807LL;
    float f_val = 1.234567f;
    double d_val = 3.141592653589793;
    const char* cstr_val = "C风格字符串";
    std::string str_val = "标准字符串对象";
    bool bool_val = true;

    LOGINFO << "测试数据类型输出：";
    LOGINFO << "  整数: " << int_val;
    LOGINFO << "  无符号整数: " << uint_val;
    LOGINFO << "  长整数: " << ll_val;
    LOGINFO << "  单精度浮点数: " << f_val;
    LOGINFO << "  双精度浮点数: " << d_val;
    LOGINFO << "  C字符串: " << cstr_val;
    LOGINFO << "  标准字符串: " << str_val;
    LOGINFO << "  布尔值: " << bool_val;

    // 测试日志上下文（文件和行号）
    LOGINFO << "这条日志应包含正确的文件路径和行号";

    std::cout << "=== 基础功能测试完成 ===" << std::endl;
}
int main(){
    basic_function_test();
}