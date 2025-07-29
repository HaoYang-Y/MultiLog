#include "log_stream.h"
#include "log_event.h"
#include "logger.h"
#include <string>
#include <cstdio>

namespace multilog {
LogStream::LogStream(multilog::Logger &logger) : logger_(logger) {}

LogStream::~LogStream() {}
LogStream::LogStreamCommit LogStream::ignore() {
  return LogStream::LogStreamCommit();
}
LogStream::LogStreamCommit LogStream::log(LogLevel level, const char *file,
                                          int line) {
  return LogStream::LogStreamCommit(this, level, file, line);
}

void LogStream::append(const char *t) {
  if (use_heap()) {
    heap_buf_.append(t);
    return;
  }
  int write_num = snprintf(stack_buf_ + stack_len_, STACK_MAX - stack_len_,
                           format_specifier<const char *>(), t);
  if (write_num > 0 && write_num + stack_len_ < STACK_MAX) {
    stack_len_ += write_num;
    return;
  }
  heap_buf_.assign(stack_buf_, stack_len_);
  stack_len_ = STACK_MAX;
  memset(stack_buf_, 0, STACK_MAX);
  heap_buf_.append(t);
  return;
}

void LogStream::append(const std::string &t) {
  if (use_heap()) {
    heap_buf_.append(t);
    return;
  }
  int write_num = snprintf(stack_buf_ + stack_len_, STACK_MAX - stack_len_,
                           format_specifier<const char *>(), t.c_str());
  if (write_num > 0 && write_num + stack_len_ < STACK_MAX) {
    stack_len_ += write_num;
    return;
  }
  heap_buf_.assign(stack_buf_, stack_len_);
  stack_len_ = STACK_MAX;
  heap_buf_.append(t);
  return;
}

void LogStream::clear(LogLevel level) {
  //创建一个logevent
  LogEvent event(level);
  if (use_heap()) {
    event.set_message(heap_buf_);
  } else {
    event.set_message(std::string(stack_buf_, stack_len_));
  }
  logger_.append_to_buffer(event);
  stack_len_ = 0;
  heap_buf_.clear();
}

bool LogStream::use_heap() const { return stack_len_ == STACK_MAX; }

LogStream::LogStreamCommit::LogStreamCommit() : log_stream_(nullptr) {}
LogStream::LogStreamCommit::LogStreamCommit(LogStream *log_stream,
                                            LogLevel level, const char *file,
                                            int line)
    : log_stream_(log_stream), level_(level) {
  log_stream_->append("[");
  log_stream_->append(LogLevel_to_str(level));
  log_stream_->append("][");
  log_stream_->append(file);
  log_stream_->append(":");
  log_stream_->append(line);
  log_stream_->append("]");
}
LogStream::LogStreamCommit::~LogStreamCommit() {
  if (log_stream_) {
    log_stream_->append("\n");
    log_stream_->clear(level_);
  }
}
} // namespace multilog