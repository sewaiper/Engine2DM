#include <cmath>

class Vector2 {
	public:
		float x;
		float y;
	
		Vector2 (float x=0.f, float y=0.f): x(x), y(y) { }
		~Vector2 () { }
		
		float length () const {
			return sqrt (x*x + y*y);
		}
		
		float squareLength () const {
			return x*x + y*y;
		}
		
		void normalize () {
			float d = this->length ();
			if (d > 0) {
				(*this) = (*this) * ((float) 1 / d);
			}
		}
		
		void addScaled (Vector2 op, float scale) {
			this->x += op.x * scale;
			this->y += op.y * scale;
		}
		
		Vector2 direction () {
			float dx = (this->x != 0) ? this->x/fabs (this->x) : 0;
			float dy = (this->y != 0) ? this->y/fabs (this->y) : 0;
			
			return Vector2 (dx, dy);
		}
		
		Vector2 compareLess (Vector2 op) {
			float dx = (this->x < op.x) ? 0.f : this->x;
			float dy = (this->y < op.y) ? 0.f : this->y;
			
			return Vector2 (dx, dy);
		}
		
		Vector2 compareMore (Vector2 op) {
			float dx = (this->x > op.x) ? 0.f : this->x;
			float dy = (this->y > op.y) ? 0.f : this->y;
			
			return Vector2 (dx, dy);
		}
		
		// Modification operators
		
		void operator() (float nx, float ny) {
			this->x = nx;
			this->y = ny;
		}
		
		void operator() (Vector2 op) {
			this->x = op.x;
			this->y = op.y;
		}
		
		Vector2 operator*= (float op) {
			this->x *= op;
			this->y *= op;
			
			return (*this);
		}
		
		Vector2 operator&= (Vector2 op) {
			this->x *= op.x;
			this->y *= op.y;
			
			return (*this);
		}
		
		Vector2 operator/= (float op) {
			this->x /= op;
			this->y /= op;
			
			return (*this);
		}
		
		Vector2 operator+= (Vector2 op) {
			this->x += op.x;
			this->y += op.y;
			
			return (*this);
		}
		
		Vector2 operator-= (Vector2 op) {
			this->x -= op.x;
			this->y -= op.y;
			
			return (*this);
		}
		
		Vector2 operator+= (float op) {
			this->x += op;
			this->y += op;
			
			return (*this);
		}
		
		Vector2 operator-= (float op) {
			this->x -= op;
			this->y -= op;
			
			return (*this);
		}
		
		// Non-modification operators
		
		Vector2 operator~ () const {
			return Vector2 (-(this->x), -(this->y));
		}
		
		Vector2 operator* (float op) const {
			return Vector2 (this->x * op, this->y * op);
		}
		
		float operator* (Vector2 op) const {
			return (this->x * op.x + this->y * op.y);
		}
		
		Vector2 operator& (Vector2 op) const {
			return Vector2 (this->x * op.x, this->y * op.y);
		}
		
		Vector2 operator/ (float op) const {
			return Vector2 (this->x / op, this->y / op);
		}
		
		Vector2 operator+ (Vector2 op) const {
			return Vector2 (this->x + op.x, this->y + op.y);
		}
		
		Vector2 operator- (Vector2 op) const {
			return Vector2 (this->x - op.x, this->y - op.y);
		}
		
		Vector2 operator+ (float op) const {
			return Vector2 (this->x + op, this->y + op);
		}
		
		Vector2 operator- (float op) const {
			return Vector2 (this->x - op, this->y - op);
		}
};
