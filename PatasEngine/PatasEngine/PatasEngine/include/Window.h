#pragma once
#include "Prerequisites.h"

class
	Window {

public:
Window() = default;
Window(int width, int height, const std::string& title);
~Window();

	void
	handleEvents();

	// Limpia el contenido de la ventana con el color predeterminado.
	void
	clear();

	// Muestra el contenido de la ventana en la pantalla.
	void
	display();

	// Verifica si la ventana sigue abierta.
	bool
	isOpen() const;

	// Dibuja un objeto que puede ser dibujado en la ventana.
	void
	draw(const sf::Drawable& drawable);

	// Obtiene el objeto interno SFML RenderWindow.
	sf::RenderWindow*
	getWindow();

	// Funcion de inicializacion
	void
	init();

	// Funcion que se actualiza por frame
	void
	update();

	// Funcion de renderizado
	void
	render();

	void
	destroy();

private:
	sf::RenderWindow* m_window;
};