#ifndef _ENGINE2MD_BODY_
#define _ENGINE2MD_BODY_
#include <SFML/Graphics.hpp>
#include "Vector.hpp"

class Body : public sf::RectangleShape {
	public:
		float   Mass;
		float   Scale;

		Vector2 Force;	
		Vector2 Acceleration;
		Vector2 Velocity;
		Vector2 Position;
	
		Body (float Mass=1.f, float g=9.81f) : Acceleration (0.f, 0.f),
	                                           Velocity (0.f, 0.f),
	                                           Position (0.f, 0.f),
	                                           Force (0.f, 0.f),
	                                           Mass (Mass),
	                                           Scale (1.f) { }
		
		~Body () { }
		
		void ApplyForce (Vector2);
		void Integration (float);
		void setPosition ();
};

#endif
