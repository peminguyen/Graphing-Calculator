#include "leftbracket.h"

// Constructor
LeftBracket::LeftBracket(char t){
    _t = t;
}

// Return the type LEFTBRACKET
TokenType LeftBracket::TypeOf() const{
    return LEFTBRACKET;
}

// Print the left bracket
void LeftBracket::Print(ostream& outs) const{
    cout << _t;
}

// Get the left bracket
char LeftBracket::GetLeftBracket(){
    return _t;
}
