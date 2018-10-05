#include "Bonus.hpp"

Bonus::Bonus() {};

void Bonus::loadImage(string filename) {
    sf::Image picture;
    if (!picture.loadFromFile(filename)) {
        cout << "Failed to load " << filename << endl;
        return;
    }
    picture.createMaskFromColor(sf::Color::White);
    texture.loadFromImage(picture);
    sprite.setTexture(texture);
    sprite.setOrigin(0, 0);
    sprite.scale(0.5, 0.5);
}


void Bonus::speedUp(Flipper& player1, Flipper& player2, Ball& ball) {
    int speedFactor;
    loadImage("speedUp.png");
    
    
}
