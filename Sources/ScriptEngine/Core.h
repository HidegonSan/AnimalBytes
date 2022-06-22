#pragma once

#include <vector>

namespace CTRPluginFramework::ScriptEngine {
  struct ErrorInfo {
    std::string msg;
    u32 line;
    u32 column;
  };

  class Core {
  public:

    static Core* get_instance();

    static MenuFolder* create_folder();

    static void append_error(u32 line, u32 column, char const* fmt, ...);

    std::vector<ErrorInfo> const& get_err_list() const;

  private:
    Core();

    std::vector<ErrorInfo> error_list;
  };
}