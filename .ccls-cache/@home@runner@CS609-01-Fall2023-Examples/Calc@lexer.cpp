// File: lexer.cpp
// Purpose: Implementation for a lexer.
#include "lexer.h"
#include <iostream>
#include <string>

////////////////////////////////////////
// Lexer_Token implementation
////////////////////////////////////////
Lexer_Token::Lexer_Token() {
  // do nothing
}

Lexer_Token::Lexer_Token(Token tok, const std::string &lexeme, int line,
                         int col) {
  this->tok = tok;
  this->lexeme = lexeme;
  this->line = line;
  this->col = col;
}

// print out the lexer token
std::ostream &operator<<(std::ostream &os, const Lexer_Token &t) {
  static std::string token_label[] = {
      "INVALID", "EOI", "NEWLINE", "PLUS",   "MINUS",  "TIMES",  "DIVIDE",
      "MOD",     "POW", "LPAREN",  "RPAREN", "INTLIT", "REALLIT"};
  return os << token_label[t.tok] << " \"" << t.lexeme << "\" Line: " << t.line << " Column " << t.col;
}


////////////////////////////////////////
// Lexer Implementation
////////////////////////////////////////
Lexer::Lexer(std::istream &_is) : _is(_is)
{
  _cur.tok = INVALID;
  _line = 1;
  _col = 0;

  //read the first character
  read();
}

//return the next token in the stream
Lexer_Token Lexer::next()
{
  // set an invalid token at the current position
  std::string lexeme = "";
  lexeme += _cur_char;
  _cur = Lexer_Token(INVALID, lexeme, _line, _col);

  //advance to the next character
  read();

  return _cur;
}

//return the current token
Lexer_Token Lexer::cur()
{
  return _cur;
}

  // get the next character from the stream
void Lexer::read()
{
  // handle the start of new lines
  if(_cur_char == '\n') {
    _line++;
    _col = 0;
  }  

  // read a character
  _cur_char = _is.get();
  if(_is) {
    //increment the column if we have read the character
    _col++;
  }
}