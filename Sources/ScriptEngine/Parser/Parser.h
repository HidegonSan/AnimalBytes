#pragma once

#include "types.h"
#include "Node.h"

namespace CTRPluginFramework::ScriptEngine {
  class Parser {
    static char const** punctuaters;

    std::string const& source;
    size_t position;
    size_t length;

  public:
    explicit Parser(std::string const& source);

    bool isvalid();
    char peek();
    void pass_space();
    bool eat(char const* str);
    void expect(char const* str);

    Node* factor();
    Node* add();
    
    Node* parse();
  };
}