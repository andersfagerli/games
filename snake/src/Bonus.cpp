//
//  Bonus.cpp
//  Snake
//
//  Created by Anders Fagerli on 09/05/2017.
//  Copyright © 2017 Anders Fagerli. All rights reserved.
//

#include "Bonus.hpp"

void speedUp(sf::RenderWindow& window, bool isBonus) {
    if (isBonus) {
        window.setFramerateLimit(30);
    }
    else {
        window.setFramerateLimit(15);
    }
}

void bamboozelColor(std::vector<Snake>& snakes, bool set) {
    if (set) {
        int randRed;
        int randGreen;
        int randBlue;
        for (int i = 0; i < snakes.size(); i++) {
            randRed = rand() % 256;
            randGreen = rand() % 256;
            randBlue = rand() % 256;
            snakes[i].setColor(sf::Color(randRed,randGreen,randBlue));
        }
    }
    else {
        for (int i = 0; i < snakes.size(); i++) {
            snakes[i].setColor(sf::Color(255,255,255));
        }
    }
}

void fiftySetFood(Food& f1, Food& f2, std::vector<Snake> snakes) {
    int randCol = rand() % 2;
    if (randCol == 0) {
        f1.setColor(sf::Color(0,0,150));
    }
    else {
        f2.setColor(sf::Color(0,0,150));
    }
    int randPos = rand() % 3 - 1;
    while (randPos == 0) {
        randPos = rand() % 3 - 1;
    }
    
    f1.setPosition(WIDTH*WIDTH*0.5/SCALE + randPos*SCALE, HEIGHT*HEIGHT*0.5/SCALE);
    f2.setPosition(WIDTH*WIDTH*0.5/SCALE + randPos*SCALE*-1, HEIGHT*HEIGHT*0.5/SCALE);
    for (int i = 0; i < snakes.size(); i++) {
        if ((f1.getPositionY() == snakes[i].getPositionY() && f1.getPositionX() == snakes[i].getPositionX()) || (f2.getPositionX() == snakes[i].getPositionX() && f2.getPositionY() == snakes[i].getPositionY())) {
            
            f1.setPosition(f1.getPositionX()+SCALE*randPos, f1.getPositionY());
            f2.setPosition(f2.getPositionX()+SCALE*randPos*-1, f2.getPositionY());
            i = 0;
            
        }
    }
}












