#include "GUI.h"
#include "Window.h"
#include "Actor.h"
#include "transform.h"
#include "Services/NotificationSystem.h"

// Inicializa la GUI estableciendo el estilo de la interfaz.
void
GUI::init() {
					
	setupGUIStyle(); // Setup GUI Style
}

// Actualiza el estado de la GUI. 
void GUI::update()
{
}

// Renderiza la GUI.
void GUI::render()
{
}

// Libera recursos y destruye la GUI.
void
GUI::destroy() {
}

// Configuraci�n de los colores basados en el estilo de Unreal Engine 5
void
GUI::setupGUIStyle() {
	ImGuiStyle& style = ImGui::GetStyle();
	ImVec4* colors = style.Colors;

	colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);  // Fondo de ventana
	colors[ImGuiCol_Border] = ImVec4(0.40f, 0.40f, 0.40f, 0.50f);  // Bordes
	colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);  // Fondo de cuadros
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);  // Hover sobre cuadros
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.34f, 0.34f, 0.34f, 1.00f);  // Cuadro activo
	colors[ImGuiCol_TitleBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);  // Fondo del t�tulo
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);  // T�tulo activo
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);  // Fondo de la barra de men�
	colors[ImGuiCol_Button] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);  // Bot�n inactivo
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);  // Bot�n hover
	colors[ImGuiCol_ButtonActive] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);  // Bot�n activo
	colors[ImGuiCol_Text] = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);  // Texto principal
	colors[ImGuiCol_TextDisabled] = ImVec4(0.55f, 0.55f, 0.55f, 1.00f);  // Texto deshabilitado
	colors[ImGuiCol_Header] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);  // Encabezado
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.34f, 0.34f, 0.34f, 1.00f);  // Encabezado hover
	colors[ImGuiCol_HeaderActive] = ImVec4(0.45f, 0.45f, 0.45f, 1.00f);  // Encabezado activo
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);  // Fondo scrollbar
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);  // Scrollbar inactivo
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f); // Scrollbar hover
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f); // Scrollbar activo
	colors[ImGuiCol_CheckMark] = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);  // Marca de check

	// Ajustes de estilo general
	style.WindowRounding = 5.0f;   // Redondeo de bordes de ventanas
	style.FrameRounding = 5.0f;   // Redondeo de bordes de cuadros
	style.ScrollbarRounding = 5.0f;   // Redondeo de bordes de scrollbar
	style.GrabRounding = 5.0f;   // Redondeo de bordes de botones de agarrar
	style.FrameBorderSize = 1.0f;   // Grosor del borde de cuadros
	style.WindowBorderSize = 1.0f;   // Grosor del borde de ventanas
	style.PopupBorderSize = 1.0f;   // Grosor del borde de popups
}

/**
 * @brief Muestra una consola en la interfaz,
 * Permite visualizar los mensajes de error, advertencia e información.
 * También permite el filtrado de mensajes.
 */
