#ifndef _TYPE_H_
#define _TYPE_H_
namespace multi{
  namespace log {
enum class LogLevel : int {
  TRACE = 0,
  DEBUG = 1,
  INFO = 2,
  WARNING = 3,
  ERROR = 4,
  FATAL = 5,
  CRITICAL = 6
};

const char* LogLevel_to_str(LogLevel level);
} // namespace log
}
#endif
/*
TODO
1. 命名空间改成MultiLog
2. 增加字符串映射功能
*/