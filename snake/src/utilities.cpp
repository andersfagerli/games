//
//  utilities.cpp
//  Snake
//
//  Created by Anders Fagerli on 02.05.2017.
//  Copyright © 2017 Anders Fagerli. All rights reserved.
//

#include "utilities.hpp"
using namespace std;

int randLim(int lower, int upper) {
    return rand() % (upper - lower + 1) + lower;
}

std::vector<highScore> readScores(std::string filename) {
    std::ifstream input(filename);
    if (input.fail()) {
        std::cout << "Feil under lesing av fil" << std::endl;
        exit(1);
    }
    
    highScore h;
    std::vector<highScore> highscores;
    std::string name, score;
    
    while (!input.eof()) {
        input >> name;
        input >> score;
        if (highscores.size() < 5) {
            h.name = name;
            h.score = std::stoi(score);
            
            highscores.push_back(h);
        }
    }
    
    input.close();
    return highscores;
}

void updateScore(int score, std::string name, std::vector<highScore>& highscores) {
    for (int i = 0; i < highscores.size(); i++) {
        if (score > highscores[i].score) {
            for (unsigned long j = highscores.size()-1; j > i; j--) {
                highscores[j].score = highscores[j-1].score;
                highscores[j].name = highscores[j-1].name;
            }
            highscores[i].score = score;
            highscores[i].name = name;
            break;
        }
    }
}

void updateHighscoreList(std::string filename, std::vector<highScore> highscores) {
    std::ofstream output;
    output.open(filename);
    
    if (output.fail()) {
        std::cout << "Feil under oppdatering av fil" << std::endl;
        exit(1);
    }
    
    for (int i = 0; i < highscores.size(); i++) {
        output << highscores[i].name;
        output << " ";
        output << highscores[i].score;
        if (i != highscores.size()-1) {
            output << std::endl;
        }
    }
    
    output.close();
    
}

/*void moveSnakeDirection(sf::Keyboard::Key, std::vector<Snake>& snakes, bool& isPlaying, bool& gameOver) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        if (snakes[0].getDirectionY() != -1) {
            snakes[0].setDirection(0,1);
            return;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        if (snakes[0].getDirectionY() != 1) {
            snakes[0].setDirection(0,-1);
            return;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if (snakes[0].getDirectionX() != 1) {
            snakes[0].setDirection(-1,0);
            return;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if (snakes[0].getDirectionX() != -1) {
            snakes[0].setDirection(1,0);
            return;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        isPlaying = false;
        gameOver = true;
        //set bonuses false
    }

}*/







