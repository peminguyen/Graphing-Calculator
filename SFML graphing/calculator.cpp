#include "calculator.h"

// Initialize all the variables and the window plane
void Calculator::init(){
    // Initialize variables
    MAX = 10;
    MIN = -10;
    INCREMENT = 0.01;
    
    // Set up default plane
    DefaultWindow.Max = Cartesian(MAX,MAX);
    DefaultWindow.Min = Cartesian(MIN,MIN);
    DefaultWindow.plane.width = 1500;
    DefaultWindow.plane.height = 1500;
     
    // Set up x and y-axis
    vertexX[0] = Cartesian(MIN,0);
    vertexX[1] = Cartesian(MAX, 0);
    vertexY[0] = Cartesian(0,MIN);
    vertexY[1] = Cartesian(0,MAX);
     
    axis[0] = sf::Vertex(convertCartesiantoWindow(vertexX[0],DefaultWindow));
    axis[1] = sf::Vertex(convertCartesiantoWindow(vertexX[1],DefaultWindow));
    axis[2] = sf::Vertex(convertCartesiantoWindow(vertexY[0],DefaultWindow));
    axis[3] = sf::Vertex(convertCartesiantoWindow(vertexY[1],DefaultWindow));
     
     // Set up the window
    window.create(sf::VideoMode(1500, 1500), "Graphing calculator");
    window.setVerticalSyncEnabled(true);
    
    // Initialize the string
    s = "x^2";
}

// Execute the graphing
void Calculator::main(){
    
    sf::Font myFont;
    if (!myFont.loadFromFile("/Users/peminguyen1996/Desktop/Graphing Calculator (SFML)/Graphing Calculator (SFML)/font/arial.ttf"))
    {
        cout << "Try again";
    }
    
    float zoom = 1;
    
    // Retrieve the window's default view
    sf::View view1 = window.getDefaultView();
    sf::View view2 = window.getDefaultView();
    
    // Handle events in window
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            
            switch (event.type) {
            // Close the window
                case sf::Event::Closed:
                    window.close();
                    break;
                // Zoom in and out, update MIN, MAX and INCREMENT accordingly from the zoom factor
                case sf::Event::MouseWheelScrolled:
                    if (event.mouseWheelScroll.delta <= -1){
                        zoom = 1.1f;
                        double zoom_rate = 1.1f;
                        MIN *= zoom_rate;
                        MAX *= zoom_rate;
                        INCREMENT *= zoom_rate;
                    }
                    else if (event.mouseWheelScroll.delta >= 1){
                        zoom = 0.9f;
                        double zoom_rate = 0.9f;
                        MIN *= zoom_rate;
                        MAX *= zoom_rate;
                        INCREMENT *= zoom_rate;
                    }
                    // Update the view from zoom
                    view1.setSize(window.getDefaultView().getSize());
                    view1.zoom(zoom);
                    break;
        // When we press LeftShift, we can enter a new string expression until we hit enter
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::LShift){
                        getline(cin, s);
                        text.setString(s);
                        text.setFont(myFont);
                        text.setColor(sf::Color(128, 128, 0));
                        text.setScale(2.f, 2.f);
                        text.setPosition(100, 100);
                    }
                    break;
            }
        }
        
        // After evaluating the value from string, store all the Cartesian coordinates in a VertexArray v;
        c = PlotExpression(s, MIN, MAX, INCREMENT);
        sf::VertexArray v = plot(DefaultWindow, c);
        
        // Reset the window plane after zoom
        DefaultWindow.Max = Cartesian(MAX,MAX);
        DefaultWindow.Min = Cartesian(MIN,MIN);
        
        vertexX[0] = Cartesian(MIN,0);
        vertexX[1] = Cartesian(MAX, 0);
        vertexY[0] = Cartesian(0,MIN);
        vertexY[1] = Cartesian(0,MAX);
        
        axis[0] = sf::Vertex(convertCartesiantoWindow(vertexX[0],DefaultWindow));
        axis[1] = sf::Vertex(convertCartesiantoWindow(vertexX[1],DefaultWindow));
        axis[2] = sf::Vertex(convertCartesiantoWindow(vertexY[0],DefaultWindow));
        axis[3] = sf::Vertex(convertCartesiantoWindow(vertexY[1],DefaultWindow));
       
        // Clear the window
        window.clear(sf::Color::Black);
        
        // Set view for zoom
        window.setView(view1);
        window.draw(v);
        
        // Set view for static even when zoom
        window.setView(view2);
        window.draw(axis,4,sf::Lines);
        window.draw(text);
        
        window.display();
        
        // Reset the stack c to 0 to get new coordinates
        c.Clear();
    }
}

// Evaluate a string expression, with x-coordinate from low to high, and store corresponding coordinates into a stack of Cartesian coordinates
Stack<Cartesian> Calculator::PlotExpression(string expression, double low, double high, double increments){
    Stack<Cartesian> c;
    Queue<Token*> infix = StringToInfix(expression);
    Queue<Token*> postfix = InfixToPostfix(infix);

    for (double i = low; i <= high; i+= increments)
        c.Push(Cartesian(i,EvaluatePostfix(postfix,i)));
    return c;
}



