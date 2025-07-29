#include "appender_file.h"
#include <iostream>

namespace multi{
 namespace log {
AppenderFile::AppenderFile(size_t size) : Appender(size), is_sync(true) {
  ofs_.open(file, std::ios::app);
  if (!ofs_.is_open()) {
    std::cerr << file << "open fial:" << errno << "\n";
    return;
  }
  thread_ = std::thread(&AppenderFile::run, this);
}

AppenderFile::~AppenderFile() {
  is_running_ = false;
  cv_.notify_one();
  if (thread_.joinable()) {
    thread_.join();
  }
  ofs_.close();
}

void AppenderFile::write(std::vector<LogEvent> &event_queue) {
  for(auto& event : event_queue){
    ofs_ << event.get_message();
  }
  ofs_.flush();
  return;
}
void AppenderFile::run() {
  while (is_running_) {
    std::unique_lock<std::mutex> lock(mutex_);

    cv_.wait(lock,
             [this]() { return !is_running_ || event_queue_.size() >= size_; });
    if (!is_running_ && event_queue_.empty()) {
      break;
    }
    std::vector<LogEvent> queue;
    queue.reserve(size_);
    std::swap(queue, event_queue_);
    lock.unlock();
    write(queue);
  }
  return;
}
} // namespace log
} // namespace multilog