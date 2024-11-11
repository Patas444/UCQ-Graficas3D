#include "BaseApp.h"
#include "Services/NotificationSystem.h"

BaseApp::~BaseApp()
{
	
	NotificationService::getInstance().saveMessagesToFile("LogData.txt");
}

/**
 * @brief Ejecuta el ciclo principal de la aplicación.
 * Inicializa la aplicación y entra en el bucle de renderizado y actualización.
 */
int
BaseApp::run() {
	NotificationService& notifier = NotificationService::getInstance();

	if (!initialize()) {
		notifier.addMessage(ConsolErrorType::ERROR, "Initializes result on a false statemente, check method validations");
		notifier.saveMessagesToFile("LogData.txt");
		ERROR("BaseApp", "run", "Initializes result on a false statemente, check method validations");
	}
	else {
		notifier.addMessage(ConsolErrorType::NORMAL, "All programs were initialized correctlY");
	}
	m_GUI.init();

	while (m_window->isOpen()) {
		m_window->handleEvents();
		update();
		render();
	}

	cleanup();
	return 0;
}
/**
 * @brief Inicializa los recursos y objetos necesarios para la aplicación.
 * Configura la ventana principal, crea los actores y asigna texturas.
 */
bool
BaseApp::initialize() {
	NotificationService& notifier = NotificationService::getInstance();
	m_window = new Window(1920, 1080, "Patas Engine");
	if (!m_window) {
		ERROR("BaseApp", "initialize", "Error on window creation, var is null");
		return false;
	}
	// Track Actor
	Track = EngineUtilities::MakeShared<Actor>("Track");
	if (!Track.isNull()) {
		Track->getComponent<ShapeFactory>()->createShape(ShapeType::RECTANGLE);

		// Establecer posición, rotación y escala desde Transform
		Track->getComponent<Transform>()->setPosition(sf::Vector2f(0.0f, 0.0f));
		Track->getComponent<Transform>()->setRotation(sf::Vector2f(0.0f, 0.0f));
		Track->getComponent<Transform>()->setScale(sf::Vector2f(11.0f, 12.0f));

		if (!texture.loadFromFile("Circuit.png")) {
			std::cout << "Error de carga de textura" << std::endl;
			return -1; // Manejar error de carga
		}
		Track->getComponent<ShapeFactory>()->getShape()->setTexture(&texture);
	}

	// Circle Actor
	Circle = EngineUtilities::MakeShared<Actor>("Circle");
	if (!Circle.isNull()) {
		Circle->getComponent<ShapeFactory>()->createShape(ShapeType::CIRCLE);

		// Establecer posición, rotación y escala desde Transform
		Circle->getComponent<Transform>()->setPosition(sf::Vector2f(200.0f, 200.0f));
		Circle->getComponent<Transform>()->setRotation(sf::Vector2f(0.0f, 0.0f));
		Circle->getComponent<Transform>()->setScale(sf::Vector2f(1.0f, 1.0f));

		if (!Mario.loadFromFile("Characters/tile000.png")) {
			std::cout << "Error de carga de textura" << std::endl;
			return -1; // Manejar error de carga
		}
		Circle->getComponent<ShapeFactory>()->getShape()->setTexture(&Mario);
	}
	m_actors.push_back(Circle);

	// Triangle Actor
	Triangle = EngineUtilities::MakeShared<Actor>("Triangle");
	if (!Triangle.isNull()) {
		Triangle->getComponent<ShapeFactory>()->createShape(ShapeType::TRIANGLE);
		Triangle->getComponent<Transform>()->setPosition(sf::Vector2f(200.0f, 200.0f));
		Triangle->getComponent<Transform>()->setRotation(sf::Vector2f(0.0f, 0.0f));
		Triangle->getComponent<Transform>()->setScale(sf::Vector2f(1.0f, 1.0f));
	}
	m_actors.push_back(Triangle);
	return true;
}

/**
 * @brief Actualiza el estado de la aplicación en cada cuadro.
 * Actualiza la ventana y la posición de los actores, incluyendo el seguimiento de waypoints.
 */
