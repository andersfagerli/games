
#include "ResourcePath.hpp"
#include "utilities.hpp"
#include "Snake.hpp"
#include "Food.hpp"
#include "Bonus.hpp"

using namespace std;

void moveSnakeDirection(std::vector<Snake>& snakes, bool& isPlaying, bool& gameOver);
void reverseMove(std::vector<Snake>& snakes, bool& isPlaying, bool& gameOver);

int main() {
    srand(time(nullptr));

    sf::ContextSettings settings;
    sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT), "Snake", sf::Style::Close, settings);
    window.setFramerateLimit(15);
    
    sf::View view(window.getView());
    view.setSize(WIDTH, -HEIGHT);
    window.setView(view);
    
    sf::Font font;
    if (!font.loadFromFile(resourcePath()+"sansation.ttf")) {
        return EXIT_FAILURE;
    }
    
    int lengthOfSnake = 1;
    
    //All text on screen and centering
    sf::Text score(to_string(lengthOfSnake), font, 500);
    score.setFillColor(sf::Color(230,230,230, 200));
    
    sf::Text playGame("PLAY", font, 70);
    playGame.setFillColor(sf::Color::White);
    
    sf::Text highscores("HIGHSCORES", font, 70);
    highscores.setFillColor(sf::Color::White);
    
    sf::Text back("BACK", font, 50);
    back.setFillColor(sf::Color::White);
    back.setOrigin(0, 0);
    back.setPosition(WIDTH/2-70, HEIGHT-100);
    
    sf::Text playerHighScores("", font, 50);
    playerHighScores.setFillColor(sf::Color::White);
    playerHighScores.setOrigin(0, 0);
    playerHighScores.setPosition(300, 150);
    
    sf::Text playerName("", font, 50);
    playerName.setFillColor(sf::Color::Black);
    
    sf::Text initials("PLAYER:", font, 50);
    initials.setFillColor(sf::Color::White);
    
    sf::RectangleShape textBox(sf::Vector2f(150,50));
    textBox.setFillColor(sf::Color(244,244,244));
    
    sf::FloatRect textRect = score.getLocalBounds();
    score.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    score.setPosition(sf::Vector2f(WIDTH/2.0f, HEIGHT/2.0f));
    
    sf::FloatRect textRect2 = playGame.getLocalBounds();
    playGame.setOrigin(textRect2.left + textRect2.width/2.0f, textRect2.top + textRect2.height/2.0f);
    playGame.setPosition(sf::Vector2f(WIDTH/2.0f, HEIGHT/2.0f-100));
    
    sf::FloatRect textRect3 = highscores.getLocalBounds();
    highscores.setOrigin(textRect3.left + textRect3.width/2.0f, textRect3.top + textRect3.height/2.0f);
    highscores.setPosition(sf::Vector2f(WIDTH/2.0f, HEIGHT/2.0f+100));
    
    sf::FloatRect textRect4 = playerName.getLocalBounds();
    playerName.setOrigin(textRect4.left + textRect4.width/2.0f, textRect4.top + textRect4.height/2.0f);
    playerName.setPosition(sf::Vector2f(WIDTH/2.0f, HEIGHT/2.0f));
    
    sf::FloatRect textRect5 = textBox.getLocalBounds();
    textBox.setOrigin(textRect5.left + textRect5.width/2.0f, textRect5.top + textRect5.height/2.0f);
    textBox.setPosition(sf::Vector2f(WIDTH/2.0f, HEIGHT/2.0f));
    
    sf::FloatRect textRect6 = initials.getLocalBounds();
    initials.setOrigin(textRect6.left + textRect6.width/2.0f, textRect6.top + textRect6.height/2.0f);
    initials.setPosition(sf::Vector2f(WIDTH/2.0f, HEIGHT/2.0f-100));
    
    sf::String userInput;
    
    sf::Clock clock;
    
    
    bool snakeHead = true;
    bool generateBonus = false;
    Snake head(snakeHead);
    Food* f = new Food(generateBonus);
    
    //List of snake objects
    vector<Snake> snakes;
    snakes.push_back(head);
    
    //Bools used in game loops
    bool gameOver = false;
    bool isPlaying = false;
    bool inHighscores = false;
    bool writingName = false;
    
    //Mouse positions
    float mouseX;
    float mouseY;
    
    //List of current highscores
    vector<highScore> highscore;
    
    //Name of player
    string name;
    
    //Variables for bonus
    int prevRand;
    int randomBonusScore = randLim(10, 20);
    bool increaseSpeed;
    bool blackOut;
    bool bamboozle;
    bool fiftyfifty;
    Food* f2;
    
    //Background color
    sf::Color background = sf::Color(0,170,190);
    
    
    while (window.isOpen()) {
        sf::Event event;
        
        if (gameOver) {
            //Update highscores if highscore
            highscore = readScores("/Users/andersfagerli/Documents/C++/Snake/Snake/highscores.txt");
            updateScore(lengthOfSnake, name, highscore); //Oppdaterer highscore liste hvis det er highscore
            updateHighscoreList("/Users/andersfagerli/Documents/C++/Snake/Snake/highscores.txt", highscore);

            lengthOfSnake = 1;
            unsigned long length = snakes.size();
            for (int i = 1; i < length; i++) {
                snakes.pop_back();
            }
            gameOver = false;
            
            //Reset bonuses
            randomBonusScore = randLim(10, 20);
            prevRand = false;
            increaseSpeed = false;
            background = sf::Color(0,170,190);
            f->setColor(sf::Color::Red);
            bamboozle = false;
            if (fiftyfifty) {
                delete f2;
                fiftyfifty = false;
            }
            
        }
        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Q || event.key.code == sf::Keyboard::Escape) {
                window.close();
                break;
            }
            
            if (inHighscores == true) {
                mouseX = sf::Mouse::getPosition(window).x;
                mouseY = sf::Mouse::getPosition(window).y;
                highscore = readScores("/Users/andersfagerli/Documents/C++/Snake/Snake/highscores.txt");
                
                playerHighScores.setString(highscore[0].name + "\t\t" + to_string(highscore[0].score)+"\n\n" +
                                           highscore[1].name + "\t\t" + to_string(highscore[1].score)+"\n\n" +
                                           highscore[2].name + "\t\t" + to_string(highscore[2].score)+"\n\n" +
                                           highscore[3].name + "\t\t" + to_string(highscore[3].score)+"\n\n" +
                                           highscore[4].name + "\t\t" + to_string(highscore[4].score));
                
                //Gå tilbake
                if (mouseX > back.getPosition().x && mouseX < back.getPosition().x+150 && mouseY > back.getPosition().y && mouseY < back.getPosition().y +50) {
                    back.setStyle(sf::Text::Bold | sf::Text::Italic);
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        inHighscores = false;
                    }
                }
                else {
                    back.setStyle(sf::Text::Regular);
                }
                break;
            }
            
            if (writingName == true) {
                    if (event.type == sf::Event::TextEntered) {
                        if (userInput.getSize() < 3) {
                            userInput.insert(userInput.getSize(), event.text.unicode);
                        }
                    }
                    else if (event.key.code == sf::Keyboard::BackSpace) {
                        userInput.erase(userInput.getSize()-1);
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                        name = userInput;
                        transform(name.begin(), name.end(), name.begin(), ::toupper);
                        userInput = "";
                        writingName = false;
                        isPlaying = true;
                    }
                
                break;
            }
            
            if (isPlaying == false) {
                mouseX = sf::Mouse::getPosition(window).x;
                mouseY = sf::Mouse::getPosition(window).y;
                if (mouseX > highscores.getPosition().x-220 && mouseX < highscores.getPosition().x+250 && mouseY > highscores.getPosition().y-40 && mouseY < highscores.getPosition().y + 40) {
                    highscores.setStyle(sf::Text::Bold | sf::Text::Italic);
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        inHighscores = true;
                    }
                }
                else if (mouseX > playGame.getPosition().x-100 && mouseX < playGame.getPosition().x+100 && mouseY > playGame.getPosition().y-40 && mouseY < playGame.getPosition().y + 40) {
                    playGame.setStyle(sf::Text::Bold | sf::Text::Italic);
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        writingName = true;
                    }
                }
                else {
                    highscores.setStyle(sf::Text::Regular);
                    playGame.setStyle((sf::Text::Regular));
                }
                break;
            }
            
            //Move snake in direction
            if (bamboozle) {
                reverseMove(snakes, isPlaying, gameOver);
            }
            else {
                moveSnakeDirection(snakes, isPlaying, gameOver);
            }
            
            
        }
        
        //Playing loop
        if (isPlaying == true) {
            //Slangen spiser
            if (f->getPositionY() == snakes[0].getPositionY() && f->getPositionX() == snakes[0].getPositionX()) {
                Snake tail(!snakeHead);
                snakes.push_back(tail);
                if (fiftyfifty) {
                    fiftyfifty = false;
                    delete f2;
                }
                lengthOfSnake++;
                
                background = sf::Color(0,170,190);
                
                if (prevRand == true) { //Aktiverer bonus
                    switch (f->getRandomNum()) {
                        case 0:
                            increaseSpeed = true;
                            clock.restart();
                            speedUp(window, increaseSpeed);
                            break;
                        case 1:
                            background = sf::Color::Black;
                            blackOut = true;
                            break;
                        case 2:
                            bamboozle = true;
                            bamboozelColor(snakes, bamboozle);
                            clock.restart();
                            break;
                        /*case 3:
                            fiftyfifty = true;
                            break;
                        default:
                            break;
                         */
                    }
                    prevRand = false;

                }
                
                if (lengthOfSnake == randomBonusScore) { //Aktiverer bonus food
                    generateBonus = true;
                    prevRand = true;
                    randomBonusScore += randLim(10, 20); //Ny score som kreves for bonus
                }
                
                delete f;
                f = new Food(generateBonus);
                if (fiftyfifty) {
                    f2 = new Food(generateBonus);
                    fiftySetFood(*f, *f2, snakes);
                    
                }
                generateBonus = false;
                
                for (int i = 0; i < snakes.size(); i++) {
                    if (f->getPositionY() == snakes[i].getPositionY() && f->getPositionX() == snakes[i].getPositionX()) {
                        f->setRandomPosition();
                        i = 0;
                    }
                }
            }
            
            //Bonus checks
            if (blackOut == true) {
                f->setColor(sf::Color::Transparent);
                blackOut = false;
            }
            
            if (increaseSpeed == true && clock.getElapsedTime().asSeconds() > 15) { //SpeedUp for 15 seconds
                increaseSpeed = false;
                speedUp(window, increaseSpeed);
            }
            
            if (bamboozle == true && clock.getElapsedTime().asSeconds() > 15) {
                bamboozle = false;
                bamboozelColor(snakes, bamboozle);
            }
            
            if (fiftyfifty == true && snakes[0].getPositionX() == f2->getPositionX() && snakes[0].getPositionY() == f2->getPositionY()) {
                gameOver = true;
            }
            
            for (unsigned long i = snakes.size()-1; i >= 1; i--) { //Oppdaterer posisjonen til hver bit
                snakes[i].setPositionX(snakes[i-1].getPositionX());
                snakes[i].setPositionY(snakes[i-1].getPositionY());
            }
            
            snakes[0].moveSnakeX();
            snakes[0].moveSnakeY();
            
            for (int i = 1; i < snakes.size(); i++) {
                if (snakes[0].getPositionX() == snakes[i].getPositionX() && snakes[0].getPositionY() == snakes[i].getPositionY()){
                    gameOver = true;
                }
            }
            
            score.setString(to_string(lengthOfSnake));
        }
        
        
        
        //Draw
        window.clear(background);
        
        if (isPlaying == true) {
            view.setSize(WIDTH, -HEIGHT);
            window.setView(view);
            
            f->update();
            
            //Center text
            textRect = score.getLocalBounds();
            score.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
            score.setPosition(sf::Vector2f(WIDTH/2.0f, HEIGHT/2.0f));
            
            //Draw text without flipped coordinates
            view.setSize(WIDTH, HEIGHT);
            window.setView(view);
            
            window.draw(score);
            
            view.setSize(WIDTH, -HEIGHT);
            window.setView(view);
            
            for (int i = 0; i < snakes.size(); i++) {
                snakes[i].update();
                snakes[i].draw(window);
            }
            
            f->draw(window);
            if (fiftyfifty) {
                f2->draw(window);
            }
        }
        else if (inHighscores == true) {
            view.setSize(WIDTH, HEIGHT);
            window.setView(view);
            
            window.draw(playerHighScores);
            window.draw(back);
        }
        else if (writingName == true) {
            view.setSize(WIDTH, HEIGHT);
            window.setView(view);
            
            playerName.setString(userInput);
            
            textRect4 = playerName.getLocalBounds();
            playerName.setOrigin(textRect4.left + textRect4.width/2.0f, textRect4.top + textRect4.height/2.0f);
            playerName.setPosition(sf::Vector2f(WIDTH/2.0f, HEIGHT/2.0f));
            
            window.draw(initials);
            window.draw(textBox);
            window.draw(playerName);
            
        }
        else {
            view.setSize(WIDTH, HEIGHT);
            window.setView(view);
            
            window.draw(playGame);
            window.draw(highscores);
            
        }
        
        
        window.display();
        
    }
    
    return 0;
}




void moveSnakeDirection(std::vector<Snake>& snakes, bool& isPlaying, bool& gameOver) {
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
    
}

void reverseMove(std::vector<Snake>& snakes, bool& isPlaying, bool& gameOver) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        if (snakes[0].getDirectionY() != -1) {
            snakes[0].setDirection(0,1);
            return;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        if (snakes[0].getDirectionY() != 1) {
            snakes[0].setDirection(0,-1);
            return;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if (snakes[0].getDirectionX() != 1) {
            snakes[0].setDirection(-1,0);
            return;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
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
    
}



