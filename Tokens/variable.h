#ifndef variable_h
#define variable_h

#include "token.h"

class Variable: public Token {
public:
    // Constructor
    Variable(char v);
    
    // Print the variable
    void Print(ostream &outs = cout) const;
    
    // Get the type variable
    TokenType TypeOf() const;
    
    // Get the value of variable
    char GetVariable();
    
private:
    char _v;
};


#endif /* variable_h */
