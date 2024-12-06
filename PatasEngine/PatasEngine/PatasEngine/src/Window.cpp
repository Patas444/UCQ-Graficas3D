#include "Window.h"

Window::Window(int width, int height, const std::string& title) {
  m_window = new sf::RenderWindow(sf::VideoMode(width, height), title);

  if (!m_window) {
    ERROR("Window", "Window", "CHECK CONSTRUCTOR");
  }
  else {
    MESSAGE("Window", "Window", "OK");
  }

  // Initialize the ImGui Resource
  ImGui::SFML::Init(*m_window);

  // Crear RenderTexture con las mismas dimensiones que la ventana
  if (!m_renderTexture.create(width, height)) {
    ERROR("Window", "RenderTexture", "CHECK CREATION");
  }
}

// Destructor de la clase Window que libera los recursos de ImGui y de la ventana.
Window::~Window() {
  delete m_window;
  delete m_window;
}

// Maneja los eventos de la ventana, incluyendo el cierre y el redimensionamiento.
void
Window::handleEvents() {
  sf::Event event;
  while (m_window->pollEvent(event)) {
    // Procesar los inputs de IMGUI
    ImGui::SFML::ProcessEvent(event);
    switch (event.type) {
    case sf::Event::Closed:
      m_window->close();
      break;
      // Manejar el evento de redimensionar
    case sf::Event::Resized:
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
  m_renderTexture.display();
}

// Muestra la RenderTexture en una ventana de ImGui.
void
Window::showInImGui() {
  const sf::Texture& texture = m_renderTexture.getTexture();

  // Obtener el tamaño de la textura
  ImVec2 size(texture.getSize().x, texture.getSize().y);

  // Renderizar la textura en ImGui con las coordenadas UV invertidas en el eje Y
  ImGui::Begin("Scene");
  ImGui::Image((void*)(intptr_t)texture.getNativeHandle(), size, ImVec2(0, 1), ImVec2(1, 0));
  ImGui::End();
}

// Actualiza ImGui con el deltaTime de la ventana.
void
Window::update() {
  // Almacena el deltaTime una sola vez
  deltaTime = clock.restart();

  // Usa el deltaTime para actualizar ImGui
  ImGui::SFML::Update(*m_window, deltaTime);
}

// Renderiza ImGui en la ventana.
void
Window::render() {
  ImGui::SFML::Render(*m_window);
}

// Libera recursos de ImGui y elimina el puntero de la ventana.
void
Window::destroy() {
  ImGui::SFML::Shutdown();
  SAFE_PTR_RELEASE(m_window);
}