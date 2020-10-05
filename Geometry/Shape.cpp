#include <iostream>
#include <cmath>
#include <vector>
#include "Vector.hpp"
#include "Shape.hpp"

void Shape::GetType () {
	size_t p0;
	size_t p1;
	size_t p2;
	size_t size = vertices.size ();
			
	switch (size) {
		case 0:
			this->type = Undef;
			return;
		break;
		case 1:
			this->type = Point;
			return;
		break;
		case 2:
			this->type = Line;
			return;
		break;
		default:
			this->type = Convex;
		break;
	}
			
	float cross;
	bool  psign;
						
	for (size_t i=0; i<size; ++i) {
		p0 = i;
		p1 = (i + 1) % size;
		p2 = (i + 2) % size;
		
		float cross = (vertices[p0] - vertices[p1]).crossProduct (vertices[p2] - vertices[p1]);
		if (i != 0 && std::signbit (cross) != psign) {
			this->type = Concave;
			return;
		}
		
		psign = std::signbit (cross);
	}
}

void Shape::GetAxises () {
	size_t next = 0;
	size_t size = vertices.size ();

	Vector2 edge;
	axises.reserve (size);
	for (size_t curr=0; curr<size; ++curr) {
		next = (curr + 1) % size;

		edge = vertices[curr] - vertices[next];
		axises.push_back (edge.perpendicular ());					
	}
}
		
bool Shape::Collision (const Shape &other) const {
	if (this->type == Line && other.type == Line) {
		return false;
	}
			
	if (this->type == Convex && other.type == Convex) {
		// Use SAT algorithm
		Projection pp1;
		Projection pp2;
		
		for (size_t i=0; i<this->axises.size(); ++i) {
			pp1 = this->Project (this->axises[i]);
			pp2 = other.Project (this->axises[i]);
			
			if (!pp1.Overlap (pp2)) return false;
		}
		
		for (size_t i=0; i<other.axises.size(); ++i) {
			pp1 = other.Project (other.axises[i]);
			pp2 = this->Project (other.axises[i]);
			
			if (!pp1.Overlap (pp2)) return false;
		} 
		
		return true;
	}
	
	return false;
}

int main () {
	Shape test;
		
	test.vertices.push_back (Vector2 (0.f, 0.f));
	test.vertices.push_back (Vector2 (4.f, 2.f));
	test.vertices.push_back (Vector2 (1.f, 1.f));
	
	test.GetType ();
	
	std::cout << test.type << std::endl;
	
	return 0;
}
