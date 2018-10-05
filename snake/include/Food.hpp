

#ifndef Food_hpp
#define Food_hpp

#include <stdio.h>

#include "Snake.hpp"
#include "utilities.hpp"


class Food {
private:
    int size = SCALE;
    int posX, posY;
    
    int randomNum;

    sf::RectangleShape shape;
    sf::Color color = sf::Color::Red;
    
public:
    Food(bool bonus);
    
    int getPositionX();
    int getPositionY();
    void setRandomPosition();
    void setPosition(int x, int y);
    
    int getRandomNum() {return randomNum;}
    
    void setColor(sf::Color color);
    
    void update();
    void draw(sf::RenderWindow& window);
    
};




#endif /* Food_hpp */
