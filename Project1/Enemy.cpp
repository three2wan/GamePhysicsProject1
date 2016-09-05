/**********************************
* Subject: TGD2251 Game Physics   *
* Name: Mohd Syazwan B Mohd Jamil *
* Student ID: 1131121220          *
* Lecturer: Dr. Wong Ya Ping      *
***********************************/

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <windows.h>
using namespace std;

class Enemy{
private:
	b2BodyDef bodyDef;
	b2Body* body;
	b2Vec2 velocity;
	b2CircleShape shape;
	b2FixtureDef fixtureDef;
	sf::Keyboard::Key keyControl;
	sf::Texture texture;
	sf::Sprite sprite;
	
	const float scale = 32.0f;
	
	void EnemyMovement(){
		int maxSpeed = 25;
		b2Vec2 velocity = body->GetLinearVelocity();
		float speed = velocity.Length();
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
			maxSpeed = 10;
		}
		
		// If the ball is too fast, apply linear damping to gradually slow down the ball.
		if (speed > maxSpeed) {
			body->SetLinearDamping(0.5);
		}
		// If the ball is too slow, apply linear impulse to gradually fasten the ball.
		else if (speed < maxSpeed - 1) {
			body->SetLinearDamping(0.0);
			// Apply horizontal speed
			if (velocity.x > 0) {
				body->ApplyLinearImpulse(b2Vec2(0.25f, 0), bodyDef.position);
			}
			else {
				body->ApplyLinearImpulse(b2Vec2(-0.25f, 0), bodyDef.position);
			}
			// Apply vertical speed
			if (velocity.y > 0) {
				body->ApplyLinearImpulse(b2Vec2(0, 0.25f), bodyDef.position);
			}
			else {
				body->ApplyLinearImpulse(b2Vec2(0, -0.25f), bodyDef.position);
			}
		}
	}
	
public:
	void setBodyAndSprite(b2World& world, sf::Vector2f position) {
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(position.x / scale, position.y / scale);
		bodyDef.userData = this;
		body = world.CreateBody(&bodyDef);
		shape.m_radius = ((33.f / 2) / scale);
		fixtureDef.shape = &shape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.f;
		fixtureDef.restitution = 1.f;
		fixtureDef.userData = this;
		body->CreateFixture(&fixtureDef);
		body->SetUserData(this);

		if (texture.loadFromFile("Resources/Spikey.png"))
			sprite.setTexture(texture);
		sprite.setOrigin(sf::Vector2f(33 / 2, 33 / 2));
		sprite.setPosition(sf::Vector2f(body->GetPosition().x * scale, body->GetPosition().y * scale));
	}
	
	void update(){
		EnemyMovement();
	}
	
	void draw(sf::RenderWindow& window) {
		sprite.setPosition(sf::Vector2f(body->GetPosition().x * scale, body->GetPosition().y * scale));
		window.draw(sprite);
	}
};