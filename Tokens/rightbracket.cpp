#include "rightbracket.h"

// Constructor
RightBracket::RightBracket(char t){
    _t = t;
}

// Return the type RIGHTBRACKET
TokenType RightBracket::TypeOf() const{
    return RIGHTBRACKET;
}

// Print the right bracket
void RightBracket::Print(ostream& outs) const{
    cout << _t;
}

// Get the right bracket
char RightBracket::GetRightBracket(){
    return _t;
}
