#include <fmt/format.h>

#include <array>
#include <cpptrace/cpptrace.hpp>
#include <csignal>

namespace theta::debug_utils {

struct InstallStacktraceSignalHandlers {
  InstallStacktraceSignalHandlers() {
    for (const auto sig : std::to_array(
             {SIGABRT, SIGFPE, SIGILL, SIGINT, SIGSEGV, SIGTERM, SIGINT})) {
      std::signal(sig, signal_handler</*exit_on_signal=*/true>);
    }

    std::signal(SIGUSR1, signal_handler</*exit_on_signal=*/false>);
  }

  template <bool exit_on_signal = true>
  static void signal_handler(int signal) {
    fmt::print(stderr, "Caught signal: {}\n", signal);
    cpptrace::generate_trace().print_with_snippets();
    if constexpr (exit_on_signal) {
      std::exit(signal);
    }
  }
};

namespace detail {
theta::debug_utils::InstallStacktraceSignalHandlers
    install_stacktrace_signal_handlers{};
}

}  // namespace theta::debug_utils
