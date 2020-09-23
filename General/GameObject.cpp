#include <iostream>
#include <list>
#include <memory>
#include <SFML/Graphics.hpp>

class FrameSet {
		std::vector<sf::IntRect> frames;
	public:
		FrameSet (size_t size) { frames.reserve (size); }
		~FrameSet () { }
		
		bool SetFrame (size_t index, const sf::IntRect &frame) {
			if (index < frames.capacity ()) {
				frames[index].left = frame.left;
				frames[index].top = frame.top;
				frames[index].width = frame.width - frame.left;
				frames[index].height = frame.height - frame.top;
				
				return true;
			}
			else {
				return false;
			}
		}
		
		sf::IntRect* GetFrame (size_t index) {
			sf::IntRect *out = nullptr;
			
			if (index < frames.capacity ()) {
				out = &frames[index];
			}
			
			return out;
		}
		
		size_t GetSize () const {
			return frames.capacity ();
		}
};

class GameObject {
	public:
		enum Direction {left, right};
	private:
		std::unique_ptr<sf::Texture> texture;
		std::unique_ptr<sf::Sprite>  sprite;
		
		sf::Vector2f position;
		enum Direction direction;
		
		unsigned frameCnt;
		
		FrameSet *activeView;
		std::list<std::unique_ptr<FrameSet> > views;
	public:	
		GameObject () : position(0.f, 0.f), activeView (nullptr) {	}
		~GameObject () { }

// --------- Construct game object ---------------------------

// --------- Graphic constructor ----------------------------
		void SetTexture (std::string path) {
			texture = std::make_unique<sf::Texture> ();
			sprite = std::make_unique<sf::Sprite> ();
			
			texture->loadFromFile (path);
			sprite->setTexture (*texture);
		}

		void AddView (size_t frameNum) {
			auto view = std::make_unique<FrameSet> (frameNum);
			views.push_back (std::move(view));
		}
		
		void AddFrame (size_t state, size_t index, const sf::IntRect &frame) {
			size_t cnt = 0;

			for (auto i=views.begin(); i!=views.end(); ++i, ++cnt) {
				if (cnt == state) {
					 if (!(*i)->SetFrame (index, frame)) {
						 std::cout << "throw: Frame is not found" << std::endl;
					 }
					return;
				}
			}
			
			std::cout << "throw: View is not found" << std::endl;
		}

// --------- Sound constructor ----------------------------


// --------- Events constructor ----------------------------


// --------- Initialize game object ----------------------------
		void Initialize () {			
			if (sprite != nullptr && !views.empty ()) { // Initialize graphics
				sf::IntRect *rect = nullptr;
				
				frameCnt = 0;
				
				auto view = std::next (views.begin(), 0);
				activeView = view->get ();
				
				rect = activeView->GetFrame (frameCnt);
				sprite->setTextureRect (*rect);
				sprite->setOrigin (rect->width/2, rect->height/2);
			}
		}

// --------- Game object parameters ---------------------
		sf::Sprite& GetSprite () const {
			return *sprite;
		}
		
		enum Direction GetDirection () const {
			return direction;
		}
		
		sf::Vector2f GetPosition () const {
			return position;
		}
		
		size_t GetNumberViews () const {
			return views.size ();
		}

		void SetView (size_t index) {
			if (!views.empty ()) {
				if (index < views.size ()) {
					frameCnt = 0;
					
					auto view = std::next (views.begin (), index);
					activeView = view->get ();
					
					sf::IntRect *rect = activeView->GetFrame (frameCnt);
					
					std::cout << "New view rect: " << std::endl;
					
					sprite->setTextureRect (*rect);
					sprite->setOrigin (rect->width/2, rect->height/2);
				}
				else
					std::cout << "throw: index invalid" << std::endl;
			}
			else
				std::cout << "throw: views is empty" << std::endl;
		}

		void NextFrame () {
			if (activeView != nullptr) {
				if (activeView->GetSize () == 0)
					std::cout << "Throw: activeView is empty" << std::endl;
				
				if (frameCnt < activeView->GetSize () - 1) ++frameCnt;
				else frameCnt = 0;
				
				sf::IntRect *rect = activeView->GetFrame (frameCnt);
				sprite->setTextureRect (*rect);
				sprite->setOrigin (rect->width/2, rect->height/2);
			}
			else
				std::cout << "throw: activeView is null" << std::endl;
		}

// --------- Transform game object ----------------------		
		void SetPosition (const sf::Vector2f &newPos) {
			position.x = newPos.x;
			position.y = newPos.y;
			
			if (sprite != nullptr) {
				sprite->setPosition (position);
			}
		}
		
		void Move (const sf::Vector2f &offset) {
			position.x += offset.x;
			position.y += offset.y;
			
			if (sprite != nullptr) {
				sprite->setPosition (position);
			}
		}
		
		void ChangeDirection() {
			if (direction == left) {
				direction = right;
			}
			else {
				direction = left;
			}
			
			if (sprite != nullptr){
				sprite->scale (-1.f, 1.f);
			}
		}
};

class ObjectBuilder {
	public:
		virtual void BuildObject () = 0; // Pure virtual build
	
		virtual void BuildGraphic () { } // Optional
		virtual void BuildSound () { } // Optional
		virtual void BuildEventHandler () { } // Optional
};

class PlayerBuilder : public ObjectBuilder {
	public:
		PlayerBuilder () { }
		virtual ~PlayerBuilder () { }
		
		virtual void BuildObject () {
			
		}
		
		virtual void BuildGraphic () {
			
		}
		
		virtual void BuildSound () {
			
		}
		
		virtual void BuildEventHandler () {
			
		}
};

int main () {
	size_t currView = 0;
	GameObject *object = new GameObject ();
	
	object->SetTexture ("bob.png");
	
	object->AddView (5);
	object->AddFrame (0, 0, sf::IntRect (39, 39, 99, 143));
	object->AddFrame (0, 1, sf::IntRect (183, 38, 245, 143));
	object->AddFrame (0, 2, sf::IntRect (328, 40, 391, 143));
	object->AddFrame (0, 3, sf::IntRect (470, 38, 532, 143));
	object->AddFrame (0, 4, sf::IntRect (616, 39, 677, 143));
	
	object->AddView (5);
	object->AddFrame (1, 0, sf::IntRect (50, 207, 101, 208));
	object->AddFrame (1, 1, sf::IntRect (195, 145, 229, 287));
	object->AddFrame (1, 2, sf::IntRect (330, 166, 386, 278));
	object->AddFrame (1, 3, sf::IntRect (461, 171, 536, 273));
	object->AddFrame (1, 4, sf::IntRect (615, 179, 693, 266));
	
	object->Initialize ();
	object->SetPosition (sf::Vector2f (300.f, 300.f));
	
	sf::RenderWindow window (sf::VideoMode (600, 600), "Example");
	sf::Event event;
	while (window.isOpen ()) {
		while (window.pollEvent (event)) {
			switch (event.type) {
				case sf::Event::Closed:
					window.close ();
				break;
				case sf::Event::KeyPressed:
					switch (event.key.code) {
						case sf::Keyboard::Space:
							object->NextFrame ();
						break;
						case sf::Keyboard::RShift:
							if (currView < object->GetNumberViews ()) ++currView;
							else currView = 0;
							
							std::cout << object->GetNumberViews () << std::endl;
							
							object->SetView (currView);
						break;
					}
				break;
			}
		}
		
		window.clear ();
		window.draw (object->GetSprite ());
		window.display ();
	}
	
	delete object;
	return 0;
}
