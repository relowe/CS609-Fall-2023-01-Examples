// File: ref_env.h
// Purpose: A reference environment class definition.
#ifndef REF_ENV_H
#define REF_ENV_H
#include <map>
#include <string>
#include "parse_tree.h"

// class prototypes for include compatability
class EvalResult;

class Ref_Env 
{
public:
  Ref_Env();

  // Bind a value to a name
  virtual void set(const std::string &name, const EvalResult &value);

  // Retrieve a bound name
  virtual EvalResult get(const std::string &name);

private:
  std::map<std::string, EvalResult> _symbol_table;
};

#endif