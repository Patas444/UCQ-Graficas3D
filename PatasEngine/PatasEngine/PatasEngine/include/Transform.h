#pragma once
#include "Prerequisites.h"
#include "Component.h"
#include "Window.h"
#include "Vector2.h"

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
    Seek(const Vector2& targetPosition,
            float speed,
            float deltaTime,
            float range) {
        Vector2 direction = targetPosition - position;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (length > range) {
            direction /= length;  // Normaliza el vector
            position += direction * speed * deltaTime;
        }
    }


    // Establece la posición del objeto.
    void
        setPosition(const Vector2& _position) {
        position = _position;
    }

    // Establece la nueva rotación del objeto.
    void
        setRotation(const Vector2& _rotation) {
        rotation = _rotation;
    }

    // Establece la nueva escala del objeto.
    void
        setScale(const Vector2& _scale) {
        scale = _scale;
    }

    // Obtiene la posición actual del objeto.
    Vector2&
        getPosition() {
        return position;
    }

    // Obtiene la rotación actual del objeto.
    Vector2&
        getRotation() {
        return rotation;
    }

    // Obtiene la escala actual del objeto.
    Vector2&
        getScale() {
        return scale;
    }

    float*
        getPosData() {
        return &position.x;
    }

    float*
        getRotData() {
        return &rotation.x;
    }

    float*
        getScaData() {
        return &scale.x;
    }

private:
    Vector2  position;  // Posicion del objeto.
    Vector2  rotation;  // Rotacion del objeto.
    Vector2  scale;     // Escala del objeto.
};