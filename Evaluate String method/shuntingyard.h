#ifndef shuntingyard_h
#define shuntingyard_h

#include "token.h"
#include "operand.h"
#include "operator.h"
#include "leftbracket.h"
#include "rightbracket.h"
#include "mathfunction.h"
#include "variable.h"
#include "queue.h"
#include "stack.h"
#include "parsedstring.h"

// Convert a string to an infix queue
Queue<Token*> StringToInfix(string s);

// Convert an infix queue to a postfix queue
Queue<Token*> InfixToPostfix(Queue<Token*> infix);

// Evaluate the postfix queue
double EvaluatePostfix(Queue<Token*> postfix, double x = 0);

#endif /* shuntingyard_h */
