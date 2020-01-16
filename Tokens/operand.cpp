#include "operand.h"

// Constructor
Operand::Operand(double o): _operand(o){
    
}

// Print the operand
void Operand::Print(ostream& outs) const {
    cout << _operand;
}

// Get the type Operand
TokenType Operand::TypeOf() const{
    return OPERAND;
}

// Get the value of operand
double Operand::GetOperand(){
    return _operand;
}
