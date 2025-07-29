#ifndef _LOG_STREAM_H_
#define _LOG_STREAM_H_

#include "log_event.h"
#include "log_type.h"
#include "log_utils.h"

#include <cstring>
#include <sstream>

namespace multilog {
class Logger;
class LogStream {
public:
  class LogStreamCommit {
  public:
    LogStreamCommit(LogStream *log_stream, LogLevel level, const char *file,
                    int line);
    LogStreamCommit();
    ~LogStreamCommit();
    template <typename T> LogStreamCommit &operator<<(T t) {
      if (log_stream_) {
        log_stream_->append(t);
      }
      return *this;
    }

  private:
    LogStream *log_stream_;
    LogLevel level_;
  };
  LogStream() = delete;
  LogStream(const LogStream &) = delete;
  LogStream(LogStream &&) = delete;
  LogStream &operator=(const LogStream &) = delete;
  LogStream &operator=(LogStream &&) = delete;

  LogStream(Logger &logger);
  ~LogStream();

  static LogStreamCommit ignore();

  LogStreamCommit log(LogLevel level, const char *file, int line);

  void append(const char *t);
  void append(const std::string &t);
  template <typename T> void append(const T &t) {
    const char *fmt = format_specifier<T>();
    // 检查是否为未特化类型（匹配默认格式符）
    if (strcmp(fmt, "unknow") == 0) {
      // 输出占位符，避免格式不匹配导致崩溃
      append("<unknown type>");
      return;
    }

    if (use_heap()) {
      heap_buf_ += std::to_string(t);
      return;
    }
    int write_num = snprintf(stack_buf_ + stack_len_, STACK_MAX - stack_len_,
                             format_specifier<T>(), t);
    if (write_num > 0 && write_num + stack_len_ < STACK_MAX) {
      stack_len_ += write_num;
      return;
    }
    heap_buf_.assign(stack_buf_, stack_len_);
    stack_len_ = STACK_MAX;
    heap_buf_.append(std::to_string(t));
    return;
    // buffer_ << t;
  }

  void clear(LogLevel level);

private:
  bool use_heap() const;

private:
  static constexpr size_t STACK_MAX = 1024;
  Logger &logger_;
  // std::ostringstream buffer_;
  char stack_buf_[STACK_MAX];
  size_t stack_len_;
  std::string heap_buf_;
};
} // namespace multilog

#endif
/*
TODO
1. 未初始化 stack_len_ 成员变量
2. append(const char* t) 中未处理 t 为 nullptr 的情况，snprintf 遇到 nullptr
3. 可能导致未定义行为，需补充判断： tack_buf_ 未初始化，首次使用时若直接复制
stack_buf_ 到 heap_buf_，可能包含垃圾数据（虽然 stack_len_
控制了有效长度，但未初始化的内存可能有意外值）。建议在构造函数中对 stack_buf_
清零：memset(stack_buf_, 0, STACK_MAX);

*/