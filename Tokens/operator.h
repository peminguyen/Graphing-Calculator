#ifndef operator_h
#define operator_h

#include "token.h"
#include <cmath>

class Operator: public Token{
public:
    // Constructor
    Operator(char o);
    
    // Print an operator
    void Print(ostream& outs = cout) const;
    
    // Get the type of the operator
    TokenType TypeOf() const;
    
    // Get the type from the string
    TokenType getType() const;
    
    // Get the operator
    char GetOperator();
    
    // Evaluate the operation
    double evaluate(const double& left, const double& right);
    
    // Get the precendence from th
    int getPrecendence();
    
    bool isRightAssociative();
    
    
private:
    char _operator;
};

#endif /* operator_h */
