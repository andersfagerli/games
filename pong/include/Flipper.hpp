//
//  Flipper.hpp
//  Pong
//
//  Created by Anders Fagerli on 08.04.2017.
//  Copyright © 2017 Anders Fagerli. All rights reserved.
//

#ifndef Flipper_hpp
#define Flipper_hpp

#include <stdio.h>
#include "Ball.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


class Flipper {
private:
    int width = 20;
    int height = 150;
    int posX, posY;
    
    
public:
    sf::RectangleShape shape;
    Flipper(int player);
    
    int getPosY();
    int getHeight();
    
    void incrementY(int speed, float time);
    void decrementY(int speed, float time);
    
    void update();
    void draw(sf::RenderWindow &window);
};

#endif /* Flipper_hpp */
