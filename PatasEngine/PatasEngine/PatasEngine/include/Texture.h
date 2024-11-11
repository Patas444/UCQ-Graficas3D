#pragma once
#include "Prerequisites.h"
#include "Component.h"

class
	Texture : public Component {
public:
	Texture() = default;

	/**
	 * @brief Constructor que inicializa y carga una textura desde un archivo.
	 * Intenta cargar la textura especificada con el nombre y extensi�n proporcionados.
	 * Si la carga falla, intenta cargar una textura por defecto ("Default.png").
	 */
	Texture(std::string textureName, std::string extension) : m_textureName(textureName),
		m_extension(extension),
		Component(ComponentType::TEXTURE) {
		if (!m_texture.loadFromFile(m_textureName + "." + m_extension)) {
			std::cout << "Error de carga de textura" << std::endl;
		}
		else {
			m_textureName = "Default";
			m_extension = "png";
			if (!m_texture.loadFromFile(m_textureName + "." + m_extension)) {
				std::cout << "Error de carga de textura" << std::endl;
			}
		}
	}

	virtual
		~Texture() = default;

	// Obtiene la referencia a la textura SFML cargada.
	sf::Texture& getTexture() {
		return m_texture;
	}
private:
	std::string m_textureName; // Nombre del archivo de la textura (sin extensi�n).
	std::string m_extension; // Extensi�n del archivo de la textura.
	sf::Texture m_texture; // Instancia de la textura SFML.
};