

#include "Snake.hpp"

Snake::Snake(bool head) {
    shape.setFillColor(sf::Color::White);
    shape.setOrigin(0, 0);
    if (head) {
        shape = sf::RectangleShape(sf::Vector2f(size,size));
        xPos = WIDTH/2;
        yPos = HEIGHT/2;
        
        shape.setPosition(xPos, yPos);
    }
    else {
        shape = sf::RectangleShape(sf::Vector2f(size,size));
        
        
        shape.setPosition(xPos, yPos);
        
    }
}


void Snake::setDirection(int dirX, int dirY) {
    directionY = dirY;
    directionX = dirX;
}

void Snake::setPositionX(int pos) {
    xPos = pos;
}
void Snake::setPositionY(int pos) {
    yPos = pos;
}

void Snake::setColor(sf::Color color) {
    shape.setFillColor(color);
}

void Snake::moveSnakeX() {
    xPos += speed*directionX*SCALE;
}
void Snake::moveSnakeY() {
    yPos += speed*directionY*SCALE;
}

void Snake::outOfBounds() {
    if (yPos > HEIGHT-size) {
        yPos = 0;
    }
    else if (yPos < 0) {
        yPos = HEIGHT-size;
    }
    else if (xPos > WIDTH-size) {
        xPos = 0;
    }
    else if (xPos < 0) {
        xPos = WIDTH-size;
    }
}


void Snake::update() {
    outOfBounds();
    shape.setPosition(xPos, yPos);
}

void Snake::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

        
        
        
        
        
