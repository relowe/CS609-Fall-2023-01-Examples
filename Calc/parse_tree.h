// File: parse_tree.h
// Purpose: Class definitions for all of the elements of our parse tree.
#include <vector>
#include "lexer.h"

//////////////////////////////////////////
// Pure Virtual Base Class
// (abstract)
//////////////////////////////////////////
class Parse_Tree {
public:
  virtual void print(int indent) const = 0;  // <- =0 syntax indicates pure virtual
};


//////////////////////////////////////////
// Base classes for the operators
//////////////////////////////////////////
class UnaryOp : public Parse_Tree {
public:
  // accessor and mutator for the child
  virtual Parse_Tree* child() const;
  virtual void child(Parse_Tree *_child);

private:
  Parse_Tree *_child;
};


class BinaryOp : public Parse_Tree {
public:
  // accessor and mutator for the children
  virtual Parse_Tree* left() const;
  virtual void left(Parse_Tree *_left);
  virtual Parse_Tree* right() const;
  virtual void right(Parse_Tree *_right);

private:
  Parse_Tree *_left;
  Parse_Tree *_right;
};


class NaryOp : public Parse_Tree {
public:
  // add a child
  void add(Parse_Tree *child);

  // iterators for looping through the children
  virtual std::vector<Parse_Tree*>::const_iterator begin() const;
  virtual std::vector<Parse_Tree*>::const_iterator end() const;
private:
  std::vector<Parse_Tree *> _children;
};


//////////////////////////////////////////
// Operator Nodes
//////////////////////////////////////////
class Program : public NaryOp {
public:
  virtual void print(int indent) const;
};


class Add : public BinaryOp {
public:
  virtual void print(int indent) const;
};


class Subtract : public BinaryOp {
public:
  virtual void print(int indent) const;
};

class Multiply : public BinaryOp {
public:
  virtual void print(int indent) const;
};

class Divide : public BinaryOp {
public:
  virtual void print(int indent) const;
};

class Mod : public BinaryOp {
public:
  virtual void print(int indent) const;
};

class Power : public BinaryOp {
public:
  virtual void print(int indent) const;
};

class Negation: public UnaryOp {
public:
  virtual void print(int indent) const;
};

class Literal : public Parse_Tree {
public:
  Literal(const Lexer_Token &tok);

  virtual void print(int indent) const;
private:
  Lexer_Token _tok;
};