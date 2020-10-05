#ifndef _ENGINE2MD_SHAPE_
#define _ENGINE2MD_SHAPE_

#include <vector>
#include "Vector.hpp"

class Shape {
	public:
		enum _Type {Undef=0, Point, Line, Convex, Concave};
	
		std::vector<Vector2> vertices;
		std::vector<Vector2> axises;
		_Type type = Undef;
		
		class Projection {
			public:
				float min;
				float max;
			
				Projection (float mn=0.f, float mx=0.f): min (mn), max (mx) { }
		
				bool Overlap (Projection p) const {
					return  (p.min > this->min && p.min < this->max) ||
							(p.max > this->min && p.max < this->max);
					}
		};
		
		Projection Project (Vector2 axis) const {
			float min = axis * this->vertices[0];
			float max = min;
			
			for (size_t i=1; i<this->vertices.size(); ++i) {
				float dot = axis * this->vertices[1];
				
				if (dot < min) min = dot;
				if (dot > max) max = dot;
			}
			
			return Projection (min, max);
		}
		
		void GetType ();
		void GetAxises ();
		bool Collision (const Shape &other) const;
};

#endif
