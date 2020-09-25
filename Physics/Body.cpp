#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Vector.hpp"
#include "ForceGenerator.hpp"
#include "Body.hpp"

void Body::ApplyForce (Vector2 AppForce) {
	Force += AppForce;
}
		
void Body::Integration (float dt) {
	Acceleration = Force / Mass;
	
	Velocity = Velocity + (Acceleration * dt);
	Position.addScaled (Velocity, dt * Scale);
	Position.addScaled (Acceleration, dt * dt * Scale * 0.5);
	
	setPosition ();
}
		
void Body::setPosition () {
	sf::RectangleShape::setPosition (Position.x, Position.y);
}

int main () {
	Body mat0 (1.5f);
	Body mat1 (2.f);
	
	mat0.Scale = 10.f;
	mat1.Scale = 10.f;
	
	mat0.Position.x = 100.f;
	mat0.Position.y = 100.f;
    mat0.setPosition ();
    
	mat1.Position.x = 120.f;
	mat1.Position.y = 10.f;
	mat1.setPosition ();
    
    mat0.setSize (sf::Vector2f (4.f, 4.f));
    mat1.setSize (sf::Vector2f (4.f, 4.f));
    
    mat0.setFillColor (sf::Color::Red);
    mat1.setFillColor (sf::Color::Green);

	ForceGenerator *Gravity = new GravityForceGenerator ();
	ForceGenerator *Drag = new DragForceGenerator (0.0001f, 0.00001f);
	
	Gravity->UpdateForce (&mat0, 0.f);
	Gravity->UpdateForce (&mat1, 0.f);
	
	sf::RenderWindow window (sf::VideoMode (600, 600), "Material");
	
	sf::Event e;
	sf::Clock clock;
	
	float time = 0.f;
 
	while (window.isOpen ()) {
		time += clock.getElapsedTime ().asMicroseconds ();
		clock.restart ();
		
		if (time >= 1000) {
			time = 0;
			if ((mat0.Position.y + mat0.getSize ().y) <= 600.f)
				mat0.Integration (0.001f);
				
			if ((mat1.Position.y + mat1.getSize ().y) <= 600.f)
				mat1.Integration (0.001f);
				
			Drag->UpdateForce (&mat0, 0.f);
			Drag->UpdateForce (&mat1, 0.f);
		}
		
		while (window.pollEvent (e)) {
			if (e.type == sf::Event::Closed) {
				window.close ();
			}
		}
		
		window.clear ();
		window.draw (mat0);
		window.draw (mat1);
		window.display ();
	}

	return 0;
}
