//
//  Food.cpp
//  Snake
//
//  Created by Anders Fagerli on 03.05.2017.
//  Copyright © 2017 Anders Fagerli. All rights reserved.
//

#include "Food.hpp"

Food::Food(bool bonus) {
    shape = sf::RectangleShape(sf::Vector2f(size,size));
    shape.setOrigin(0, 0);
    setRandomPosition();
    shape.setPosition(posX, posY);

    if (bonus) {
        randomNum = rand() % bonuses.size();
        switch (randomNum) {
            case 0:;
                shape.setFillColor(sf::Color(255,255,51));
                break;
            case 1:;
                shape.setFillColor(sf::Color::Black);
                break;
            case 2:;
                shape.setFillColor(sf::Color::Blue);
                break;
            case 3:;
                shape.setFillColor(sf::Color::Green);
                break;
            default:;
                shape.setFillColor(color);
                break;
        }
    }
    else {
        shape.setFillColor(color);
    }
}

int Food::getPositionX() {
    return posX;
}
int Food::getPositionY() {
    return posY;
}

void Food::setRandomPosition() {
    posX = randLim(0, WIDTH/SCALE)*SCALE;
    while (posX >= WIDTH - size) {
        posX = randLim(0, WIDTH/SCALE)*SCALE;
    }
    
    posY = randLim(0, HEIGHT/SCALE)*SCALE;
    while (posY >= HEIGHT - size) {
        posY = randLim(0, HEIGHT/SCALE)*SCALE;
    }
}
void Food::setPosition(int x, int y) {
    posX = x;
    posY = y;
}

void Food::setColor(sf::Color color) {
    shape.setFillColor(color);
}

void Food::update() {
    shape.setPosition(posX, posY);
}

void Food::draw(sf::RenderWindow& window) {
    window.draw(shape);
}
