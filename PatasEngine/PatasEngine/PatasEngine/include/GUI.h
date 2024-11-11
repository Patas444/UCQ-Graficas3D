#pragma once
#include "Prerequisites.h"
#include <vector>
#include "Actor.h"

class Window;

class
	GUI {
public:
	GUI() = default;
	~GUI() = default;

	// Inicializa la configuración y los recursos necesarios para la GUI.
	void
	init();

	// Actualiza los elementos de la GUI en cada frame.
	void
	update();

	// Renderiza la GUI en pantalla.
	void
	render();

	// Libera los recursos utilizados por la GUI.
	void
	destroy();

	/**
	 * @brief Muestra la consola de mensajes de error y advertencias.
	 * La consola muestra mensajes categorizados según su tipo (error, advertencia, información),
	 * proporcionando una interfaz para el seguimiento de mensajes del programa.
	 */
	void
	console(const std::map<ConsolErrorType, std::vector<std::string>>& programMessages);

	/**
	 * @brief Configura el estilo visual de la GUI.
	 * Establece las propiedades visuales y estéticas de los elementos gráficos de la GUI.
	 */
	void
	setupGUIStyle();

	/**
	 * @brief Muestra un menú jerárquico de actores en la escena.
	 * Permite al usuario seleccionar y visualizar los actores cargados en la aplicación.
	 */
	void
	hierarchy(const std::vector<EngineUtilities::TSharedPointer<Actor>>& actors, int& selectedActorID);


	/**
	 * @brief Muestra un menú para la creación de nuevos actores en la escena.
	 * Proporciona opciones para añadir nuevos actores y agregarlos a la lista de actores en la escena.
	 */
	void
	actorCreationMenu(std::vector<EngineUtilities::TSharedPointer<Actor>>& actors);

	/**
	 * @brief Muestra el panel de inspector para el actor seleccionado.
	 * Proporciona detalles y propiedades editables del actor actualmente seleccionado.
	 */
	void
	inspector(EngineUtilities::TSharedPointer<Actor> selectedActor);


private:
	std::map<int, std::string> m_programMessages;
};