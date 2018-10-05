

#ifndef Snake_hpp
#define Snake_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Food.hpp"
#include "utilities.hpp"


class Snake {
private:
    int xPos, yPos;
    int size = SCALE;
    int length = 0;
    int speed = 1;
    int directionX = -1, directionY = 0;
    sf::RectangleShape shape;
public:
    Snake(bool head);
    
    void moveSnakeX();
    void moveSnakeY();
    
    void setDirection(int dirX, int dirY);
    int getDirectionX() {return directionX;}
    int getDirectionY() {return directionY;}

    void setPositionX(int pos);
    void setPositionY(int pos);
    int getPositionX() {return xPos;}
    int getPositionY() {return yPos;}
    
    void setColor(sf::Color color);
    
    int getSize() {return size;}
    
    void outOfBounds();
    
    void update();
    void draw(sf::RenderWindow& window);
    
};



#endif /* Snake_hpp */
