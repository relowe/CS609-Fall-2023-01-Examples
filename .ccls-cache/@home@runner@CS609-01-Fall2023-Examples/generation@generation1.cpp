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
 */

// return a random integer in the range [min, max]
int select_rule(int min, int max) 
{
    return rand() % (max - min + 1) + min;
}

///////////////////////////////////////////////////////////////////////////
// Non-terminal functions
///////////////////////////////////////////////////////////////////////////
std::string s();
std::string e();
std::string n();
std::string d();


/*
 *  1.) s -> e
 */
std::string s() 
{
    return e();
}


/*
 *  2.) e -> e + e
 *  3.) e -> e - e
 *  4.) e -> e * e
 *  5.) e -> e / e
 *  6.) e -> n
 */
std::string e()
{
    int rule = select_rule(2, 6);

    if(rule == 2) {
        return e() + " + " + e();
    } else if(rule == 3) {
        return e() + " - " + e();
    } else if(rule == 4) {
        return e() + " * " + e();
    } else if(rule == 5) {
        return e() + " / " + e();
    }

    // rule 6
    return n();
}


/*
 *  7.) n -> nd
 *  8.) n -> d
 */
std::string n()
{
    int rule = select_rule(7, 8);

    if(rule == 7) {
        return n() + d();
    }

    // rule 8
    return d();
}

/* 
 *  9.) d -> 0
 * 10.) d -> 1
 */
std::string d()
{
    int rule = select_rule(9, 10);

    if(rule == 9) {
        return "0";
    } else {
        return "1";
    }
}


///////////////////////////////////////////////////////////////////////////
// Generator
///////////////////////////////////////////////////////////////////////////
int main()
{
    std::cout << s() << std::endl;
}