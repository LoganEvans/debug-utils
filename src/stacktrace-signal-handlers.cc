#include <fmt/format.h>

#include <array>
#include <cpptrace/cpptrace.hpp>
#include <csignal>

namespace theta::debug_utils {

struct InstallStacktraceSignalHandlers {
  InstallStacktraceSignalHandlers() {
    for (const auto sig : std::to_array(
             {SIGABRT, SIGFPE, SIGILL, SIGINT, SIGSEGV, SIGTERM, SIGINT})) {
      std::signal(sig, signal_handler);
    }
  }

  static void signal_handler(int signal) {
    fmt::print(stderr, "Caught signal: {}\n", signal);
    cpptrace::generate_trace().print_with_snippets();
    std::exit(signal);
  }
};

namespace detail {
theta::debug_utils::InstallStacktraceSignalHandlers
    install_stacktrace_signal_handlers{};
}

}  // namespace theta::debug_utils
