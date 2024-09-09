#pragma once
#include "Prerequisites.h"

class 
Window {
public:
	Window();
	Window(int width, int height, const std::string& title);
	~Window();

	void
	handlerEvents();

	void
	clear();

	void
	display();

	bool
	isOpen() const;

	void
	draw(const sf::Drawable& drawable);

	sf::RenderWindow*
	getWindow();

	void
	init();

	void
	update();

	void
	render();

	void
	destroy();

private:
	sf::RenderWindow* m_window;
};