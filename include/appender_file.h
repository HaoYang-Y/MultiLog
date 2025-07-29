#ifndef _APPENDER_FILE_H_
#define _APPENDER_FILE_H_

#include "appender.h"
#include "logger.h"
#include <fstream>

namespace multilog {
class AppenderFile : public Appender {
public:
  AppenderFile(size_t size);
  ~AppenderFile() override;

protected:
  void write(std::vector<LogEvent> &event_queue) override;
  void run() override;

private:
private:
  const char *file = "test.log";
  bool is_sync;
  std::ofstream ofs_;
};
} // namespace multilog
#endif