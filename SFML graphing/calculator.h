#include <SFML/Graphics.hpp>

#ifndef calculator_h
#define calculator_h
#include "stack.h"
#include "queue.h"
#include "graphing.h"
#include "shuntingyard.h"

class Calculator{
public:
    // Initialize all the variables and the window plane
    void init();
    
    // Execute the graphing
    void main();
private:
    WindowSize DefaultWindow;
    sf::RenderWindow window;
    Cartesian vertexX[2],vertexY[2];
    sf::Vertex axis[4];
    
    // Stack c contains all the Cartesian coordinate vertices
    Stack<Cartesian> c;
    
    // Text of the equation displayed on SFML
    sf::Text text;
    
    // String that will be put into the equation
    string s;
    
    double MAX = 10;
    double MIN = -10;
    double INCREMENT = 0.01;
    
    // Evaluate a string expression, with x-coordinate from low to high, and store corresponding coordinates into a stack of Cartesian coordinates
    Stack<Cartesian> PlotExpression(string expression, double low, double high, double increments);
   
};

#endif /* calculator_h */
