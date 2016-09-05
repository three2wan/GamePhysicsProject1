/**********************************
* Subject: TGD2251 Game Physics   *
* Name: Mohd Syazwan B Mohd Jamil *
* Student ID: 1131121220          *
* Lecturer: Dr. Wong Ya Ping      *
***********************************/

#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>

class Border{
private:
	b2Body* body;
	b2BodyDef bodyDef;
	b2PolygonShape bodyShape;
	b2FixtureDef bodyFixtureDef;
	
	sf::RectangleShape rect;
	sf::Texture texture;
	sf::Sprite sprite;

	const float scale = 32.0f;

public:
	Border(b2World& world, sf::Vector2f size, sf::Vector2f position) {
		rect = sf::RectangleShape(size);
		rect.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
		rect.setFillColor(sf::Color(255, 255, 255, 255));
		rect.setOutlineThickness(1);
		rect.setOutlineColor(sf::Color::Black);
		
		bodyDef.position = b2Vec2(position.x / scale, position.y / scale);
		bodyDef.type = b2_staticBody;
		
		bodyShape.SetAsBox((size.x / 2) / scale, (size.y / 2) / scale);
		
		bodyFixtureDef.shape = &bodyShape;
		bodyFixtureDef.density = 0.3f;
		bodyFixtureDef.friction = 0.5f;

		body = world.CreateBody(&bodyDef);
		body->CreateFixture(&bodyFixtureDef);
	}
	
	void setFillColor(sf::Color col) {                                                                                                                                                                         
		rect.setFillColor(col);
	}

	void setOutlineThickness(float thickness) {
		rect.setOutlineThickness(thickness);
	}

	void setOutlineColor(sf::Color col) {
		rect.setOutlineColor(col);
	}

	void update() {
		rect.setRotation(body->GetAngle() * 180 / b2_pi);
		rect.setPosition(body->GetPosition().x * scale, body->GetPosition().y * scale);
	}

	sf::Shape& getShape() {
		return rect;
	}
};