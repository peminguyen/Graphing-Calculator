#include "shuntingyard.h"

// Convert a string to an infix queue
Queue<Token*> StringToInfix(string s){
    ParsedString ps(s);
    Queue<Token*> output;
    string temp;
    char t;
    double d;
    // Loop until no other string to parse
    // Each time we get a new token, push to the output queue
    while (!ps.isEmpty()) {
        temp = ps.nextToken();
        switch (ps.getType()) {
            case OPERAND:
                // Get the number converted from the next string token
                d = ps.getNumber();
                output.Push(new Operand(d));
                break;
                // In other cases, convert the parsed string to character
            case OPERATOR:
                t = temp[0];
                output.Push(new Operator(t));
                break;
            case LEFTBRACKET:
                t = temp[0];
                output.Push(new LeftBracket(t));
                break;
            case RIGHTBRACKET:
                t = temp[0];
                output.Push(new RightBracket(t));
                break;
            // When there is SPACE or COMMA, do nothing
            case SPACE:
                break;
            case COMMA:
                break;
            case VARIABLE:
                t = temp[0];
                output.Push(new Variable(t));
                break;
            case FUNCTION:
                output.Push(new Function(temp));
                break;
            default:
                break;
        }
    }
    return output;
}


// Convert an infix queue to a postfix queue
Queue<Token*> InfixToPostfix(Queue<Token*> infix){
    Queue<Token*> postfix;
    Stack<Token*> s;
    Token* p;
    // While there are still tokens to be read from the input
    while (!(infix.isEmpty())){
        // Pop the token from the input and check its type
        p = infix.Pop();
        switch (p->TypeOf()){
                // If it is a number, push into the output queue
            case OPERAND:{
                postfix.Push(p);
                break;
            }
            case VARIABLE:{
                postfix.Push(p);
                break;
            }
                // If it is a left bracket, push into the operator stack
            case LEFTBRACKET:{
                s.Push(p);
                break;
            }
                // If it is a function, push into the operator stack
            case FUNCTION:{
                s.Push(p);
                break;
            }
                // If it is a right bracket, pop all the operators from the operator stack until the left bracket
                // onto the output queue
            case RIGHTBRACKET:{
                while (!(s.isEmpty()) && (*s.Begin())->TypeOf() != LEFTBRACKET ){
                    postfix.Push(s.Pop());
                }
                s.Pop();
                break;
            }
                // If it is an operator
            case OPERATOR:{
                // while ((there is a function at the top of the operator stack)
                // or (there is an operator at the top of the operator stack with greater precedence)
                // or (the operator at the top of the operator stack has equal precedence and is left associative))
                // and (the operator at the top of the operator stack is not a left bracket):
                // Push to the postfix queue
                while (!(s.isEmpty()) && (((*s.Begin())->TypeOf() == FUNCTION) || (((*s.Begin())->TypeOf() == OPERATOR
                            && (static_cast<Operator*>(*s.Begin())->getPrecendence() > static_cast<Operator*>(p)->getPrecendence() ||
                                    (static_cast<Operator*>(*s.Begin())->getPrecendence() == static_cast<Operator*>(p)->getPrecendence() &&
                            !(static_cast<Operator*>(*s.Begin())->isRightAssociative())) )) )) &&
                       (*s.Begin())->TypeOf() != LEFTBRACKET){
                    postfix.Push(s.Pop());
                }
                // After the while loop, push all the operator in the operator stack
                s.Push(p);
                break;
            }
            default:
                break;
                
        }
    }
    // Push the remaining operators in the operator stack to the postfix queue
    while (!(s.isEmpty())){
        postfix.Push(s.Pop());
    }
    return postfix;
}

// Evaluate the postfix queue
double EvaluatePostfix(Queue<Token*> postfix, double x){
    Stack<Token*> s;
    Token* p;
    double left = 0, right = 0, output = 0;
    
    while (!(postfix.isEmpty())){
        p = postfix.Pop();
        switch (p->TypeOf()){
                // If the type of the node in the Queue is an operand, push it to the Stack
            case OPERAND:{
                s.Push(p);
                break;
            }
            // If the type of the node in the Queue is a variable, push it to the Stack as an Operand
            case VARIABLE:{
                s.Push(new Operand(x));
                break;
            }
            // If the type is an operator, get the operator, pop at the Stack, do the operation then push the result to the Stack
            case OPERATOR:{
                // For unary operators
                if (s.getSize() == 1){
                    right = static_cast<Operand*>(s.Pop())->GetOperand();
                    output = static_cast<Operator*>(p)->evaluate(left, right);
                }
                // For regular operators
                else {
                    right = static_cast<Operand*>(s.Pop())->GetOperand();
                    left = static_cast<Operand*>(s.Pop())->GetOperand();
                    output = static_cast<Operator*>(p)->evaluate(left, right);
                }
                
                s.Push(new Operand(output));
                break;
            }
            // If the type is a function, pop the operand at the stack and push the result to the Stack
            case FUNCTION:{
                switch (static_cast<Function*>(p)->FunctionTypeOf()){
                    // For function of one argument
                    case ONE_ARGUMENT:{
                        right = static_cast<Operand *>(s.Pop())->GetOperand();
                        output = static_cast<Function *>(p)->evaluate(right);
                        break;
                    }
                    // For function of two arguments (min, max)
                    case TWO_ARGUMENT:{
                        right = static_cast<Operand*>(s.Pop())->GetOperand();
                        left = static_cast<Operand*>(s.Pop())->GetOperand();
                        output = static_cast<Function*>(p)->evaluate(left, right);
                        break;
                    }
                }
                s.Push(new Operand(output));
                break;
            }
        }
    }
    return static_cast<Operand*>(*s.Begin())->GetOperand();
}

