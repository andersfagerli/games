#include "Ball.hpp"

Ball::Ball(int radius, int startVelX, int startVelY, int posX, int posY) {
    this->radius = radius;
    this->velX = startVelX;
    this->velY = startVelY;
    this->posX = posX;
    this->posY = posY;
    
    shape.setRadius(radius);
    shape.setFillColor(sf::Color::White);
    shape.setOrigin(0, 0);
    shape.setPosition(posX, posY);
}

void Ball::incrementX() {
    posX += velX;
}
void Ball::incrementY() {
    posY += velY;
}

void Ball::bounce() {
    velX *= -1;
    //Flipper::getPosY();
}

bool hitFlipper(const Ball& b, const Flipper& f) {
    return b.shape.getGlobalBounds().intersects(f.shape.getGlobalBounds());
}

int Ball::getVelY() {
    return velY;
}
int Ball::getPosX() {
    return posX;
}
int Ball::getPosY() {
    return posY;
}
void Ball::setPosition(int positionX, int positionY) {
    posX = positionX;
    posY = positionY;
}
void Ball::setVelocity(int velX, int velY) {
    this->velX = velX;
    this->velY = velY;
}

void Ball::update() {
    shape.setPosition(posX, posY);
    if (posY >= HEIGHT || posY <= 0) {
        velY*=-1;
    }
    
}

void Ball::draw(sf::RenderWindow &window) {
    window.draw(shape);
}
