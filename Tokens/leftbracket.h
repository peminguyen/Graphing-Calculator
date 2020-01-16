#ifndef leftbracket_h
#define leftbracket_h

#include "token.h"

// Class Left Brackets
class LeftBracket: public Token{
public:
    // Constructor
    LeftBracket(char t);
    
    // Return the type LEFTBRACKET
    TokenType TypeOf() const;
    
    // Print the left bracket
    void Print(ostream& outs = cout) const;
    
    // Get the left bracket
    char GetLeftBracket();
private:
    char _t;
    
};


#endif /* leftbracket_h */
