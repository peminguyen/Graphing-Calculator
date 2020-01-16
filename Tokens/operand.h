#ifndef operand_h
#define operand_h

#include "token.h"

class Operand: public Token{
public:
    // Constructor
    Operand(double o);
    
    // Print the operand
    void Print(ostream& outs = cout) const;
    
    // Get the type Operand
    TokenType TypeOf() const;
    
    // Get the value of operand
    double GetOperand();
    
private:
    double _operand;
};


#endif /* operand_h */
