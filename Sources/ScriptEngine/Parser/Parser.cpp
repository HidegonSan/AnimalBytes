#include <CTRPluginFramework.hpp>
#include <cstdint>
#include <ctype.h>
#include "Parser.h"

namespace CTRPluginFramework::ScriptEngine {
  
  Parser::Parser(std::string const& source)
    : source(source),
      position(0),
      length(source.length())
  {
  }

  bool Parser::isvalid() {
    return position < length;
  }

  char Parser::peek() {
    return source[position];
  }

  void Parser::pass_space() {
    while( isvalid() && peek() <= ' ' ) {
      position++;
    }
  }

  bool Parser::eat(char const* str) {
    bool bval = isalpha(*str) || *str == '_';

    while( isvalid() && *str ) {
      if( peek() != *str++ ) {
        return false;
      }

      position++;
    }

    if( bval && isvalid() && (isalnum(peek()) || peek() == '_') ) {
      return false;
    }

    return true;
  }

  void Parser::expect(char const* str) {
    if( !eat(str) ) {
      
    }
  }

  Node* Parser::factor() {

  }

  Node* Parser::add() {
    auto x = factor();

    while( isvalid() ) {

    }

    return x;
  }

  Node* Parser::parse() {
    return add();
  }

}