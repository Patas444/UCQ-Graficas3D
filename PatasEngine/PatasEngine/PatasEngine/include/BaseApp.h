#pragma once
#include "Prerequisites.h"
#include "Window.h"
#include "ShapeFactory.h"
#include "Actor.h"

class
	BaseApp {
public:
	BaseApp() = default;
	~BaseApp() = default;

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

	void
	cleanup();

	void
	updateMovement(float deltaTime, EngineUtilities::TSharedPointer<Actor> circle);

private:
	sf::Clock clock;
	sf::Time deltaTime;

	Window* m_window;
	EngineUtilities::TSharedPointer<Actor> Triangle;
	EngineUtilities::TSharedPointer<Actor> Circle;

	// Seek Activity
	int currentWaypoint = 0;

	std::vector<sf::Vector2f> waypoints = {
	{100.0f, 100.0f},
	{400.0f, 100.0f},
	{400.0f, 400.0f},
	{100.0f, 400.0f}
	};
};