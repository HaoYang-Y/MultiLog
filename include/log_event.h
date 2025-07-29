#ifndef _LOG_EVENT_H_
#define _LOG_EVENT_H_

#include "log_type.h"
#include <chrono>
#include <string>

namespace multi{
  namespace log {
class LogEvent {
public:
  LogEvent(multi::log::LogLevel level);
  void set_message(std::string message);
  const std::string &get_message() const;
  LogLevel get_level();

private:
  LogLevel level_;
  std::string message_;
  std::chrono::system_clock::time_point timestamp_;
};
} // namespace log
} // namespace multilog
#endif
/*
TODO
1. 时间戳未正确初始化和缺少访问接口
2.
*/