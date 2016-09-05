/**********************************
* Subject: TGD2251 Game Physics   *
* Name: Mohd Syazwan B Mohd Jamil *
* Student ID: 1131121220          *
* Lecturer: Dr. Wong Ya Ping      *
***********************************/

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h> 
#include <iostream>
using namespace std;

class Player{
private:
	b2BodyDef bodyDef;
	b2Body* body;
	b2PolygonShape shape;
	b2FixtureDef fixtureDef;
	b2Vec2 prevPos;

	enum control { left, right };
	sf::Keyboard::Key keyControl[2];
	sf::Texture texture;
	sf::Sprite sprite;

	const float scale = 32.0f;
	int speed = 20;
	
	void playerMove() {
		b2Vec2 currentPos = body->GetPosition();
		keyControl[left] = sf::Keyboard::Left;
		keyControl[right] = sf::Keyboard::Right;
		b2Vec2 zeroVel = body->GetLinearVelocity();
		zeroVel.x = 0;
		zeroVel.y = 0;
		body->SetLinearVelocity(zeroVel);

		if (sf::Keyboard::isKeyPressed(keyControl[left])) {
			b2Vec2 vel = body->GetLinearVelocity();
			vel.x = -speed;
			body->SetLinearVelocity(vel);
		}
		else if (sf::Keyboard::isKeyPressed(keyControl[right])) {
			b2Vec2 vel = body->GetLinearVelocity();
			vel.x = speed;
			body->SetLinearVelocity(vel);
		}

		prevPos = body->GetPosition();
	}
	
	void UseAbility(){
		bool useAbility = false;
		sf::Clock clock;
		sf::Time time = clock.getElapsedTime();
				
		/*if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
			if(abilityInterval <= 0.0f && useAbility == true){
				useAbility = false;
				cout << "Not use ability anymore" << endl;
			}
			
			useAbility = true;
			cout << "Use ability" << endl;	
				
		}*/
	}
	
public:
	void setBodyAndSprite(b2World& world, sf::Vector2f position) {
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(position.x / scale, position.y / scale);
		body = world.CreateBody(&bodyDef);
		shape.SetAsBox((64 / 2) / scale, (24 / 2) / scale);
		fixtureDef.shape = &shape;
		fixtureDef.density = 0.3f;
		fixtureDef.friction = 0.5f;
		body->CreateFixture(&fixtureDef);
		body->SetUserData(this);

		if (texture.loadFromFile("Resources/blocky_smile.png"))
			sprite.setTexture(texture);
		sprite.setOrigin(sf::Vector2f(64 / 2, 24 / 2));
		sprite.setPosition(sf::Vector2f(body->GetPosition().x * scale, body->GetPosition().y * scale));
	}

	void update(b2World& world){
		playerMove();
		sprite.setRotation(body->GetAngle() * 180 / b2_pi);
		sprite.setPosition(body->GetPosition().x * scale, body->GetPosition().y * scale);
		
		UseAbility();
	}

	void draw(sf::RenderWindow& window) {
		sprite.setPosition(sf::Vector2f(body->GetPosition().x * scale, body->GetPosition().y * scale));
		window.draw(sprite);
	}
};