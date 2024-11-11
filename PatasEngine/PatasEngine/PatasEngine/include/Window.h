#pragma once
#include <SFML/Graphics.hpp>

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

	/**
	 * @brief Dibuja un objeto que puede ser dibujado en la ventana.
	 * drawable Referencia a un objeto SFML que puede ser dibujado.
	 */
	void 
	draw(const sf::Drawable& drawable);

	/**
	 * @brief Obtiene el objeto interno SFML RenderWindow.
	 * Un puntero al objeto interno SFML RenderWindow.
	 */
	sf::RenderWindow* 
	getWindow();

	// Renderiza el contenido de la ventana en una textura.
	void 
	renderToTexture();

	// Aplica un estilo personalizado a la ventana.
	void
	setCustomStyle();

	// Muestra el contenido de la ventana en una interfaz de ImGui.
	void 
	showInImGui();

	// Funcion de inicializacion
	void
	init();

	// Funcion que se actualiza por frame
	void
	update();

	// Funcion de renderizado
	void
	render();

	// Libera los recursos utilizados por la ventana.
	void
	destroy();

private:
	sf::RenderWindow* m_window; // Puntero al objeto `RenderWindow` de SFML.
	sf::View m_view; // Vista de la ventana para manejar la perspectiva de visualización.

public:
	sf::RenderTexture m_renderTexture; // Textura de renderizado para almacenamiento de gráficos.
	sf::Time deltaTime; // Tiempo transcurrido entre frames.
	sf::Clock clock; // Reloj para calcular el tiempo transcurrido entre frames.
	
};