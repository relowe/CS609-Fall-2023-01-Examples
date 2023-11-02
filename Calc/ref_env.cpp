// File: ref_env.cpp
// Purpose: A reference environment class implementation.
#include <map>
#include <string>
#include "parse_tree.h"
#include "ref_env.h"

Ref_Env::Ref_Env()
{
  // nothing to do here
}

// Bind a value to a name
void Ref_Env::set(const std::string &name, const EvalResult &value)
{
  _symbol_table[name] = value;
}

// Retrieve a bound name
EvalResult Ref_Env::get(const std::string &name)
{
  if(_symbol_table.find(name) != _symbol_table.end()) {
    // we have found the varaible
    return _symbol_table[name];
  }

  // if we make it here, we did not find the variable
  EvalResult result;
  result.set_type(UNDEFINED);
  return result;
}