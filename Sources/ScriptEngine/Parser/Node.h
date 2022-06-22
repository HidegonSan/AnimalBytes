#pragma once

namespace CTRPluginFramework::ScriptEngine {
  enum NodeKind : u8 {
    ND_I8,
    ND_I16,
    ND_I32,
    ND_U8,
    ND_U16,
    ND_U32,

    ND_ADD,
  };

  struct Node {
    NodeKind kind;

    union {
      u32 val_int;
      float val_f32;

      struct {
        Node* lhs;
        Node* rhs;
      };
    };
  };
}