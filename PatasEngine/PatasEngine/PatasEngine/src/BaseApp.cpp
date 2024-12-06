#include "BaseApp.h"

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
        notifier.addMessage(ConsolErrorType::NORMAL, "All programs were initialized correctly");
    }
    m_GUI.init();

    while (m_window->isOpen()) {
        m_window->handleEvents();
        deltaTime = clock.restart();
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
    ResourceManager& resourceManager = ResourceManager::getInstance();

    m_window = new Window(1920, 1080, "Patas Engine");
    if (!m_window) {
        notifier.addMessage(ConsolErrorType::ERROR, "Error on window creation, pointer is null");
        ERROR("BaseApp", "initialize", "Error on window creation, var is null");
        return false;
    }

   /**
    * @brief Lista de waypoints utilizados para el movimiento de los actores
    * (En este caso del Circle/Mario :) ).
    * Los actores seguirán estos puntos de referencia en el orden establecido.
    */
    points[0] = Vector2(720.0f, 350.0f);
    points[1] = Vector2(720.0f, 260.0f);
    points[2] = Vector2(125.0f, 50.0f);
    points[3] = Vector2(70.0f, 120.0f);
    points[4] = Vector2(70.0f, 450.0f);
    points[5] = Vector2(400.0f, 350.0f);
    points[6] = Vector2(550.0f, 500.0f);
    points[7] = Vector2(650.0f, 550.0f);
    points[8] = Vector2(720.0f, 450.0f);

    // Track Actor
    Track = EngineUtilities::MakeShared<Actor>("Track");
    if (!Track.isNull()) {
        Track->getComponent<ShapeFactory>()->createShape(ShapeType::RECTANGLE);

        // Establecer posici�n, rotaci�n y escala desde Transform
        Track->getComponent<Transform>()->setTransform(Vector2(0.0f, 0.0f),
            Vector2(0.0f, 0.0f), Vector2(11.0f, 12.0f));

        // Cargar la textura de Track
        if (!resourceManager.loadTexture("Circuit", "png")) {
            notifier.addMessage(ConsolErrorType::ERROR, "Error de carga de la textura: Circuit");
        }

        EngineUtilities::TSharedPointer<Texture> trackTexture = resourceManager.getTexture("Circuit");
        if (trackTexture) {
            Track->getComponent<ShapeFactory>()->getShape()->setTexture(&trackTexture->getTexture());
        }

        m_actors.push_back(Track);
    }
    else {
        notifier.addMessage(ConsolErrorType::ERROR, "Error - Nullpointer Reference");
        notifier.addMessage(ConsolErrorType::WARNING, "Warning - Missing Texture from source bin");
    }

    //Circle Actor
    Circle = EngineUtilities::MakeShared<Actor>("Player");
    if (!Circle.isNull()) {
        Circle->getComponent<ShapeFactory>()->createShape(ShapeType::CIRCLE);

        Circle->getComponent<Transform>()->setTransform(Vector2(200.0f, 200.0f),
            Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f));

        // Cargar la textura de Track
        if (!resourceManager.loadTexture("Characters/tile000", "png")) {
            notifier.addMessage(ConsolErrorType::ERROR, "Error de carga de la textura: Mario");
        }

        EngineUtilities::TSharedPointer<Texture> trackTexture = resourceManager.getTexture("Characters/tile000");
        if (trackTexture) {
            Circle->getComponent<ShapeFactory>()->getShape()->setTexture(&trackTexture->getTexture());
        }

        m_actors.push_back(Circle);
    }
    else {
        notifier.addMessage(ConsolErrorType::ERROR, "Error - Nullpointer Reference");
        notifier.addMessage(ConsolErrorType::WARNING, "Warning - Missing Texture from source bin");
    }

    // Triangle Actor
    Triangle = EngineUtilities::MakeShared<Actor>("Triangle");
    if (!Triangle.isNull()) {
        Triangle->getComponent<ShapeFactory>()->createShape(ShapeType::TRIANGLE);
        Triangle->getComponent<Transform>()->setPosition(Vector2(200.0f, 200.0f));
        Triangle->getComponent<Transform>()->setRotation(Vector2(0.0f, 0.0f));
        Triangle->getComponent<Transform>()->setScale(Vector2(1.0f, 1.0f));
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
    m_window->update();

    for (auto& actor : m_actors) {
        if (!actor.isNull()) {
            actor->update(m_window->deltaTime.asSeconds());
            if (actor->getName() == "Player") {
                updateMovement(m_window->deltaTime.asSeconds(), actor);
            }
        }
    }
}

/**
 * @brief Renderiza todos los actores y las interfaces de usuario.
 * Llama a los métodos de renderizado de cada actor, muestra el contenido en ImGui,
 * y presenta las herramientas de interfaz gráfica.
 */
void
BaseApp::render() {
    NotificationService& notifier = NotificationService::getInstance();

    m_window->clear();
    for (auto& actor : m_actors) {
        if (!actor.isNull()) {
            actor->render(*m_window);
        }
    }

    // Mostrar el render en ImGui
    m_window->renderToTexture();  // Finaliza el render a la textura
    m_window->showInImGui();      // Muestra la textura en ImGui

    // Configuramos la consola y le pasamos los mensajes
    m_GUI.console(notifier.getNotifications());

    m_GUI.inspector();

    //Muestra ventana
    m_GUI.hierarchy(m_actors);

    m_window->render();
    m_window->display();
}

// Libera los recursos de la aplicación.
void
BaseApp::cleanup() {
    m_window->destroy();
    delete m_window;
}

/**
 * @brief Actualiza el movimiento de un actor siguiendo los puntos de recorrido definidos.
 * @param deltaTime: Tiempo de delta para sincronizar el movimiento.
 */
void
BaseApp::updateMovement(float deltaTime, EngineUtilities::TSharedPointer<Actor> circle) {
    // Verificar si el Circle es nulo
    if (!circle || circle.isNull()) return;

    // Obtener el componente Transform
    auto transform = circle->getComponent<Transform>();
    if (transform.isNull()) return;

    // Posici�n actual del destino (punto de recorrido)
    Vector2 targetPos = points[m_currentPoint];

    // Llamar al Seek del Transform
    transform->Seek(targetPos, 200.0f, deltaTime, 10.0f);

    // Obtener la posici�n actual del actor desde Transform
    Vector2 currentPos = transform->getPosition();

    // Comprobar si el actor ha alcanzado el destino (o esta cerca)
    float distanceToTarget = std::sqrt(std::pow(targetPos.x - currentPos.x, 2) + std::pow(targetPos.y - currentPos.y, 2));

    if (distanceToTarget < 10.0f) { // Umbral para considerar que ha llegado
        m_currentPoint = (m_currentPoint + 1);
        if (m_currentPoint > 8) {
            m_currentPoint = 0;
        }
    }
}