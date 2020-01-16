#ifndef mathfunction_h
#define mathfunction_h

#include "token.h"
#include <cmath>

enum FunctionType {ONE_ARGUMENT, TWO_ARGUMENT, DEFAULT};

class Function: public Token{
public:
    // Constructor
    Function(string f);
    
    // Print the function
    void Print(ostream& outs = cout) const;
    
    // Get the type function
    TokenType TypeOf() const;
    
    // Check what kind of function it is
    FunctionType FunctionTypeOf() const;
    
    // Get the value of function
    string GetFunction();
    
    // Evaluate when the function takes one argument
    double evaluate(const double& a);
    
    // Evaluate when the function takes one argument
    double evaluate(const double& a, const double& b);
    
private:
    string _function;
    FunctionType _ftype;
};

#endif /* mathfunction_h */
