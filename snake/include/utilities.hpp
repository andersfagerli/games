

#ifndef utilities_hpp
#define utilities_hpp

//Include all libraries here
#include "ResourcePath.hpp"
//#include "Snake.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>


struct highScore {
    std::string name;
    int score;
};

const std::vector<std::string> bonuses = {"YELLOW", "BLACK", "BLUE", "GREEN"};
//Black - gjør skjermen og food svart(transparent?), blir vanlig dersom treffer food
//Yellow - speedup
//Blue - reverserer bevegelser

const int HEIGHT = 900;
const int WIDTH = 900;

const int SCALE = 30;

int randLim(int lower, int upper);

//void moveSnakeDirection(sf::Keyboard::Key, std::vector<Snake>& snakes, bool& isPlaying, bool& gameOver);

std::vector<highScore> readScores(std::string filename);

void updateScore(int score, std::string name, std::vector<highScore> &highscores);

void updateHighscoreList(std::string filename, std::vector<highScore> highscores);





#endif /* utilities_hpp */
