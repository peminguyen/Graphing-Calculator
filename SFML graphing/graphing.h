#ifndef graphing_h
#define graphing_h

#include <SFML/Graphics.hpp>
#include "windowsize.h"
#include "cartesian.h"
#include "stack.h"
#include <iostream>
using namespace std;


// Convert Real World Coordinates to Window Coordinates
//Because real world coordinates and coordinates in SFML are different, we need to convert from real world to window world for display
sf::Vector2f convertCartesiantoWindow(Cartesian& c, WindowSize& p);

// Plot all the data from a stack of Cartesian coordinates
sf::VertexArray plot(WindowSize& p, Stack<Cartesian>& c);

#endif /* graphing_h */
