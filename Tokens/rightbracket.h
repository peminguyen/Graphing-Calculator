#ifndef rightbracket_h
#define rightbracket_h

#include "token.h"

class RightBracket: public Token{
public:
    // constructor
    RightBracket(char t);
    
    // Return the type RIGHTBRACKET
    TokenType TypeOf() const;
    
    // Print the right bracket
    void Print(ostream& outs = cout) const;
    
    // Get the right bracket
    char GetRightBracket();
private:
    char _t;
    
};

#endif /* rightbracket_h */