void
GUI::console(const std::map<ConsolErrorType, std::vector<std::string>>& programMessages) {
	ImGui::Begin("Console");
	static ImGuiTextFilter filter; // Filtro de búsqueda
	filter.Draw("Filter (\"error\", \"warning\", etc.)", 180.0f);
	ImGui::Separator();
	ImGui::BeginChild("ScrollingRegion", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
	for (const auto& pair : programMessages) {
		// Establece color según el tipo de mensaje
		ImVec4 color;
		switch (pair.first) {
		case ConsolErrorType::ERROR:
			color = ImVec4(1.0f, 0.4f, 0.4f, 1.0f); // Rojo para errores
			break;
		case ConsolErrorType::WARNING:
			color = ImVec4(1.0f, 1.0f, 0.4f, 1.0f); // Amarillo para advertencias
			break;
		case ConsolErrorType::NORMAL:
		default:
			color = ImVec4(0.8f, 0.8f, 0.8f, 1.0f); // Gris para mensajes de información
			break;
		}
		for (const auto& message : pair.second) {
			if (!filter.PassFilter(message.c_str())) continue; // Filtrar mensajes según el filtro de búsqueda
			ImGui::PushStyleColor(ImGuiCol_Text, color);
			ImGui::Text("[%d] %s", pair.first, message.c_str());
			ImGui::PopStyleColor();
		}
	}
	if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
		ImGui::SetScrollHereY(1.0f);
	ImGui::EndChild();
	ImGui::End();
}

/**
 * @brief Muestra la jerarquía de actores en la interfaz y permite seleccionar un actor.
 * Permite visualizar la posicion y escala del actor seleccionado.
 */
void GUI::hierarchy(const std::vector<EngineUtilities::TSharedPointer<Actor>>& actors, int& selectedActorID) {
	ImGui::Begin("Hierarchy"); // Abrir la ventana de jerarquía


	for (int i = 0; i < actors.size(); ++i) {
		if (!actors[i].isNull()) {
			if (ImGui::Selectable(actors[i]->getName().c_str(), selectedActorID == i)) {
				selectedActorID = i;  // Establecer actor seleccionado
			}
		}
	}

	ImGui::End(); // Cerrar la ventana de jerarquía
}

/**
 * @brief Muestra la ventana del Inspector.
 * Permite visualizar y modificación de atributos del actor actualmente seleccionado.
 */
void GUI::inspector(EngineUtilities::TSharedPointer<Actor> selectedActor) {
	if (selectedActor.isNull()) return;

	ImGui::Begin("Inspector"); // Abrir la ventana del Inspector

	// Mostrar el nombre del actor
	ImGui::Text("Actor: %s", selectedActor->getName().c_str());

	auto transform = selectedActor->getComponent<Transform>();
	if (!transform.isNull()) {
		Vector2 position = transform->getPosition();
		Vector2 rotation = transform->getRotation(); // Cambié esto a vector para alinearlo con el formato
		Vector2 scale = transform->getScale();

		ImGui::Separator();

		// Sección de posición
		ImGui::Text("Position");
		ImGui::PushItemWidth(50.0f);

		// Eje X (rojo)
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.8f, 0.1f, 0.1f, 1.0f));
		ImGui::Text("X");
		ImGui::PopStyleColor();
		ImGui::SameLine();
		ImGui::InputFloat("##PosX", &position.x);

		// Eje Y (verde)
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.1f, 0.8f, 0.1f, 1.0f));
		ImGui::Text("Y");
		ImGui::PopStyleColor();
		ImGui::SameLine();
		ImGui::InputFloat("##PosY", &position.y);

		ImGui::Separator();

		// Sección de rotación
		ImGui::Text("Rotation");

		// Eje X (rojo)
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.8f, 0.1f, 0.1f, 1.0f));
		ImGui::Text("X");
		ImGui::PopStyleColor();
		ImGui::SameLine();
		ImGui::InputFloat("##RotX", &rotation.x);

		// Eje Y (verde)
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.1f, 0.8f, 0.1f, 1.0f));
		ImGui::Text("Y");
		ImGui::PopStyleColor();
		ImGui::SameLine();
		ImGui::InputFloat("##RotY", &rotation.y);

		ImGui::Separator();

		// Sección de escala
		ImGui::Text("Scale");

		// Eje X (rojo)
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.8f, 0.1f, 0.1f, 1.0f));
		ImGui::Text("X");
		ImGui::PopStyleColor();
		ImGui::SameLine();
		ImGui::InputFloat("##ScaleX", &scale.x);

		// Eje Y (verde)
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.1f, 0.8f, 0.1f, 1.0f));
		ImGui::Text("Y");
		ImGui::PopStyleColor();
		ImGui::SameLine();
		ImGui::InputFloat("##ScaleY", &scale.y);

		// Aplicar cambios a la transformación
		transform->setPosition(position);
		transform->setRotation(rotation);
		transform->setScale(scale);
	}

	ImGui::End(); // Cerrar la ventana del Inspector
}

/**
 * @brief Muestra un menú para la creación de actores. permitiendo seleccionar nombre y forma.
 * Permite crear un actor con cualquiera de las siguintes formas(Cuadrado/Circulo/Triangulo)
 * y darle un nombre.
 */
void GUI::actorCreationMenu(std::vector<EngineUtilities::TSharedPointer<Actor>>& actors) {
	static char actorName[128] = "";  // Para almacenar el nombre del actor temporalmente
	static int selectedShape = 0;     // 0: Rectángulo, 1: Círculo, 2: Triángulo

	ImGui::Begin("Actor Creation");

	ImGui::InputText("Actor Name", actorName, IM_ARRAYSIZE(actorName));
	ImGui::Combo("Shape", &selectedShape, "Rectangle\0Circle\0Triangle\0");

	if (ImGui::Button("Create Actor")) {
		std::string name = actorName;

		if (name.empty()) {
			// Enviar mensaje de error si el nombre está vacío
			NotificationService& notifier = NotificationService::getInstance();
			notifier.addMessage(ConsolErrorType::ERROR, "Actor creation failed: Actor name cannot be empty.");
		}
		else {
			// Crear el actor con el nombre y forma seleccionada
			EngineUtilities::TSharedPointer<Actor> newActor = EngineUtilities::MakeShared<Actor>(name);

			switch (selectedShape) {
			case 0:
				newActor->getComponent<ShapeFactory>()->createShape(ShapeType::RECTANGLE);
				break;
			case 1:
				newActor->getComponent<ShapeFactory>()->createShape(ShapeType::CIRCLE);
				break;
			case 2:
				newActor->getComponent<ShapeFactory>()->createShape(ShapeType::TRIANGLE);
				break;
			}

			// Agregar el nuevo actor al vector de actores
			actors.push_back(newActor);

			// Notificar éxito en la creación
			NotificationService& notifier = NotificationService::getInstance();
			notifier.addMessage(ConsolErrorType::NORMAL, "Actor '" + name + "' created successfully.");

			// Limpiar el campo de nombre para el próximo actor
			actorName[0] = '\0';
		}
	}
	ImGui::End();

}