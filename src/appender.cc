#include "appender.h"

namespace multi{
 namespace log {
Appender::Appender(size_t size) : size_(size),is_running_(true) {}
Appender::~Appender() {}
void Appender::append(LogEvent event) {
  std::lock_guard<std::mutex> lock(mutex_);
  event_queue_.push_back(event);
  if (event_queue_.size() >= size_) {
    cv_.notify_one();
  }
}
} // namespace log
} // namespace multilog
