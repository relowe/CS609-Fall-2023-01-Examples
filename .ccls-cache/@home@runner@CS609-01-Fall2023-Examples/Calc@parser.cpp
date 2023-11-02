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
    Parse_Tree *statement = parse_Statement();
    // ignore null statements
    if(statement != nullptr) {
      result->add(statement);
    }
  } while (not has(EOI));

  return result;
}

/*
< Statement >    ::= ID < Statement' > NEWLINE
                     | < IO-Operation > NEWLINE
                     | < Expression > NEWLINE
                     | NEWLINE
 */
Parse_Tree* Parser::parse_Statement() {
  Parse_Tree *result;

  if(has(NEWLINE)) {
    consume();
    return nullptr;
  }

  if(has(ID)) {
    // get the ID from parse_Number
    result = parse_Number();
    result = parse_Statement2(result);
  } else if(has(INPUT) or has(DISPLAY)) {
    result = parse_IO_Operation();
  } else {
    result = parse_Expression();
  }
  
  must_be(NEWLINE);
  consume();

  return result;
}


/*
< Statement' >   ::= EQUAL < Expression > 
                     | < Factor' > < Term' > < Expression' >
*/
Parse_Tree *Parser::parse_Statement2(Parse_Tree *left) 
{
  Parse_Tree *result;
  
  if(has(EQUAL)) {
    // this an assignment
    consume(); 
    Assignment *result = new Assignment();
    result->left(left);
    result->right(parse_Expression());
    return result;
  } else {
    result = parse_Factor2(left);
    result = parse_Term2(result);
    result = parse_Expression2(result);
  }

  return result;
}

/*
< IO-Operation > ::= DISPLAY < Expression >
                     | INPUT ID
*/
Parse_Tree* Parser::parse_IO_Operation() {
  if(has(DISPLAY)) {
    consume();
    Display *result = new Display();
    result->child(parse_Expression());
    return result;
  }

  must_be(INPUT);
  consume();
  must_be(ID);
  Input *result = new Input();
  result->child(parse_Number());
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
< Number >       ::= INTLIT | REALLIT | ID
*/
Parse_Tree* Parser::parse_Number() {
  if (has(INTLIT)) {
    return new Literal(consume());
  } else if (has(REALLIT)) {
    return new Literal(consume());
  } else {
    must_be(ID);
    return new Variable(consume());
  }
}