#include "variable.h"

// Constructor
Variable::Variable(char v):_v(v){
    
}

// Print the variable
void Variable::Print(ostream &outs) const{
    cout << _v;
}

// Get the type variable
TokenType Variable::TypeOf() const{
    return VARIABLE;
}

// Get the value of variable
char Variable::GetVariable(){
    return _v;
}
