#pragma once

#include "Prerequisites.h"
#include "Component.h"

class Window;

class
    Entity {
public:

    //Destructor virtual.

    virtual
        ~Entity() = default;

    //Método virtual puro para actualizar la entidad.
    virtual void
        update(float deltaTime) = 0;

    //Método virtual puro para renderizar la entidad.
    virtual void
        render(Window& window) = 0;


    //Agrega un componente a la entidad.
    template <typename T>
    void addComponent(EngineUtilities::TSharedPointer<T> component) {
        static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
        components.push_back(component.template dynamic_pointer_cast<Component>());
    }




    //Obtiene un componente de la entidad.
    template<typename T>
    EngineUtilities::TSharedPointer<T>
        getComponent() {
        for (auto& component : components) {
            EngineUtilities::TSharedPointer<T> specificComponent = component.template dynamic_pointer_cast<T>();
            if (specificComponent) {
                return specificComponent;
            }
        }
        return EngineUtilities::TSharedPointer<T>();
    }

protected:
    bool isActive;

    int id;

    std::vector<EngineUtilities::TSharedPointer<Component>> components;
};