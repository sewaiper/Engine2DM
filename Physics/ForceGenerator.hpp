#ifndef _ENGINE2MD_FORCE_GENERATOR_
#define _ENGINE2MD_FORCE_GENERATOR_

#include <iostream>
#include "Vector.hpp"
#include "Body.hpp"

class ForceGenerator {
	public:
		virtual void UpdateForce (Body*, float) = 0;
};


// ---------------------------------------------------
// Gravity force
// ---------------------------------------------------
class GravityForceGenerator : public ForceGenerator {
		float g;
	public:
		GravityForceGenerator (float g = 9.81f): g (g) { }
		virtual ~GravityForceGenerator () { }
		
		virtual void UpdateForce (Body*, float);
};

void GravityForceGenerator::UpdateForce (Body *body, float dt) {	
	if (body->Mass != 0.f)
		body->ApplyForce (Vector2 (0.f, body->Mass * this->g));
}

// ---------------------------------------------------
// Drag force
// --------------------------------------------------- 
class DragForceGenerator : public ForceGenerator {
		float k1;
		float k2;
	public:
		DragForceGenerator (float k1, float k2): k1 (k1), k2 (k2) { }
		virtual ~DragForceGenerator () { }
		
		virtual void UpdateForce (Body*, float);
};

void DragForceGenerator::UpdateForce (Body *body, float dt) {
	Vector2 iDrag (body->Velocity);
	
	float dragCoeff = iDrag.length ();
	dragCoeff = k1 * dragCoeff + k2 * dragCoeff * dragCoeff;
	
	iDrag.normalize ();
	iDrag *= -dragCoeff;
	
	body->ApplyForce (iDrag);
}

#endif

