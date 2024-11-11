#include "ShapeFactory.h"

sf::Shape*
ShapeFactory::createShape(ShapeType shapeType) {
	m_shapeType = shapeType;
	switch (shapeType) {
	case EMPTY: {
		return nullptr;
	}
	// Crea un círculo de radio 10.
	case CIRCLE: {
		sf::CircleShape* circle = new sf::CircleShape(10.0f);
		circle->setFillColor(sf::Color::White);
		m_shape = circle;
		return circle;
	}
	// Crea un rectángulo de tamaño 100x50.
	case RECTANGLE: {
		sf::RectangleShape* rectangle = new sf::RectangleShape(sf::Vector2(100.0f, 50.0f));
		rectangle->setFillColor(sf::Color::White);
		m_shape = rectangle;
		return rectangle;
	}
	// Crea un triángulo usando un círculo de 3 lados con radio 50.
	case TRIANGLE: {
		sf::CircleShape* triangle = new sf::CircleShape(50.0f, 3);
		triangle->setFillColor(sf::Color::White);
		m_shape = triangle;
		return triangle;
	}
	default:
		return nullptr;
	}
}

// Define la posición de la figura en coordenadas (x, y).
void
ShapeFactory::setPosition(float x, float y) {
	if (m_shape) {
		m_shape->setPosition(x, y);
	}
}

// Define la posición de la figura usando un vector sf::Vector2f.
void
ShapeFactory::setPosition(const sf::Vector2f& position) {
	if (m_shape) {
		m_shape->setPosition(position);
	}
}

// Establece la rotación de la figura en grados.
void
ShapeFactory::setRotation(float angle) {
	if (m_shape) {
		m_shape->setRotation(angle);
	}
}

// Establece la escala de la figura usando un vector sf::Vector2f.
void
ShapeFactory::setScale(const sf::Vector2f& scl) {
	if (m_shape) {
		m_shape->setScale(scl);
	}
}

// Cambia el color de relleno de la figura.
void
ShapeFactory::setFillColor(const sf::Color& color) {
	m_shape->setFillColor(color);
}