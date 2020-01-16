#ifndef cartesian_h
#define cartesian_h

// Struct for Cartesian coordinates, which contains x and y coordinates
struct Cartesian {
    double _x;
    double _y;
    // Default constructor
    Cartesian();
    
    // Constructor which takes two coordinate arguments
    Cartesian(double x, double y);
};



#endif /* cartesian_h */
