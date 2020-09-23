#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Vector.hpp"

class Particle : public sf::RectangleShape {
	public:
		float   Mass;
		float   Scale;
	
		Vector2 Acceleration;
		Vector2 Velocity;
		Vector2 Position;
		
		// Forces
		Vector2 AppForce;
		Vector2 Frictional;
		float   Drag;
		float   Gravity;
	
		Particle (float Mass=1.f, float g=9.81f) : Acceleration (0.f, 0.f),
	                                               Velocity (0.f, 0.f),
	                                               Position (0.f, 0.f),
	                                               Frictional (0.f, 0.f),
	                                               Drag (0.f),
	                                               AppForce (0.f, 0.f),
	                                               Mass (Mass),
	                                               Scale (1.f) {
			Gravity = Mass * g;
		}
		
		~Particle () { }
		
		void ApplyForce (Vector2 force) {
			AppForce += force;
		}
		
		Vector2 CalcNetForce () {
			Vector2 iDrag (Drag, Drag);
			Vector2 iFrictional (Frictional);
			Vector2 iGravity (0.f, Gravity - Drag);
			
			Vector2 iDirection = AppForce.direction ();

			iDrag       &= ~iDirection;
			iFrictional &= ~iDirection;

			return (AppForce + iFrictional + iDrag + iGravity);
		}
		
		void Integration (float dt) {
			Vector2 NetForce;
			
			NetForce = CalcNetForce();
			
			Acceleration = NetForce / Mass;
			
			Velocity = Velocity + (Acceleration * dt);
			Position = Position + (Velocity * dt) * Scale;
			
			setPosition ();
		}
		
		void setPosition () {
			sf::RectangleShape::setPosition (Position.x, Position.y);
		}
};

class Firework : public Particle {
	
};

int main () {
	Particle mat0 (1.f);
	Particle mat1 (3.f);
	
	mat0.Scale = 10.f;
	mat1.Scale = 10.f;
	
	mat0.Position.x = 100.f;
	mat0.Position.y = 10.f;
    mat0.setPosition ();
    
	mat1.Position.x = 120.f;
	mat1.Position.y = 10.f;
	mat1.setPosition ();

    mat0.Drag = 1.f;
    mat1.Drag = 4.f;
    
    mat0.setSize (sf::Vector2f (4.f, 4.f));
    mat1.setSize (sf::Vector2f (4.f, 4.f));
    
    mat0.setFillColor (sf::Color::Red);
    mat1.setFillColor (sf::Color::Green);
	
	mat0.ApplyForce (Vector2 (1.f, -2.f));
	mat1.ApplyForce (Vector2 (5.f, 0.f));
	
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
