// File: parse_tree.cpp
// Purpose: Implementation of the parse tree classes
#include <iostream>
#include <iomanip>
#include "parse_tree.h"

//////////////////////////////////////////
// Base classes for the operators
//////////////////////////////////////////

// accessor and mutator for the child
Parse_Tree* UnaryOp::child() const
{
  return _child;
}


void UnaryOp::child(Parse_Tree *_child)
{
  this->_child = _child;
}



// accessor and mutator for the children
Parse_Tree* BinaryOp::left() const
{
  return _left;
}


void BinaryOp::left(Parse_Tree *_left)
{
  this->_left = _left;
}


Parse_Tree* BinaryOp::right() const
{
  return _right;
}


void BinaryOp::right(Parse_Tree *_right)
{
  this->_right = _right;
}



// add a child
void NaryOp::add(Parse_Tree *child)
{
  _children.push_back(child);
}

// iterators for looping through the children
std::vector<Parse_Tree*>::const_iterator NaryOp::begin() const
{
  return _children.begin();
}


std::vector<Parse_Tree*>::const_iterator NaryOp::end() const
{
  return _children.end();
}


//////////////////////////////////////////
// Operator Nodes
//////////////////////////////////////////
void Program::print(int indent) const
{
  // print the indent
  std::cout << std::setw(indent) << "";
  std::cout << "Program" << std::endl;

  //loop over the children
  for(auto itr = begin(); itr != end(); itr++) {
    (*itr)->print(indent+1);
  }
}


void Add::print(int indent) const
{
  // print the right child
  right()->print(indent+1);

  //indent and print ourself
  std::cout << std::setw(indent) << "";
  std::cout << "+" << std::endl;

  // print the left child
  left()->print(indent+1);
}


void Subtract::print(int indent) const
{
  // print the right child
  right()->print(indent+1);

  //indent and print ourself
  std::cout << std::setw(indent) << "";
  std::cout << "-" << std::endl;

  // print the left child
  left()->print(indent+1);
}


void Multiply::print(int indent) const
{
  // print the right child
  right()->print(indent+1);

  //indent and print ourself
  std::cout << std::setw(indent) << "";
  std::cout << "*" << std::endl;

  // print the left child
  left()->print(indent+1);
}


void Divide::print(int indent) const
{
  // print the right child
  right()->print(indent+1);

  //indent and print ourself
  std::cout << std::setw(indent) << "";
  std::cout << "/" << std::endl;

  // print the left child
  left()->print(indent+1);
}


void Mod::print(int indent) const
{
  // print the right child
  right()->print(indent+1);

  //indent and print ourself
  std::cout << std::setw(indent) << "";
  std::cout << "MOD" << std::endl;

  // print the left child
  left()->print(indent+1);
}


void Power::print(int indent) const
{
  // print the right child
  right()->print(indent+1);

  //indent and print ourself
  std::cout << std::setw(indent) << "";
  std::cout << "^" << std::endl;

  // print the left child
  left()->print(indent+1);
}


void Negation::print(int indent) const
{
  // print myself 
  std::cout << std::setw(indent) << "";
  std::cout << "- (NEG)";

  child()->print(indent+1);
}


Literal::Literal(const Lexer_Token &tok)
{
  this->_tok = tok;  
}

void Literal::print(int indent) const
{
  // print ourself 
  std::cout << std::setw(indent) << "";
  std::cout << _tok.lexeme;
}