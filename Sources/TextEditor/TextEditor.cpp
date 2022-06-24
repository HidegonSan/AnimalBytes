#include <CTRPluginFramework.hpp>
#include "TextEditor.h"
#include "impl/TEImpl.h"

namespace CTRPluginFramework {
  static TextEditor* __g_instance;

  TextEditor::TextEditor()
    : impl(new TextEditorImpl)
  {
    __g_instance = this;
  }

  TextEditor::TextEditor(std::string const& path)
    : impl(new TextEditorImpl(path))
  {
  }

  TextEditor::~TextEditor()
  {
  }

  int TextEditor::open() const {
    impl->open();
  }

  TextEditor* TextEditor::get_instance() {
    return __g_instance;
  }

}