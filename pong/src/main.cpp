#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Ball.hpp"
#include "Flipper.hpp"
#include "Bonus.hpp"
#include "ResourcePath.hpp"


using namespace std;

/*bool hitFlipper(const Ball& b, const Flipper& f) {
 return b.shape.getGlobalBounds().intersects(f.shape.getGlobalBounds());
 }*/


int main() {
    srand(time(nullptr));
    
    // Create the main window
    //int const HEIGHT = 1000, WIDTH = 2000;, see Ball.hpp
    sf::ContextSettings settings;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Pong!", sf::Style::Close, settings);
    window.setFramerateLimit(60);
    
    sf::Font font;
    if (!font.loadFromFile(resourcePath()+"sansation.ttf")) {
        return EXIT_FAILURE;
    }
    
    // Flipped coordinates
    sf::View view(window.getView());
    view.setSize(WIDTH, -HEIGHT);
    window.setView(view);
    
    // Clock
    sf::Clock clock;
    sf::Clock bonusClock;
    
    // Set flippers
    Flipper player1(1);
    Flipper player2(2);
    
    // Text in menu
    sf::Text pong("PONG", font, 200);
    pong.setFillColor(sf::Color::White);
    pong.move(WIDTH/2-250, 50);
    
    sf::Text play1("MULTIPLAYER", font, 50);
    play1.setFillColor(sf::Color::White);
    play1.move(WIDTH/2-130, HEIGHT/2);
    
    sf::Text play2("ONE PLAYER", font, 50);
    play2.setFillColor(sf::Color::White);
    play2.move(WIDTH/2-125, HEIGHT/2+200);
    
    
    // Menu
    bool isPlaying = false;
    bool isPlayingMulti = false;
    bool isPlayingSingle = false;
    
    
    // Player parameters
    int score1 = 0;
    int score2 = 0;
    int flipperSpeed = 800;
    
    // Scores shown in window
    sf::Text player1_text(to_string(score1), font, 50);
    player1_text.setFillColor(sf::Color::White);
    player1_text.move(WIDTH/2 - 100, 0);
    
    sf::Text player2_text(to_string(score2), font, 50);
    player2_text.setFillColor(sf::Color::White);
    player2_text.move(WIDTH/2 + 80, 0);
    
    // Create barrier
    sf::RectangleShape barrier;
    barrier.setFillColor(sf::Color::White);
    barrier.setSize(sf::Vector2f(5,50));
    barrier.setOrigin(0, 0);
    int yPosition = HEIGHT-50;
    barrier.setPosition(WIDTH/2, yPosition);
    
    // Bonus items
    vector<int> bonusList;
    int randInt;
    Bonus bonus;
    
    // Ball parameters
    int radius = 20;
    int startSpeedX = 20;
    int startSpeedY = 20;
    int xSpeed;
    int ySpeed;
    int directionX;
    int directionY;
    
    // Set ball
    Ball ball(radius,startSpeedX,startSpeedY,WIDTH/2,HEIGHT/2);
    
    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Q) {
                window.close();
                break;
            }
            
            // Menu
            if (!isPlaying) {
                float mouseX = sf::Mouse::getPosition(window).x;
                float mouseY = sf::Mouse::getPosition(window).y;
                
                if (mouseY < HEIGHT/2+50 && mouseY > HEIGHT/2 && mouseX < WIDTH/2+175 && mouseX > WIDTH/2-125) {
                    play1.setStyle(sf::Text::Bold | sf::Text::Underlined);
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                        isPlaying = true;
                        isPlayingMulti = true;
                        bonusClock.restart().asSeconds();
                        break;
                    }
                }
                else if (mouseY < HEIGHT/2+250 && mouseY > HEIGHT/2+200 && mouseX < WIDTH/2+175 && mouseX > WIDTH/2-125) {
                    play2.setStyle(sf::Text::Bold | sf::Text::Underlined);
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                        isPlaying = true;
                        isPlayingSingle = true;
                        bonusClock.restart().asSeconds();
                        break;
                    }
                    
                }
                else {
                    play1.setStyle(sf::Text::Regular);
                    play2.setStyle(sf::Text::Regular);
                }
            }
            
        }
        // Multiplayer loop
        if (isPlayingMulti) {
            float deltaTime = clock.restart().asSeconds();
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player1.getPosY() < HEIGHT-120) {
                player1.incrementY(flipperSpeed, deltaTime);
            }
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && player1.getPosY() > 20) {
                player1.decrementY(flipperSpeed, deltaTime);
            }
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::K) && player2.getPosY() < HEIGHT-120) {
                player2.incrementY(flipperSpeed, deltaTime);
            }
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::M) && player2.getPosY() > 20) {
                player2.decrementY(flipperSpeed, deltaTime);
            }
            
            //Resets ball and updates scores if out of bounds
            if (ball.getPosX() < -10) {
                score2++;
                ball.setPosition(WIDTH/2, HEIGHT/2);
                clock.restart();
                bonusClock.restart();
            }
            else if (ball.getPosX() > WIDTH+10) {
                score1++;
                ball.setPosition(WIDTH/2, HEIGHT/2);
                clock.restart();
                bonusClock.restart();
            }
            
            //Reverses movement of ball if it hits flippers
            if (ball.shape.getGlobalBounds().intersects(player1.shape.getGlobalBounds())) {
                directionX = 1;
                if (xSpeed > 0) {
                    directionX = -1;
                }
                
                if (ball.getPosY() < player1.getPosY()-player1.getHeight()/2+player1.getHeight()/4){
                    directionY = -1;
                    xSpeed = randLim(startSpeedX-2, startSpeedX+2)*directionX;
                    ySpeed = randLim(startSpeedY-2, startSpeedY+2)*directionY;
                    ball.setVelocity(xSpeed,ySpeed);
                }
                else if (ball.getPosY() < player1.getPosY()-player1.getHeight()/2+player1.getHeight()*2/4) {
                    directionY = -1;
                    xSpeed = randLim(startSpeedX+5, startSpeedX+8)*directionX;
                    ySpeed = randLim(1, 5)*directionY;
                    ball.setVelocity(xSpeed,ySpeed);
                }
                else if (ball.getPosY() < player1.getPosY()-player1.getHeight()/2+player1.getHeight()*3/4){
                    directionY = 1;
                    xSpeed = randLim(startSpeedX+5, startSpeedX+8)*directionX;
                    ySpeed = randLim(1, 5)*directionY;
                    ball.setVelocity(xSpeed,ySpeed);
                }
                else {
                    directionY = 1;
                    xSpeed = randLim(startSpeedX-2, startSpeedX+2)*directionX;
                    ySpeed = randLim(startSpeedY-2, startSpeedY+2)*directionY;
                    ball.setVelocity(xSpeed,ySpeed);
                }
            }
            else if (ball.shape.getGlobalBounds().intersects(player2.shape.getGlobalBounds())) {
                directionX = 1;
                if (xSpeed > 0) {
                    directionX = -1;
                }
                
                if (ball.getPosY() < player2.getPosY()-player2.getHeight()/2+player2.getHeight()/4){
                    directionY = -1;
                    xSpeed = randLim(startSpeedX-2, startSpeedX+2)*directionX;
                    ySpeed = randLim(startSpeedY-2, startSpeedY+2)*directionY;
                    ball.setVelocity(xSpeed,ySpeed);
                }
                else if (ball.getPosY() < player2.getPosY()-player2.getHeight()/2+player2.getHeight()*2/4) {
                    directionY = -1;
                    xSpeed = randLim(startSpeedX+5, startSpeedX+8)*directionX;
                    ySpeed = randLim(1, 5)*directionY;
                    ball.setVelocity(xSpeed,ySpeed);
                }
                else if (ball.getPosY() < player2.getPosY()-player2.getHeight()/2+player2.getHeight()*3/4){
                    directionY = 1;
                    xSpeed = randLim(startSpeedX+5, startSpeedX+8)*directionX;
                    ySpeed = randLim(1, 5)*directionY;
                    ball.setVelocity(xSpeed,ySpeed);
                }
                else {
                    directionY = 1;
                    xSpeed = randLim(startSpeedX-2, startSpeedX+2)*directionX;
                    ySpeed = randLim(startSpeedY-2, startSpeedY+2)*directionY;
                    ball.setVelocity(xSpeed,ySpeed);
                }
            }
            
            if (bonusClock.restart().asSeconds() > 15) {
                
                randInt = randLim(0, 2);
                switch (randInt) {
                    case 0:;
                        //
                        break;
                    case 1:;
                        //
                        break;
                    case 2:;
                        //
                        break;
                    default:;
                        break;
                }
                
                if (bonusClock.restart().asSeconds() > 30) {
                    bonusClock.restart();
                }
            }
            
            // Move ball
            ball.incrementY();
            ball.incrementX();
            
            // Update scores in window
            player1_text.setString(to_string(score1));
            player2_text.setString(to_string(score2));
            
        }
        // Singleplayer loop
        if (isPlayingSingle) {
            float deltaTime = clock.restart().asSeconds();
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player1.getPosY() < HEIGHT-120) {
                player1.incrementY(flipperSpeed, deltaTime);
            }
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && player1.getPosY() > 20) {
                player1.decrementY(flipperSpeed, deltaTime);
            }
            
            // Computer
            if (player2.getPosY() < HEIGHT - 120 && player2.getPosY() > 20) {
                player2.shape.setPosition(WIDTH-30, ball.getPosY()); // Follows ball's y - position
            }
            
            //Resets ball and updates scores if out of bounds
            if (ball.getPosX() < -10) {
                score2++;
                ball.setPosition(WIDTH/2, HEIGHT/2);
                clock.restart();
            }
            else if (ball.getPosX() > WIDTH+10) {
                score1++;
                ball.setPosition(WIDTH/2, HEIGHT/2);
                clock.restart();
            }
            
            //Reverses movement of ball if it hits flippers
            if (ball.shape.getGlobalBounds().intersects(player1.shape.getGlobalBounds())) {
                directionX = 1;
                if (xSpeed > 0) {
                    directionX = -1;
                }
                
                if (ball.getPosY() < player1.getPosY()-player1.getHeight()/2+player1.getHeight()/4){
                    directionY = -1;
                    xSpeed = randLim(startSpeedX-2, startSpeedX+2)*directionX;
                    ySpeed = randLim(startSpeedY-2, startSpeedY+2)*directionY;
                    ball.setVelocity(xSpeed,ySpeed);
                }
                else if (ball.getPosY() < player1.getPosY()-player1.getHeight()/2+player1.getHeight()*2/4) {
                    directionY = -1;
                    xSpeed = randLim(startSpeedX+5, startSpeedX+8)*directionX;
                    ySpeed = randLim(1, 5)*directionY;
                    ball.setVelocity(xSpeed,ySpeed);
                }
                else if (ball.getPosY() < player1.getPosY()-player1.getHeight()/2+player1.getHeight()*3/4){
                    directionY = 1;
                    xSpeed = randLim(startSpeedX+5, startSpeedX+8)*directionX;
                    ySpeed = randLim(1, 5)*directionY;
                    ball.setVelocity(xSpeed,ySpeed);
                }
                else {
                    directionY = 1;
                    xSpeed = randLim(startSpeedX-2, startSpeedX+2)*directionX;
                    ySpeed = randLim(startSpeedY-2, startSpeedY+2)*directionY;
                    ball.setVelocity(xSpeed,ySpeed);
                }
            }
            else if (ball.shape.getGlobalBounds().intersects(player2.shape.getGlobalBounds())) {
                directionX = 1;
                if (xSpeed > 0) {
                    directionX = -1;
                }
                
                if (ball.getPosY() < player2.getPosY()-player2.getHeight()/2+player2.getHeight()/4){
                    directionY = -1;
                    xSpeed = randLim(startSpeedX-2, startSpeedX+2)*directionX;
                    ySpeed = randLim(startSpeedY-2, startSpeedY+2)*directionY;
                    ball.setVelocity(xSpeed,ySpeed);
                }
                else if (ball.getPosY() < player2.getPosY()-player2.getHeight()/2+player2.getHeight()*2/4) {
                    directionY = -1;
                    xSpeed = randLim(startSpeedX+5, startSpeedX+8)*directionX;
                    ySpeed = randLim(1, 5)*directionY;
                    ball.setVelocity(xSpeed,ySpeed);
                }
                else if (ball.getPosY() < player2.getPosY()-player2.getHeight()/2+player2.getHeight()*3/4){
                    directionY = 1;
                    xSpeed = randLim(startSpeedX+5, startSpeedX+8)*directionX;
                    ySpeed = randLim(1, 5)*directionY;
                    ball.setVelocity(xSpeed,ySpeed);
                }
                else {
                    directionY = 1;
                    xSpeed = randLim(startSpeedX-2, startSpeedX+2)*directionX;
                    ySpeed = randLim(startSpeedY-2, startSpeedY+2)*directionY;
                    ball.setVelocity(xSpeed,ySpeed);
                }
            }
            
            
            // Move ball
            ball.incrementY();
            ball.incrementX();
            
            // Update scores in window
            player1_text.setString(to_string(score1));
            player2_text.setString(to_string(score2));
            
        }
        
        
        
        window.clear();
        
        //Display objects in window
        if (isPlayingMulti) {
            // Update objects
            ball.update();
            //player1.update();
            //player2.update();
            
            // Draw objects
            ball.draw(window);
            player1.draw(window);
            player2.draw(window);
            window.draw(barrier);
            
            
            // Draw scores
            view.setSize(WIDTH, HEIGHT);
            window.setView(view);
            window.draw(player1_text);
            window.draw(player2_text);
            
            
            // Reset coordinates
            view.setSize(WIDTH, -HEIGHT);
            window.setView(view);
            
            window.display();
        }
        
        else if (isPlayingSingle) {
            // Update objects
            ball.update();
            //player1.update();
            //player2.update();
            
            // Draw objects
            ball.draw(window);
            player1.draw(window);
            player2.draw(window);
            window.draw(barrier);
            
            
            // Draw scores
            view.setSize(WIDTH, HEIGHT);
            window.setView(view);
            window.draw(player1_text);
            window.draw(player2_text);
            
            
            // Reset coordinates
            view.setSize(WIDTH, -HEIGHT);
            window.setView(view);
            
            window.display();
        }
        
        else {
            view.setSize(WIDTH, HEIGHT);
            window.setView(view);
            window.draw(pong);
            window.draw(play1);
            window.draw(play2);
            
            view.setSize(WIDTH, -HEIGHT);
            window.setView(view);
            player1.draw(window);
            player2.draw(window);
            
            window.display();
        }
        
    }
    
    
    return EXIT_SUCCESS;
}

