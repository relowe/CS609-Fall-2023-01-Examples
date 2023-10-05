// File: parser.cpp
// Purpose: The implemenation file for the parser class
#include "parser.h"
#include <iostream>

// constructor
Parser::Parser(Lexer *_lex) {
  // get the lexer
  this->_lex = _lex;

  // get the first token
  _lex->next();
}

// attempt to parse the program which the lexer provides
Parse_Tree *Parser::parse() { return parse_Program(); }

//////////////////////////////////////////
// Lexer Convenience Functions
//////////////////////////////////////////

// Returns true if the current token matches tok{}
// Returns false otherwise
bool Parser::has(Token tok) { return _lex->cur().tok == tok; }

// Returns true if the current token matches tok
// Prints an error message and aborts the program otherwise
bool Parser::must_be(Token tok) {
  if (has(tok)) {
    return true;
  }

  // if we make it here, this is an error
  std::cerr << "Parse Error: Unexpected " << _lex->cur() << std::endl;

  // destroy the program
  exit(-1);
}

// Return the current token and advance the lexer.
Lexer_Token Parser::consume() {
  Lexer_Token t = _lex->cur();
  _lex->next();
  return t;
}

//////////////////////////////////////////
// Recursive Descent Parser functions
//////////////////////////////////////////

/*
< Program > ::= < Statement > < Program' >

< Program' > ::=  < Statement > < Program' >
                  | ""
*/
Parse_Tree* Parser::parse_Program() {
  Program *result = new Program();
  
  do {
    result->add(parse_Statement());
  } while (not has(EOI));

  return result;
}

/*
< Statement >    ::= < Expression > NEWLINE
 */
Parse_Tree* Parser::parse_Statement() {
  Parse_Tree *result = parse_Expression();
  must_be(NEWLINE);
  consume();

  return result;
}

/*
< Expression >   ::= < Term > < Expression' >
 */
Parse_Tree* Parser::parse_Expression() {
  Parse_Tree *left = parse_Term();
  return parse_Expression2(left);
}

/*
< Expression' >  ::= PLUS < Term > < Expression' >
                     | MINUS < Term > < Expression' >
                     | ""
 */
Parse_Tree* Parser::parse_Expression2(Parse_Tree *left) {
  if (has(PLUS)) {
    consume();
    Add *result = new Add();
    result->left(left);
    result->right(parse_Term());
    return parse_Expression2(result);
  } else if (has(MINUS)) {
    consume();
    Subtract *result = new Subtract();
    result->left(left);
    result->right(parse_Term());
    return parse_Expression2(result);
  }

  // "" rule
  return left;
}

/*
< Term >         ::= < Factor > < Term' >
*/
Parse_Tree* Parser::parse_Term() {
    Parse_Tree *left = parse_Factor();
    return parse_Term2(left);
}

/*
< Term' >        ::= TIMES < Factor > < Term' >
                     | DIVIDE < Factor > < Term' >
                     | MOD < Factor > < Term' >
*/
Parse_Tree* Parser::parse_Term2(Parse_Tree *left) {
  if (has(TIMES)) {
    consume();
    Multiply *result = new Multiply();
    result->left(left);
    result->right(parse_Factor());
    return parse_Term2(result);
  } else if (has(DIVIDE)) {
    consume();
    Divide *result = new Divide();
    result->left(left);
    result->right(parse_Factor());
    return parse_Term2(result);
  } else if (has(MOD)) {
    consume();
    Mod *result = new Mod();
    result->left(left);
    result->right(parse_Factor());
    return parse_Term2(result);
  }
  
  //epsilon rule
  return left;
}

/*
< Factor >       ::= < Base > < Factor' >
*/
Parse_Tree* Parser::parse_Factor() {
  Parse_Tree *left = parse_Base();
  return parse_Factor2(left);
}

/*
< Factor' >      ::= POW < Factor >
                     | ""
*/
Parse_Tree* Parser::parse_Factor2(Parse_Tree *left) {
  if (has(POW)) {
    consume();
    Power *result = new Power();
    result->left(left);
    result->right(parse_Factor());
    return result;
  }

  return left;
}

/*
< Base >         ::= LPAREN < Expression > RPAREN
                     | MINUS < Expression >
                     | < Number >
*/
Parse_Tree *Parser::parse_Base() {
  if (has(LPAREN)) {
    consume();
    Parse_Tree *result = parse_Expression();
    must_be(RPAREN);
    consume();
    return result;
  } else if (has(MINUS)) {
    consume();
    Negation *result = new Negation();
    result->child(parse_Expression());
    return result;
  } else {
    return parse_Number();
  }
}

/*
< Number >       ::= INTLIT | REALLIT
*/
Parse_Tree* Parser::parse_Number() {
  if (has(INTLIT)) {
    return new Literal(consume());
  } else {
    must_be(REALLIT);
    return new Literal(consume());
  }
}