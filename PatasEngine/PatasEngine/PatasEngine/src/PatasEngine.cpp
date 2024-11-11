#include "BaseApp.h"
#include <SFML/Graphics.hpp>
#include "Window.h"

sf::RenderWindow* window;

int
main() {
	BaseApp app;
	return app.run();
}