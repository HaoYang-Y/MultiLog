#ifndef _LOGGER_H_
#define _LOGGER_H_

#include "log_stream.h"
#include <atomic>
#include <memory>
#include <vector>

namespace multi{
 namespace log {

class LogEvent;
class Appender;

class Logger {
public:
  Logger(const Logger &) = delete;
  Logger(Logger &&) = delete;
  Logger &operator=(const Logger &) = delete;
  Logger &operator=(Logger &&) = delete;

  static Logger &getInstance();

  LogStream::LogStreamCommit log(LogLevel level, const char *file, int line);
  void append_to_buffer(LogEvent event);

private:
  Logger();

private:
  // std::atomic<bool> used_;
  LogLevel level_;
  std::vector<std::unique_ptr<Appender>> appenders_;
};
} // namespace log
} // namespace multilog

#define LOGTRACE                                                               \
  multi::log::Logger::getInstance().log(multi::log::LogLevel::TRACE, __FILE__,     \
                                      __LINE__)
#define LOGDEBUG                                                               \
  multi::log::Logger::getInstance().log(multi::log::LogLevel::DEBUG, __FILE__,     \
                                      __LINE__)
#define LOGINFO                                                                \
  multi::log::Logger::getInstance().log(multi::log::LogLevel::INFO, __FILE__,      \
                                      __LINE__)
#define LOGWARN                                                                \
  multi::log::Logger::getInstance().log(multi::log::LogLevel::WARNING, __FILE__,   \
                                      __LINE__)
#define LOGERROR                                                               \
  multi::log::Logger::getInstance().log(multi::log::LogLevel::ERROR, __FILE__,     \
                                      __LINE__)
#define LOGFATAL                                                               \
  multi::log::Logger::getInstance().log(multi::log::LogLevel::FATAL, __FILE__,     \
                                      __LINE__)
#define LOGCRIT                                                                \
  multi::log::Logger::getInstance().log(multi::log::LogLevel::CRITICAL, __FILE__,  \
                                      __LINE__)
#endif
