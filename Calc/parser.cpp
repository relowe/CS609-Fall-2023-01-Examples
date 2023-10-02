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
void Parser::parse() { parse_Program(); }

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
void Parser::parse_Program() {
  do {
    parse_Statement();
  } while (not has(EOI));
}

/*
< Statement >    ::= < Expression > NEWLINE
 */
void Parser::parse_Statement() {
  parse_Expression();
  must_be(NEWLINE);
  consume();
}

/*
< Expression >   ::= < Term > < Expression' >
 */
void Parser::parse_Expression() {
  parse_Term();
  parse_Expression2();
}

/*
< Expression' >  ::= PLUS < Term > < Expression' >
                     | MINUS < Term > < Expression' >
                     | ""
 */
void Parser::parse_Expression2() {
  if (has(PLUS)) {
    consume();
    parse_Term();
    parse_Expression2();
  } else if (has(MINUS)) {
    consume();
    parse_Term();
    parse_Expression2();
  }
}

/*
< Term >         ::= < Factor > < Term' >
*/
void Parser::parse_Term() {
    parse_Factor();
    parse_Term2();
}

/*
< Term' >        ::= TIMES < Factor > < Term' >
                     | DIVIDE < Factor > < Term' >
                     | MOD < Factor > < Term' >
*/
void Parser::parse_Term2() {
  if (has(TIMES)) {
    consume();
    parse_Factor();
    parse_Term2();
  } else if (has(DIVIDE)) {
    consume();
    parse_Factor();
    parse_Term2();
  } else if (has(MOD)) {
    consume();
    parse_Factor();
    parse_Term2();
  }
}

/*
< Factor >       ::= < Base > < Factor' >
*/
void Parser::parse_Factor() {
  parse_Base();
  parse_Factor2();
}

/*
< Factor' >      ::= POW < Factor >
                     | ""
*/
void Parser::parse_Factor2() {
  if (has(POW)) {
    consume();
    parse_Factor();
  }
}

/*
< Base >         ::= LPAREN < Expression > RPAREN
                     | MINUS < Expression >
                     | < Number >
*/
void Parser::parse_Base() {
  if (has(LPAREN)) {
    consume();
    parse_Expression();
    must_be(RPAREN);
    consume();
  } else if (has(MINUS)) {
    consume();
    parse_Expression();
  } else {
    parse_Number();
  }
}

/*
< Number >       ::= INTLIT | REALLIT
*/
void Parser::parse_Number() {
  if (has(INTLIT)) {
    consume();
  } else {
    must_be(REALLIT);
    consume();
  }
}