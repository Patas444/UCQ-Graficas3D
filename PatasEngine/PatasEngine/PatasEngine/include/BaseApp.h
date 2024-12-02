#pragma once
#include <SFML/Graphics.hpp>
#include "Prerequisites.h"
#include <Window.h>
#include "ShapeFactory.h"
#include "Actor.h"
#include "GUI.h"
#include "Services/NotificationSystem.h"

class
BaseApp {

public:
	BaseApp() = default;
	~BaseApp();

	// Funcion encargada de ejecutar la aplicacion en main
	int
	run();

	// Funcion de inicializacion
	bool
	initialize();

	// Funcion que se actualiza por frame
	void
	update();

	// Funcion de renderizado
	void
	render();

	// Libera los recursos utilizados por la aplicaci�n.
	void
	cleanup();

	/**
	 * @brief Actualiza el movimiento del actor especificado.
	 * Esta funci�n gestiona el movimiento de un actor en funci�n del
	 * tiempo transcurrido.
	 */
	void
	updateMovement(float deltaTime, EngineUtilities::TSharedPointer<Actor> circle);

	/**
	 * @brief Realiza la l�gica de movimiento para el actor Circle.
	 * Actualiza la posici�n del actor Circle en base al tiempo transcurrido
	 * y la l�gica definida.
	 */
	void
	MovimientoCirculo(float deltaTime, EngineUtilities::TSharedPointer<Actor> Circle);

	int
	ActualPosition = 0; // Posicion actual de los waypoints

private:
	Window* m_window;
	EngineUtilities::TSharedPointer<Actor> Triangle;
	EngineUtilities::TSharedPointer<Actor> Circle;
	EngineUtilities::TSharedPointer<Actor> Track;
	std::vector< EngineUtilities::TSharedPointer<Actor>> m_actors;

	// Seek Activity
	int currentWaypoint = 0;

   /**
	* @brief Lista de waypoints utilizados para el movimiento de los actores 
	* (En este caso del Circle/Mario :) ).
	* Los actores seguir�n estos puntos de referencia en el orden establecido.
	*/
	std::vector<Vector2> waypoints = {
		{720.0f, 350.0f},
		{720.0f, 260.0f},
		{125.0f, 50.0f},
		{70.0f, 120.0f},
		{70.0f, 450.0f},
		{400.0f, 350.0f},
		{550.0f, 500.0f},
		{650.0f, 550.0f},
		{720.0f, 450.0f}
	};

	sf::Texture Mario; // Textura para el Actor Circle del personaje: Mario.
	sf::Texture texture; // Textura usada para la pista/escenario.

	GUI m_GUI; // Interfaz gr�fica de usuario para la aplicaci�n.
};