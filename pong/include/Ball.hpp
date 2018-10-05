

#ifndef Ball_hpp
#define Ball_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Flipper.hpp"
#include "utilities.hpp"

const int HEIGHT = 1000;
const int WIDTH = 2000;

class Ball {
private:
    int radius;
    int velX, velY;
    double posX, posY;
public:
    sf::CircleShape shape;
    Ball(int radius, int startVelX, int startVelY, int posX, int posY);
    
    void incrementX();
    void incrementY();
    
    void bounce();
    
    int getVelY();
    int getPosX();
    int getPosY();
    
    void setPosition(int positionX, int positionY);
    void setVelocity(int velX, int velY);
    
    
    void update();
    void draw(sf::RenderWindow &window);
    
};

#endif /* Ball_hpp */
