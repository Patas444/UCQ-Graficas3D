#pragma once
class Window;


//Tipos de componentes disponibles en el juego.
enum
ComponentType {
NONE = 0,
TRANSFORM = 1,
SPRITE = 2,
RENDERER = 3,
PHYSICS = 4,
AUDIOSOURCE = 5,
SHAPE = 6,
};

//Clase base abstracta para todos los componentes del juego.
class
Component {
public:

	//Constructor por defecto.
	Component() = default;

	//Constructor con tipo de componente.
	Component(const ComponentType type) : m_type(type) {}


	//Destructor virtual.
	virtual
	~Component() = default;

	// Método virtual puro para actualizar el componente.
	virtual void
	update(float deltaTime) = 0;

	//Método virtual puro para renderizar el componente.
	virtual void
	render(Window window) = 0;

	//Obtiene el tipo del componente.
	ComponentType
	getType() const { return m_type; }

protected:
	// Tipo de Componente.
	ComponentType m_type; 
};