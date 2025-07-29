#include "logger.h"
#include "appender.h"
#include "appender_file.h"
#include "log_config.h"

namespace multi{
namespace log {

Logger &Logger::getInstance() {
  static Logger instance;
  return instance;
}

LogStream::LogStreamCommit Logger::log(LogLevel level, const char *file,
                                       int line) {
  thread_local LogStream log_stream(*this);
  if (level < level_) {
    log_stream.ignore();
  }
  return log_stream.log(level, file, line);
}

void Logger::append_to_buffer(LogEvent event) {
  for (auto &appender : appenders_) {
    appender->append(event);
  }
}
Logger::Logger() : level_(LogLevel::CRITICAL),appenders_() {
  appenders_.push_back(std::unique_ptr<AppenderFile>(new AppenderFile(50000)));
#ifdef LOGLEVEL
level_ = LogLevel::LOGLEVEL;
#endif
}
} // namespace log
} // namespace multilog
  /*
  TODO
  1. 日志级别 level_未初始化
  2. 未使用的成员变量 used_
  3. 日志级别判断的线程安全性
  log() 方法中通过 if (level < level_) 判断是否忽略日志，但 level_
  是普通成员变量，若在多线程环境下修改 level_（例如通过未来的 setLevel()
  方法），可能导致读取到不一致的值。
  4.Appender 管理的灵活性不足
当前 appenders_ 仅在构造函数中硬编码添加了 AppenderFile，用户无法动态添加 /
  移除输出目标（如控制台、网络等），缺乏灵活性。
  5.6. 日志宏定义的可扩展性
当前宏定义（LOGTRACE、LOGDEBUG 等）直接绑定到
  Logger::getInstance()，若未来需要支持多 Logger
  实例（而非单例），宏定义会难以修改。
  
建议：
保留现有宏的同时，提供更灵活的宏定义方式（可选）：
  
cpp
运行
// 保留原有宏，新增通用宏（支持自定义Logger）
#define LOG(logger, level) logger.log(level, __FILE__, __LINE__)
// 使用示例：LOG(myLogger, LogLevel::INFO) << "message";
6.单例模式的析构问题
单例 Logger 的析构会在程序退出时发生，此时 appenders_ 中的 Appender（如
  AppenderFile）可能需要执行资源清理（如刷新缓冲区、关闭文件）。需确保 Appender
  的析构函数能正确处理这些操作，避免资源泄漏。
  */