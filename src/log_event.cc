#include "log_event.h"
namespace multi{
namespace log {
LogEvent::LogEvent(LogLevel level) : level_(level), timestamp_() {}
void LogEvent::set_message(std::string message) { message_ = message; }
const std::string &LogEvent::get_message() const { return message_; }
LogLevel LogEvent::get_level() { return level_; }
} // namespace log
} // namespace multilog