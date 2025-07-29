#ifndef _LOG_UTILS_H_
#define _LOG_UTILS_H_
namespace multilog {
template <typename T> inline const char *format_specifier() {
  return "unknow";
}

// 为常用类型特化格式说明符
template <> inline const char *format_specifier<int>() { return "%d"; }
template <> inline const char *format_specifier<long>() { return "%ld"; }
template <> inline const char *format_specifier<char>() { return "%c"; }
template <> inline const char *format_specifier<long long>() { return "%lld"; }
template <> inline const char *format_specifier<unsigned int>() { return "%u"; }
template <> inline const char *format_specifier<unsigned long>() {
  return "%lu";
}
template <> inline const char *format_specifier<unsigned long long>() {
  return "%llu";
}
template <> inline const char *format_specifier<float>() { return "%.6f"; }
template <> inline const char *format_specifier<double>() { return "%.6lf"; }
template <> inline const char *format_specifier<const char *>() { return "%s"; }
template <> inline const char *format_specifier<std::string>() { return "%s"; }
} // namespace multilog

#endif