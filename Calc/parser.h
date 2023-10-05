// File: parser.h
// Purpose: Class definition of a recursive descent parser.
#include "lexer.h"
#include "parse_tree.h"

class Parser
{
public:
  // constructor
  Parser(Lexer *_lex);

  // attempt to parse the program which the lexer provides
  Parse_Tree *parse();

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
  Parse_Tree* parse_Program();
  Parse_Tree* parse_Statement();
  Parse_Tree* parse_Expression();
  Parse_Tree* parse_Expression2(Parse_Tree *left);
  Parse_Tree* parse_Term();
  Parse_Tree* parse_Term2(Parse_Tree *left);
  Parse_Tree* parse_Factor();
  Parse_Tree* parse_Factor2(Parse_Tree *left);
  Parse_Tree* parse_Base();
  Parse_Tree* parse_Number();
};