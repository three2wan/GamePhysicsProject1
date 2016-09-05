/**********************************
* Subject: TGD2251 Game Physics   *
* Name: Mohd Syazwan B Mohd Jamil *
* Student ID: 1131121220          *
* Lecturer: Dr. Wong Ya Ping      *
***********************************/

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Border.cpp"
#include "Player.cpp"
#include "Enemy.cpp"
#include <iostream>
#include <windows.h>

sf::Font loadFont(const string& fontFilename = "resources/sansation.ttf")
{
  sf::Font myFont;
  if (!myFont.loadFromFile(fontFilename))
  {
    cout << "Can not load font from " << fontFilename << endl;
    exit(1);
  }
  return myFont;
}

sf::Font loadFont2(const std::string& fontFilename = "resources/04b03.ttf")
{
	sf::Font myFont;
	if (!myFont.loadFromFile(fontFilename))
	{
		std::cout << "Can not load font from " << fontFilename << std::endl;
		exit(1);
	}
	return myFont;
}

int main(){
	
	const float scale = 32.0f;
	
	// Timer for fixed update
	float fixedTimeStep = 0.02f; // 50 times per second
	//sf::Clock fixedUpdateClock;
	sf::Clock clock;
	float timeElapsedSinceLastFrame = 0;
	
	// Window creation
	int windowSizeX = 800, windowSizeY = 600;
	int windowBorderSize = 16;
	sf::RenderWindow window(sf::VideoMode(windowSizeX, windowSizeY), "Run Away, Blocky!");
	
	// Set vSync to true (and as a result, we have a cap of 60FPS)
	window.setVerticalSyncEnabled(true);
	window.setActive();
	
	// Create gravity and world, then assign gravity to world
	b2Vec2 gravity(0.f, 9.81f);
	b2World world(gravity);
	
	//Text instruction
	sf::Font myFont = loadFont();
	sf::Text myText;
	myText.setFont(myFont);  
	myText.setCharacterSize(20);
	myText.setPosition(170.f, 150.f);
	myText.setColor(sf::Color::White);
	myText.setString("Instruction!\n\nPress 'Enter' to start the game\nPress arrow Left / Right to move Left / Right\nHold Spacebar to slowdown Spikey\nTry to avoid hit by Spikey\n");
	
	//Text score
	sf::Font font2 = loadFont2();
	sf::Text text2;
	text2.setFont(font2);
	text2.setCharacterSize(16);
	text2.setPosition(3, -3);
	text2.setColor(sf::Color::White);
	
	
	// Border creation
	sf::Vector2f horizontalBorderSize(windowSizeX, windowBorderSize);
	sf::Vector2f verticalBorderSize(windowBorderSize, windowSizeY - windowBorderSize * 2);
	sf::Vector2f topBorderPos(windowSizeX / 2, windowBorderSize / 2);
	sf::Vector2f bottomBorderPos(windowSizeX / 2, windowSizeY - windowBorderSize / 2);
	sf::Vector2f leftBorderPos(windowBorderSize / 2, windowSizeY / 2);
	sf::Vector2f rightBorderPos(windowSizeX - windowBorderSize / 2, windowSizeY / 2);

	Border topBorder(world, horizontalBorderSize, topBorderPos);
	topBorder.setOutlineThickness(-1);
	topBorder.setOutlineColor(sf::Color::Black);
	topBorder.setFillColor(sf::Color(100, 100, 100));
	Border bottomBorder(world, horizontalBorderSize, bottomBorderPos);
	bottomBorder.setOutlineThickness(-1);
	bottomBorder.setOutlineColor(sf::Color::Black);
	bottomBorder.setFillColor(sf::Color(100, 100, 100));
	Border leftBorder(world, verticalBorderSize, leftBorderPos);
	leftBorder.setOutlineThickness(-1);
	leftBorder.setOutlineColor(sf::Color::Black);
	leftBorder.setFillColor(sf::Color(100, 100, 100));
	Border rightBorder(world, verticalBorderSize, rightBorderPos);
	rightBorder.setOutlineThickness(-1);
	rightBorder.setOutlineColor(sf::Color::Black);
	rightBorder.setFillColor(sf::Color(100, 100, 100));
	
	//create player
	sf::Vector2f playerPos(400.0f, 572.0f);
	Player myPlayer;
	myPlayer.setBodyAndSprite(world, playerPos);
	
	//create enemy
	float enemyPosX = 10 * scale;
	float enemyPosY = 1 * scale;
	sf::Vector2f enemyPos(enemyPosX, enemyPosY);
	Enemy myEnemy[5];
	int maxEnemy = 5;
	
	for (int i = 0; i < maxEnemy; i++) {
		myEnemy[i].setBodyAndSprite(world, enemyPos);
	}
	
	bool started;
	bool reset = true;
	
	while(window.isOpen()){
		sf::Event event;
		
		while(window.pollEvent(event)){
			switch(event.type){
				case sf::Event::Closed: {
					window.close();
					break;
				}
				
				case sf::Event::KeyPressed: {
					switch(event.key.code){
						case sf::Keyboard::Escape:{
							window.close();
							break;
						}
						
						case sf::Keyboard::Return: {
							if(started){
								started = false;
								reset = true;
							}
							else{
								started = true;
								reset = false;
							}
							break;
						}
					}
					break;
				}
			}			
		}
		
		if(started){
			// We get the time elapsed since last frame and add it to timeElapsedSinceLastFrame
			timeElapsedSinceLastFrame += clock.restart().asSeconds();
			
			// If sufficient time has elapsed, we update the physics
			if (timeElapsedSinceLastFrame >= fixedTimeStep)
			{
				// Step is used to update physics position/rotation
				world.Step(fixedTimeStep, //update frequency
					8,                //velocityIterations
					3                 //positionIterations  
				);

				// Update the objects that uses physics
				topBorder.update();
				bottomBorder.update();
				leftBorder.update();
				rightBorder.update();

				myPlayer.update(world);

				for (int i = 0; i < maxEnemy; i++) {
					myEnemy[i].update();
				}
				
				// timeElapsedSinceLastFrame can be higher than fixedTimeStep,
				// so we deduct timeElapsedSinceLastFrame with fixedTimeStep
				timeElapsedSinceLastFrame -= fixedTimeStep;
			}
			
		}
		
		// Rendering
		window.clear(sf::Color(0, 0, 0));
		
		// Render all objects
		window.draw(topBorder.getShape());
		window.draw(bottomBorder.getShape());
		window.draw(leftBorder.getShape());
		window.draw(rightBorder.getShape());
		
		if(reset){
			reset = false;
			started = false;
      
			clock.restart();
		}
		
		if(!started){
			window.draw(myText);
		}
		else{
			myPlayer.draw(window);
			
			float noOfEnemy = 0;
			
			for (int i = 0; i < maxEnemy; i++) {
				myEnemy[i].draw(window);
			}
			
			text2.setString("Time: ");
			window.draw(text2);
		}
		
		window.display();
	}
	
		return 0;
}