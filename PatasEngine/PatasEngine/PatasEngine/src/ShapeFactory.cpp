#include "ShapeFactory.h"

/**
 * @brief Crea una figura seg�n el tipo especificado
 * ShapeType del Tipo de figura a crear una figura:
 * (CIRCLE, RECTANGLE, TRIANGLE.)
 */
sf::Shape*
ShapeFactory::createShape(ShapeType shapeType) {
  m_ShapeType = shapeType;
  switch (shapeType)
  {
  case NONE: {
    return nullptr;
  }
  // Crea un círculo de radio 10.
  case CIRCLE: {
    sf::CircleShape* circle = new sf::CircleShape(10.0f);
    m_shape = circle;
    return circle;
  }
  // Crea un rectángulo de tamaño 100x50.
  case RECTANGLE: {
    sf::RectangleShape* rectangle = new sf::RectangleShape(sf::Vector2(100.0f, 50.0f));
    m_shape = rectangle;
    return rectangle;
  }
  // Crea un triángulo usando un círculo de 3 lados con radio 50.
  case TRIANGLE: {
    sf::CircleShape* triangle = new sf::CircleShape(50.0f, 3);
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

// Define la posición de la figura usando un vector del Vector2 (De la libreria matematica).
void
ShapeFactory::setPosition(const Vector2& position) {
  if (m_shape) {
    m_shape->setPosition(position.x, position.y);
  }
}

// Establece la rotación de la figura en grados.
void
ShapeFactory::setRotation(float angle) {
  if (m_shape) {
    m_shape->setRotation(angle);
  }
}

// Establece la escala de la figura usando un vector del Vector2 (De la libreria matematica).
void
ShapeFactory::setScale(const Vector2& scl) {
  if (m_shape) {
    m_shape->setScale(scl.x, scl.y);
  }
}

// Cambia el color de relleno de la figura.
void
ShapeFactory::setFillColor(const sf::Color& color) {
  m_shape->setFillColor(color);
}