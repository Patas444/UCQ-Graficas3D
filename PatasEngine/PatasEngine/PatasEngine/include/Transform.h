#pragma once
#include "Prerequisites.h"
#include "Component.h"
#include "Window.h"

class
    Transform : public Component {
public:
    Transform() : position(0.0f, 0.0f),
        rotation(0.0f, 0.0f),
        scale(1.0f, 1.0f),
        Component(ComponentType::TRANSFORM) {}

    virtual
    ~Transform() = default;

    /**
     * @brief Actualiza el componente de malla.
     * deltaTime El tiempo transcurrido desde la Ultima actualizaci�n.
     */
    void
    update(float deltaTime) override {}

    /**
     * @brief Renderiza el componente de malla.
     * deviceContext Contexto del dispositivo para operaciones gr�ficas.
     */
    void
    render(Window window) override {}

    // Libera los recursos asociados al componente.
    void
    destroy() {};

    /**
     * @brief Función que mueve el objeto hacia una posición objetivo con una velocidad específica.
     *
     * @param targetPosition La posición objetivo hacia la cual se mueve el objeto.
     * @param speed La velocidad de movimiento.
     * @param deltaTime El tiempo transcurrido desde la última actualización.
     * @param range La distancia mínima antes de que el movimiento hacia el objetivo se detenga.
     */
    void
    Seek(const sf::Vector2f& targetPosition,
            float speed,
            float deltaTime,
            float range) {
        sf::Vector2f direction = targetPosition - position;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (length > range) {
            direction /= length;  // Normaliza el vector
            position += direction * speed * deltaTime;
        }
    }


    // Establece la posición del objeto.
    void
        setPosition(const sf::Vector2f& _position) {
        position = _position;
    }

    // Establece la nueva rotación del objeto.
    void
        setRotation(const sf::Vector2f& _rotation) {
        rotation = _rotation;
    }

    // Establece la nueva escala del objeto.
    void
        setScale(const sf::Vector2f& _scale) {
        scale = _scale;
    }

    // Obtiene la posición actual del objeto.
    sf::Vector2f&
        getPosition() {
        return position;
    }

    // Obtiene la rotación actual del objeto.
    sf::Vector2f&
        getRotation() {
        return rotation;
    }

    // Obtiene la escala actual del objeto.
    sf::Vector2f&
        getScale() {
        return scale;
    }
private:
    sf::Vector2f position;  // Posicion del objeto.
    sf::Vector2f rotation;  // Rotacion del objeto.
    sf::Vector2f scale;     // Escala del objeto.
};