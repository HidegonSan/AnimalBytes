#pragma once

#include <CTRPluginFramework.hpp>

namespace CTRPluginFramework::ScriptEngine {
  class CScriptFile {

    explicit CScriptFile(std::string const& path) {
      File::Open(file, path);
      
      size = file.GetSize();
    }

    std::string read(std::vector<std::string>& lines, int maxsize) {

      u64 curpos = file.Tell();



    }

  private:
    File file;
    u64 size;
  };
}