#include <CTRPluginFramework.hpp>
#include "Core.h"

namespace CTRPluginFramework::ScriptEngine {
  namespace {
    Core* g_instance;
  }

  Core* Core::get_instance() {
    if( !g_instance ) {
      g_instance = new Core;
    }

    return g_instance;
  }



}