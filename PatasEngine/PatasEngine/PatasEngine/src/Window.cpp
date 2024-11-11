#include "Window.h"
#include "GUI.h"
#include "Prerequisites.h"
#include <SFML/Graphics.hpp>

Window::Window(int width, int height, const std::string& title) {
	// Crear una nueva ventana con el título y las dimensiones especificadas.
	m_window = new sf::RenderWindow(sf::VideoMode(width, height), title);

	// Verifica si la ventana se creó correctamente
	if (!m_window) {
		ERROR("Window", "Window", "CHECK CONSTRUCTOR");
	}
	else {
		MESSAGE("Window", "Window", "OK");
	}

	// Initalize the ImGui Resource
	ImGui::SFML::Init(*m_window);

	// Crear RenderTexture con las mismas dimensiones que la ventana
	if (!m_renderTexture.create(width, height)) {
		ERROR("Window", "RenderTexture", "CHECK CREATION");
	}
}

// Destructor de la clase Window que libera los recursos de ImGui y de la ventana.
Window::~Window() {
	ImGui::SFML::Shutdown();
	delete m_window;
}

// Maneja los eventos de la ventana, incluyendo el cierre y el redimensionamiento.
void
Window::handleEvents() {
	sf::Event event;
	while (m_window->pollEvent(event)) {
		// Process Input Events into ImGui
		ImGui::SFML::ProcessEvent(event);
		switch (event.type) {
		case sf::Event::Closed:
			m_window->close();
			break;
		case sf::Event::Resized:
			// Obtener el nuevo tama�o de la ventana
			unsigned int width = event.size.width;
			unsigned int height = event.size.height;

			m_view = m_window->getView();
			m_view.setSize(static_cast<float>(width), static_cast<float>(height));
			m_window->setView(m_view);

			// Actualizar RenderTexture si la ventana cambia de tama�o
			m_renderTexture.create(width, height);
			break;
		}
	}
}

// Limpia la ventana y la RenderTexture.
void
Window::clear() {
	if (m_window != nullptr) {
		m_window->clear();
	}
	else {
		ERROR("Window", "clear", "CHECK FOR WINDOW POINTER DATA");
	}
	if (m_renderTexture.getSize().x > 0 && m_renderTexture.getSize().y > 0) {
		m_renderTexture.clear();
	}
}

// Muestra el contenido de la ventana en pantalla.
void
Window::display() {
	if (m_window != nullptr) {
		m_window->display();
	}
	else {
		ERROR("Window", "display", "CHECK FOR WINDOW POINTER DATA");
	}
}

// Verifica si la ventana está abierta.
bool
Window::isOpen() const {
	if (m_window != nullptr) {
		return m_window->isOpen();
	}
	else {
		ERROR("Window", "isOpen", "CHECK FOR WINDOW POINTER DATA");
		return false;
	}
}

// Dibuja un objeto en la RenderTexture.
void
Window::draw(const sf::Drawable& drawable) {
	
	// Dibujar en la RenderTexture en lugar de la ventana directamente
	if (m_renderTexture.getSize().x > 0 && m_renderTexture.getSize().y > 0) {
		m_renderTexture.draw(drawable);
	}
}

// Obtiene el puntero a la ventana.
sf::RenderWindow*
Window::getWindow() {
	if (m_window != nullptr) {
		return m_window;
	}
	else {
		ERROR("Window", "getWindow", "CHECK FOR WINDOW POINTER DATA");
		return nullptr;
	}
}

// Finaliza el proceso de renderizado en la RenderTexture.
void
Window::renderToTexture() {
	// Despu�s de renderizar todo lo que quieras en la textura
	m_renderTexture.display();
}

// Aplica un estilo personalizado a la interfaz de ImGui.
void Window::setCustomStyle() {
	ImGuiStyle& style = ImGui::GetStyle();

	// Configuración general de los bordes y tamaños
	style.WindowRounding = 8.0f;
	style.FrameRounding = 5.0f;
	style.ScrollbarRounding = 12.0f;
	style.GrabRounding = 5.0f;
	style.WindowBorderSize = 1.0f;
	style.FrameBorderSize = 1.0f;
	style.PopupBorderSize = 1.0f;
	style.WindowPadding = ImVec2(10, 10);

	// Colores de la interfaz estilo Mario Galaxy
	ImVec4* colors = style.Colors;
	colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.1f, 1.0f);       // Fondo de ventana, azul oscuro
	colors[ImGuiCol_TitleBg] = ImVec4(0.1f, 0.1f, 0.4f, 1.0f);        // Fondo del título, morado
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.2f, 0.2f, 0.6f, 1.0f);  // Fondo del título activo
	colors[ImGuiCol_FrameBg] = ImVec4(0.0f, 0.0f, 0.2f, 1.0f);        // Fondo de cuadro, azul oscuro
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.4f, 0.4f, 0.9f, 0.6f); // Fondo de cuadro al pasar el cursor
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.6f, 0.6f, 1.0f, 0.6f);  // Fondo de cuadro activo
	colors[ImGuiCol_Button] = ImVec4(0.2f, 0.2f, 0.5f, 1.0f);         // Color de botón
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.3f, 0.3f, 0.7f, 1.0f);  // Color de botón al pasar el cursor
	colors[ImGuiCol_ButtonActive] = ImVec4(0.4f, 0.4f, 0.8f, 1.0f);   // Color de botón activo
	colors[ImGuiCol_Text] = ImVec4(0.9f, 0.9f, 0.9f, 1.0f);           // Color de texto blanco
	colors[ImGuiCol_Border] = ImVec4(0.6f, 0.6f, 0.9f, 0.7f);         // Color de borde, azul claro
	colors[ImGuiCol_CheckMark] = ImVec4(0.8f, 0.8f, 1.0f, 1.0f);      // Color de las marcas de selección
	colors[ImGuiCol_SliderGrab] = ImVec4(0.6f, 0.6f, 1.0f, 1.0f);     // Color del deslizador
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.8f, 0.8f, 1.0f, 1.0f); // Color del deslizador activo
}

// Muestra la RenderTexture en una ventana de ImGui.
void Window::showInImGui() {
	setCustomStyle();  // Llama a la función para aplicar el estilo personalizado
	const sf::Texture& texture = m_renderTexture.getTexture();
	ImVec2 size(texture.getSize().x, texture.getSize().y);

	// Panel de la Escena
	ImGui::Begin("Scene");
	ImGui::Image((void*)(intptr_t)texture.getNativeHandle(), size, ImVec2(0, 1), ImVec2(1, 0));
	ImGui::End();

}

// Actualiza ImGui con el deltaTime de la ventana.
void
Window::update() {
	// Almacena el deltaTime una sola vez
	deltaTime = clock.restart();

	// Usa ese deltaTime para actualizar ImGui
	ImGui::SFML::Update(*m_window, deltaTime);

}

// Renderiza ImGui en la ventana.
void Window::render()
{
	ImGui::SFML::Render(*m_window);
}

// Libera recursos de ImGui y elimina el puntero de la ventana.
void
Window::destroy() {
	ImGui::SFML::Shutdown();
	SAFE_PTR_RELEASE(m_window);
}