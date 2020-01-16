#ifndef token_h
#define token_h

#include <iostream>
using namespace std;

// Different types of tokens
enum TokenType{OPERAND, OPERATOR, LEFTBRACKET, RIGHTBRACKET, SPACE, FUNCTION, VARIABLE, LETTER, COMMA, OTHER};

class Token{
public:
    // Output the token
    friend ostream& operator <<(ostream& outs, const Token& t);
    
    // Print a token
    virtual void Print(ostream& outs = cout) const = 0;
    
    // Get the token type
    virtual TokenType TypeOf() const = 0;
};

#endif /* token_h */
