// File: lexer.h
// Purpose: Definitions for a lexer.
#ifndef LEXER_H
#define LEXER_H
#include <string>
#include <iostream>

// our language's tokens
enum Token {
  INVALID = 0,
  EOI,
  NEWLINE,
  PLUS,
  MINUS,
  TIMES,
  DIVIDE,
  MOD,
  POW,
  LPAREN,
  RPAREN,
  INTLIT,
  REALLIT
};

// Tokens as emitted by the lexer
class Lexer_Token
{
public:
  Lexer_Token();
  Lexer_Token(Token tok, const std::string &lexeme, int line, int col);
  Token tok;
  std::string lexeme;
  int line;
  int col;
};
std::ostream &operator<<(std::ostream &os, const Lexer_Token &t);

// Lexer definition
class Lexer
{
public:
  Lexer(std::istream &_is);

  //return the next token in the stream
  Lexer_Token next();

  //return the current token
  Lexer_Token cur();

private:
  std::istream &_is;
  char _cur_char;
  Lexer_Token _cur;
  int _line;
  int _col;

  // get the next character from the stream
  void read();
};

#endif