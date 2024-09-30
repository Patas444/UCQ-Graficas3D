#pragma once
#include "Prerequisites.h"
#include "Entity.h"
#include "ShapeFactory.h"

class
Actor : Entity {
public:
    //Constructor por defecto.
    Actor() = default;

    Actor(std::string actorName);

    
    //Destructor virtual.
    virtual
        ~Actor() = default;

    //Actualiza el actor.
    void
        update(float deltaTime) override;


    //Renderiza el actor.
    void
        render(Window& window) override;


    //Destruye el actor y libera los recursos asociados.
    void
        destroy();

    //Obtiene un componente específico del actor.
    template <typename T>
    EngineUtilities::TSharedPointer<T>
        getComponent();
private:
    // Nombre del actor.
    std::string m_name = "Actor"; 
};

template<typename T>
inline EngineUtilities::TSharedPointer<T>
Actor::getComponent() {
    for (auto& component : components) {
        EngineUtilities::TSharedPointer<T> specificComponent = component.template dynamic_pointer_cast<T>();
        if (specificComponent) {
            return specificComponent;
        }
    }
    // Devuelve un TSharedPointer vacío si no se encuentra el componente
    return EngineUtilities::TSharedPointer<T>();
}
