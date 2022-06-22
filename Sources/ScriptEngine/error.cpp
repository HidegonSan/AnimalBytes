#include <CTRPluginFramework.hpp>
#include <cstdarg>
#include "Core.h"
#include "Cheats/CodeContext.h"

namespace CTRPluginFramework::ScriptEngine {
  
  void Core::append_error(u32 line, u32 column, char const* fmt, ...) {
    auto buf = Cheats::CodeContext::get_instance()->chbuffer;
    auto inst = Core::get_instance();

    va_list ap;
    va_start(ap, fmt);
    vsprintf(buf, fmt, ap);
    va_end(ap);

    ErrorInfo err {
      .msg = std::string(buf),
      .line = line,
      .column = column
    };

    inst->error_list.emplace_back(err);
  }

}