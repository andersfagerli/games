#include "Flipper.hpp"

Flipper::Flipper(int player) {
    
    shape = sf::RectangleShape(sf::Vector2f(height, width));
    shape.setRotation(90);
    shape.setFillColor(sf::Color::White);
    shape.setOrigin(0, 0);
    posY = HEIGHT/2;
    
    if (player == 1) {
        posX = 50;
        shape.setPosition(posX, posY);
    }
    else {
        posX = WIDTH - 30;
        shape.setPosition(posX, posY);
    }
}

int Flipper::getPosY() {
    return posY;
}
int Flipper::getHeight() {
    return height;
}

void Flipper::incrementY(int speed, float time) {
    shape.move(0, speed*time);
    posY = shape.getPosition().y;
}
void Flipper::decrementY(int speed, float time) {
    shape.move(0, -speed*time);
    posY = shape.getPosition().y;
}

void Flipper::update() {
    shape.setPosition(posX, posY);
}
void Flipper::draw(sf::RenderWindow &window) {
    window.draw(shape);
}
