#include <torch/csrc/jit/jit_log.h>
#include <c10/util/Exception.h>
#include <caffe2/utils/string_utils.h>
#include <cstdlib>
#include <iomanip>
#include <mutex>
#include <regex>
#include <sstream>
#include <thread>

namespace torch {
namespace jit {

JitLoggingLevels jit_log_level() {
  static const char* c_log_level = std::getenv("PYTORCH_JIT_LOG_LEVEL");
  static const JitLoggingLevels log_level = c_log_level
      ? static_cast<JitLoggingLevels>(std::atoi(c_log_level))
      : JitLoggingLevels::OFF;
  return log_level;
}

std::string jit_log_prefix(JitLoggingLevels level, const std::string& in_str) {
  std::stringstream in_ss(in_str);
  std::stringstream out_ss(in_str);
  std::string line;

  while (std::getline(in_ss, line, '\n')) {
    out_ss << level << line << std::endl;
  }

  return out_ss.str();
}

std::ostream& operator<<(std::ostream& out, JitLoggingLevels level) {
  switch (level) {
    case JitLoggingLevels::OFF:
      TORCH_INTERNAL_ASSERT("UNREACHABLE");
      break;
    case JitLoggingLevels::GRAPH_DUMP:
      out << "JIT_GRAPH_DUMP";
      break;
    case JitLoggingLevels::INFO:
      out << "JIT_INFO";
      break;
    case JitLoggingLevels::DEBUG:
      out << "JIT_DEBUG";
      break;
    default:
      TORCH_INTERNAL_ASSERT("Invalid level");
  }

  return out;
}

} // namespace jit
} // namespace torch
