//
//  utilities.cpp
//  Pong
//
//  Created by Anders Fagerli on 09.04.2017.
//  Copyright © 2017 Anders Fagerli. All rights reserved.
//

#include "utilities.hpp"

int randLim(int min, int max) {
    return rand() % (max-min+1) + min;
}
