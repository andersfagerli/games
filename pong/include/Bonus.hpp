

#ifndef Bonus_hpp
#define Bonus_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <iostream>

#include "Ball.hpp"
#include "Flipper.hpp"

using namespace std;

class Bonus {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    
public:
    Bonus();
    void loadImage(string filename);
    
    void speedUp(Flipper& player1, Flipper& player2, Ball& ball);
    
    
    
};


#endif /* Bonus_hpp */
