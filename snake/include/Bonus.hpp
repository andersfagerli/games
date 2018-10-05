//
//  Bonus.hpp
//  Snake
//
//  Created by Anders Fagerli on 09/05/2017.
//  Copyright © 2017 Anders Fagerli. All rights reserved.
//

#ifndef Bonus_hpp
#define Bonus_hpp

#include <stdio.h>
#include "utilities.hpp"
#include "Food.hpp"

void speedUp(sf::RenderWindow& window, bool isBonus);
void bamboozelColor(std::vector<Snake>& snakes, bool set);
void fiftySetFood(Food& f1, Food& f2, std::vector<Snake> snakes);

#endif /* Bonus_hpp */
