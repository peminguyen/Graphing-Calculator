#include "token.h"

// Output the token
ostream& operator <<(ostream& outs, const Token& t){
    t.Print(outs);
    return outs;
}
