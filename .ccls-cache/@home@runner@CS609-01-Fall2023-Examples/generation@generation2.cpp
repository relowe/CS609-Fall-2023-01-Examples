#include <iostream>
#include <stdlib.h>
#include <string>

/*
 * This program implements a generator for the following language:
 *  1.) s -> e
 *  2.) e -> e + e
 *  3.) e -> e - e
 *  4.) e -> e * e
 *  5.) e -> e / e
 *  6.) e -> n
 *  7.) n -> nd
 *  8.) n -> d
 *  9.) d -> 0
 * 10.) d -> 1
 * we are going to limit the depth of recursion
 */

int max_depth;

// return a random integer in the range [min, max]
int select_rule(int min, int max, int depth) {
  if (depth >= max_depth)
    return max; // max is always non-recurisve
  return rand() % (max - min + 1) + min;
}

///////////////////////////////////////////////////////////////////////////
// Non-terminal functions
///////////////////////////////////////////////////////////////////////////
std::string s(int depth);
std::string e(int depth);
std::string n(int depth);
std::string d(int depth);

/*
 *  1.) s -> e
 */
std::string s(int depth) { return e(depth); }

/*
 *  2.) e -> e + e
 *  3.) e -> e - e
 *  4.) e -> e * e
 *  5.) e -> e / e
 *  6.) e -> n
 */
std::string e(int depth) {
  int rule = select_rule(2, 6, depth);

  if (rule == 2) {
    return e(depth + 1) + " + " + e(depth + 1);
  } else if (rule == 3) {
    return e(depth + 1) + " - " + e(depth + 1);
  } else if (rule == 4) {
    return e(depth + 1) + " * " + e(depth + 1);
  } else if (rule == 5) {
    return e(depth + 1) + " / " + e(depth + 1);
  }

  // rule 6
  return n(depth);
}

/*
 *  7.) n -> nd
 *  8.) n -> d
 */
std::string n(int depth) {
  int rule = select_rule(7, 8, depth);

  if (rule == 7) {
    return n(depth + 1) + d(depth);
  }

  // rule 8
  return d(depth);
}

/*
 *  9.) d -> 0
 * 10.) d -> 1
 */
std::string d(int depth) {
  int rule = select_rule(9, 10, depth);

  if (rule == 9) {
    return "0";
  } else {
    return "1";
  }
}

///////////////////////////////////////////////////////////////////////////
// Generator
///////////////////////////////////////////////////////////////////////////
int main() {
  // for-ever loop
  for (;;) {
    std::cout << "Recursion Depth? ";
    std::cin >> max_depth;
    std::cout << s(0) << std::endl;
  }
}