void
BaseApp::update() {
	// Update window method
	m_window->update();

	// Mouse Position
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*m_window->getWindow());
	sf::Vector2f mousePosF(static_cast<float>(mousePosition.x),
		static_cast<float>(mousePosition.y));

	if (!Track.isNull()) {
		Track->update(m_window->deltaTime.asSeconds());
	}
	if (!Triangle.isNull()) {
		Triangle->update(m_window->deltaTime.asSeconds());
	}
	if (!Circle.isNull()) {
		Circle->update(m_window->deltaTime.asSeconds());
		updateMovement(m_window->deltaTime.asSeconds(), Circle);
	}
	for (auto& actor : m_actors) {
		if (!actor.isNull()) {
			actor->update(m_window->deltaTime.asSeconds());
			if (actor->getName() == "Circle") {
				MovimientoCirculo(m_window->deltaTime.asSeconds(), actor);
			}
		}
	}
}

// Controla el movimiento de un actor específico usando waypoints.
void BaseApp::MovimientoCirculo(float deltaTime, EngineUtilities::TSharedPointer<Actor> Circle) {
	if (Circle.isNull()) return;

	auto transform = Circle->getComponent<Transform>();
	if (transform.isNull()) return;

	sf::Vector2f targetPos = waypoints[ActualPosition];
	transform->Seek(targetPos, 200.0f, deltaTime, 10.0f);
	sf::Vector2f currentPos = transform->getPosition();
	float distanceToTarget = std::sqrt(std::pow(targetPos.x - currentPos.x, 2) + std::pow(targetPos.y - currentPos.y, 2));

	if (distanceToTarget < 10.0f) {
		ActualPosition = (ActualPosition + 1) % waypoints.size();
	}
}

int selectedActorID = -1;


/**
 * @brief Renderiza todos los actores y las interfaces de usuario.
 * Llama a los métodos de renderizado de cada actor, muestra el contenido en ImGui,
 * y presenta las herramientas de interfaz gráfica.
 */
void
BaseApp::render() {
	NotificationService& notifier = NotificationService::getInstance();
	m_window->clear();

	if (!Track.isNull()) {
		Track->render(*m_window);
	}
	if (!Circle.isNull()) {
		Circle->render(*m_window);
	}
	if (!Triangle.isNull()) {
		Triangle->render(*m_window);
	}

	for (auto& actor : m_actors) {
		if (!actor.isNull()) {
			actor->render(*m_window);
		}
	}

	// Mostrar el render en ImGui
	m_window->renderToTexture();  // Finaliza el render a la textura
	m_window->showInImGui();      // Muestra la textura en ImGui

	//Muestra consola de notificaciones
	m_GUI.console(notifier.getNotifications());

	//Muestra ventana
	m_GUI.hierarchy(m_actors, selectedActorID);

	if (selectedActorID >= 0 && selectedActorID < m_actors.size()) {
		m_GUI.inspector(m_actors[selectedActorID]);
	}

	m_GUI.actorCreationMenu(m_actors);


	m_window->render();
	m_window->display();

}

// Libera los recursos de la aplicación.
void
BaseApp::cleanup() {
	m_window->destroy();
	delete m_window;
}

// Actualiza el movimiento del actor Circle basado en puntos de recorrido.
void
BaseApp::updateMovement(float deltaTime, EngineUtilities::TSharedPointer<Actor> circle) {
	// Verificar si el Circle es nulo
	if (!circle || circle.isNull()) {
	return;
	}

	// Obtener el componente Transform
	auto transform = circle->getComponent<Transform>();
	if (transform.isNull()) {
	return;
	}

	// Posición actual del destino (punto de recorrido)
	sf::Vector2f targetPos = waypoints[currentWaypoint];

	// Llamar al Seek del Transform
	transform->Seek(targetPos, 200.0f, deltaTime, 10.0f);

	// Obtener la posición actual del actor desde Transform
	sf::Vector2f currentPos = transform->getPosition();

	// Comprobar si el actor ha alcanzado el destino (o está cerca)
	float distanceToTarget = std::sqrt(std::pow(targetPos.x - currentPos.x, 2) + std::pow(targetPos.y - currentPos.y, 2));

	if (distanceToTarget < 10.0f) { // Umbral para considerar que ha llegado
	currentWaypoint = (currentWaypoint + 1) % waypoints.size(); // Ciclar a través de los puntos
	}
};