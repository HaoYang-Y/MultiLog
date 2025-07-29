#ifndef _LOGGER_H_
#define _LOGGER_H_

#include "log_stream.h"
#include <atomic>
#include <memory>
#include <vector>

namespace multilog {

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
} // namespace multilog

#define LOGTRACE                                                               \
  multilog::Logger::getInstance().log(multilog::LogLevel::TRACE, __FILE__,     \
                                      __LINE__)
#define LOGDEBUG                                                               \
  multilog::Logger::getInstance().log(multilog::LogLevel::DEBUG, __FILE__,     \
                                      __LINE__)
#define LOGINFO                                                                \
  multilog::Logger::getInstance().log(multilog::LogLevel::INFO, __FILE__,      \
                                      __LINE__)
#define LOGWARN                                                                \
  multilog::Logger::getInstance().log(multilog::LogLevel::WARNING, __FILE__,   \
                                      __LINE__)
#define LOGERROR                                                               \
  multilog::Logger::getInstance().log(multilog::LogLevel::ERROR, __FILE__,     \
                                      __LINE__)
#define LOGFATAL                                                               \
  multilog::Logger::getInstance().log(multilog::LogLevel::FATAL, __FILE__,     \
                                      __LINE__)
#define LOGCRIT                                                                \
  multilog::Logger::getInstance().log(multilog::LogLevel::CRITICAL, __FILE__,  \
                                      __LINE__)
#endif
