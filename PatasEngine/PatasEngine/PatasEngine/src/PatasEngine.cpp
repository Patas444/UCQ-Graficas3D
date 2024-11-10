#include "BaseApp.h"
#include <SFML/Graphics.hpp>
#include "Window.h"

sf::RenderWindow* window;
//sf::CircleShape* shape;

int
main() {
	BaseApp app;
	return app.run();
}