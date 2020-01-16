#ifndef windowsize_h
#define windowsize_h

#include <SFML/Graphics.hpp>
#include "cartesian.h"

//Struct to set size for the window plane
struct WindowSize {
public:
    //window plane
    sf::FloatRect plane;
    
    // Max and min coordinates
    Cartesian Max;
    Cartesian Min;
};

#endif /* windowsize_h */
