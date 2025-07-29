#include "log_type.h"

namespace multi{
 namespace log {
    const char* LogLevel_to_str(LogLevel level){
  switch (level) {
  case LogLevel::TRACE:
    return "TRACE";
  case LogLevel::DEBUG:
    return "DEBUG";
  case LogLevel::INFO:
    return "INFO";
  case LogLevel::WARNING:
    return "WARNING";
  case LogLevel::ERROR:
    return "ERROR";
  case LogLevel::FATAL:
  return "FATAL";
  case LogLevel::CRITICAL:
    return "CRITICAL";
  default:
    return "unknown";
  }
}
} // namespace log
}