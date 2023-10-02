// File: parser.h
// Purpose: Class definition of a recursive descent parser.
#include "lexer.h"

class Parser
{
public:
  // constructor
  Parser(Lexer *_lex);

  // attempt to parse the program which the lexer provides
  void parse();

private:
  Lexer *_lex;

  //////////////////////////////////////////
  // Lexer Convenience Functions
  //////////////////////////////////////////

  // Returns true if the current token matches tok
  // Returns false otherwise
  bool has(Token tok);

  // Returns true if the current token matches tok
  // Prints an error message and aborts the program otherwise
  bool must_be(Token tok);

  // Return the current token and advance the lexer.
  Lexer_Token consume();

  //////////////////////////////////////////
  // Recursive Descent Parser functions
  //////////////////////////////////////////
  void parse_Program();
  void parse_Statement();
  void parse_Expression();
  void parse_Expression2();
  void parse_Term();
  void parse_Term2();
  void parse_Factor();
  void parse_Factor2();
  void parse_Base();
  void parse_Number();
};