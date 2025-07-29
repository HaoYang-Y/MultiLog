#include "log_event.h"
namespace multilog {
LogEvent::LogEvent(multilog::LogLevel level) : level_(level), timestamp_() {}
void LogEvent::set_message(std::string message) { message_ = message; }
const std::string &LogEvent::get_message() const { return message_; }
LogLevel LogEvent::get_level() { return level_; }
} // namespace multilog