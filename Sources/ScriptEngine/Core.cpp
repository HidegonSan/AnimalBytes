#include <CTRPluginFramework.hpp>
#include "Editor/ScriptEditor.h"
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

  ScriptEditor* Core::get_editor() {
    return get_instance()->editor;
  }

  Core::Core() {
    this->editor = new 
  }

}