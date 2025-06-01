#pragma once

#include <fmt/format.h>

#include <csignal>
#include <filesystem>
#include <functional>
#include <source_location>

namespace theta::debug_utils {

class Debug {
 public:
  static bool s_enabled_;

  static int get_indent(bool enter) {
    if (enter) {
      return s_indent_++;
    }
    return s_indent_--;
  }

  static void enable() { s_enabled_ = true; }

  static void disable() { s_enabled_ = false; }

  template <typename... Args>
  Debug(const char *format, Args... args)
      : msg_{fmt::format(fmt::runtime(format), args...)},
        indent_{get_indent(/*enter=*/true)} {
    print_entry('>');
  }

  Debug(std::function<void()> func) : indent_(0), func_(func) {}

  Debug(std::source_location loc = std::source_location::current())
      : loc_{loc}, indent_{get_indent(/*enter=*/true)} {
    print_entry('>');
  }

  ~Debug() {
    print_entry('<');
    get_indent(/*enter=*/false);
  }

  template <typename... Args>
  void note(const char *format, Args... args) {
    note_ = fmt::format(fmt::runtime(format), args...);
  }

  template <typename... Args>
  void print(const char *format, Args... args) const {
    if (s_enabled_) {
      fmt::print(stderr, "{:{}s}# {}\n", "", indent_,
                 fmt::format(fmt::runtime(format), args...));
    }
  }

  static std::string format_location(
      const std::source_location &loc = std::source_location::current()) {
    return fmt::format(
        "{}({}):{}", std::filesystem::path{loc.file_name()}.filename().string(),
        loc.line(), loc.function_name());
  }

 private:
  static int s_indent_;

  const int indent_;
  const std::source_location loc_;
  const std::string msg_;
  std::string note_;
  std::function<void()> func_;

  void print_entry(char token) const {
    if (s_enabled_) {
      fmt::print(stderr, "{:{}s}{} {}|{}{}\n", "", indent_, token,
                 format_location(loc_), msg_, note_);
    }
  }
};

}  // namespace theta::debug_utils
