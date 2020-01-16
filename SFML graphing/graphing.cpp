#include "graphing.h"

// Convert a Real World Coordinate to a Window Coordinate
//Because real world coordinates and coordinates in SFML are different, we need to convert from real world to window world for display
sf::Vector2f convertCartesiantoWindow(Cartesian& c, WindowSize& p){
    
    sf::Vector2f pos;
    
    // Convert into Window world's (x,y) coordinate
    pos.x= p.plane.left + p.plane.width * (c._x - p.Min._x)/(p.Max._x - p.Min._x);
    pos.y= p.plane.top + p.plane.height * (p.Max._y - c._y)/(p.Max._y-p.Min._y);
    
    return pos;
}

// Plot all the data from a stack of Cartesian coordinates
sf::VertexArray plot(WindowSize& p,Stack<Cartesian>& c)
{
    sf::VertexArray g;
    // Append each Coordinate to the VertexArray
    for (Stack<Cartesian>::Iterator it = c.Begin(); it != c.End(); it++){
        sf::Vector2f pos=convertCartesiantoWindow(*it,p);
        g.append(sf::Vertex(pos,sf::Color::Cyan));
    }
    return g;
}
