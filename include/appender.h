#ifndef _APPENDER_H_
#define _APPENDER_H_

#include "log_event.h"
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <vector>
#include <thread>

namespace multi{
namespace log {
class Appender {
public:
  Appender(size_t size);
  void append(LogEvent event);
  virtual ~Appender();

protected:
  virtual void write(std::vector<LogEvent> &event_queue) = 0;
  virtual void run() = 0;

private:

protected:
  std::vector<LogEvent> event_queue_;
  size_t size_;
  std::mutex mutex_;
  std::condition_variable cv_;
  std::thread thread_;
  std::atomic<bool> is_running_;

private:
};
} // namespace log
} // namespace multilog
/*
1. 成员变量初始化顺序错误
C++ 中成员变量的初始化顺序由 类中声明的顺序
决定，而非构造函数初始化列表的顺序。Appender 中成员声明顺序为：
*/

#endif