#include "Actor.h"

Actor::Actor(std::string actorName) {
    // Setup Actor Name 
    m_name = actorName;

    // Setup Shape 
    EngineUtilities::TSharedPointer<ShapeFactory> shape = EngineUtilities::MakeShared<ShapeFactory>();
    addComponent(shape);

    // Setup Transform
    EngineUtilities::TSharedPointer<Transform> transform = EngineUtilities::MakeShared<Transform>();
    addComponent(transform);
}

/**
 * @brief Actualiza los componentes del actor.
 * Sincroniza la posición, rotación y escala del objeto `ShapeFactory`
 * con los valores de transformación definidos en `Transform`.
 */
void
Actor::update(float deltaTime) {
    auto transform = getComponent<Transform>();
    auto shape = getComponent<ShapeFactory>();

    if (transform && shape) {
        Vector2 position(transform->getPosition().x, transform->getPosition().y);
        shape->setPosition(position);
        shape->setRotation(transform->getRotation().x);
        Vector2 scale(transform->getScale().x, transform->getScale().y);
        shape->setScale(scale);
    }
}

/**
 * @brief Renderiza el actor en la ventana proporcionada.
 * Recorre los componentes y dibuja el `ShapeFactory` asociado si está presente.
 */
void
Actor::render(Window& window) {
    for (unsigned int i = 0; i < components.size(); i++) {
        if (components[i].dynamic_pointer_cast<ShapeFactory>()) {
            window.draw(*components[i].dynamic_pointer_cast<ShapeFactory>()->getShape());
        }
    }
}

/**
 * @brief Destruye el actor.
 * Método vacío para potencial limpieza de recursos asociados al actor.
 */
void
Actor::destroy() {
}

// Obtiene el nombre del actor.
std::string
Actor::getName() const {
    return m_name;
}

// Agrega el nombre del actor.
void
Actor::setName(const std::string& newName) {
    m_name = newName;
}