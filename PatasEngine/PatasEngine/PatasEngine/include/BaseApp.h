#pragma once
#include <SFML/Graphics.hpp>

class
BaseApp{
public:
	BaseApp() = default;
	~BaseApp() = default;

	//Funcion que ejecuta la aplicación
	int
	run();

	void
	initialize();

	void
	handleEvents();

	void
	update();

	void
	render();

	void
	cleanup();

private:
	sf::RenderWindow* window;
	sf::CircleShape* shape;
};