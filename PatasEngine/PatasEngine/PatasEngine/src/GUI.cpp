#include "GUI.h"
#include "Window.h"
#include "imgui_internal.h"

// Inicializa la GUI estableciendo el estilo de la interfaz.
void
GUI::init() {

    // Setup GUI Style
    setupGUIStyle();

}

// Actualiza el estado de la GUI. 
void
GUI::update() {
}

// Renderiza la GUI.
void
GUI::render() {
}

// Libera recursos y destruye la GUI.
void
GUI::destroy() {
}

// Configura el estilo y los colores de la GUI mediante ImGUI
void GUI::setupGUIStyle() {
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

void
GUI::console(std::map<ConsolErrorType, std::string> programMessages) {
    ImGui::Begin("Console");
    for (const auto& pair : programMessages) {
        ImGui::Text("Code: %d - Message: %s", pair.first, pair.second.c_str());
    }
    ImGui::End();

}

/**
 * @brief Muestra la jerarquía de actores en la interfaz y permite seleccionar un actor.
 * Permite visualizar la posicion y escala del actor seleccionado.
 */
void
GUI::hierarchy(std::vector<EngineUtilities::TSharedPointer<Actor>>& actors) {
    NotificationService& notifier = NotificationService::getInstance();

    ImGui::Begin("Hierarchy");

    for (int i = 0; i < actors.size(); ++i) {
        auto& actor = actors[i];
        if (actor.isNull()) continue;

        ImGui::PushID(i);
        std::string displayName = std::to_string(i) + " - " + actor->getName();
        if (ImGui::Selectable(displayName.c_str(), selectedActor == actor)) {
            selectedActor = actor;
        }
        ImGui::PopID();
    }

    ImGui::Separator();
    ImGui::Spacing();

    if (ImGui::Button("Create Circle")) {
        auto circleAct = EngineUtilities::MakeShared<Actor>("Circle");
        if (!circleAct.isNull()) {
            circleAct->getComponent<ShapeFactory>()->createShape(ShapeType::CIRCLE);

            circleAct->getComponent<Transform>()->setTransform(Vector2(100.0f, 100.0f),
                Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f));

            actors.push_back(circleAct);

            notifier.addMessage(ConsolErrorType::NORMAL, "Actor '" + circleAct->getName() + "' created successfully.");
        }
    }

    if (ImGui::Button("Create Rectangle")) {
        auto ractangleAct = EngineUtilities::MakeShared<Actor>("Rectangle");
        if (!ractangleAct.isNull()) {
            ractangleAct->getComponent<ShapeFactory>()->createShape(ShapeType::RECTANGLE);

            ractangleAct->getComponent<Transform>()->setTransform(Vector2(200.0f, 150.0f),
                Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f));
            actors.push_back(ractangleAct);

            notifier.addMessage(ConsolErrorType::NORMAL, "Actor '" + ractangleAct->getName() + "' created successfully.");
        }
    }

    if (ImGui::Button("Create Triangle")) {
        auto triangleAct = EngineUtilities::MakeShared<Actor>("Triangle");
        if (!triangleAct.isNull()) {
            triangleAct->getComponent<ShapeFactory>()->createShape(ShapeType::TRIANGLE);

            triangleAct->getComponent<Transform>()->setTransform(Vector2(150.0f, 200.0f),
                Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f));
            actors.push_back(triangleAct);

            notifier.addMessage(ConsolErrorType::NORMAL, "Actor '" + triangleAct->getName() + "' created successfully.");
        }
    }

    ImGui::End();
}

/**
 * @brief Muestra la ventana del Inspector.
 * Permite visualizar y modificación de atributos del actor actualmente seleccionado.
 */
void
GUI::inspector() {

    if (selectedActor.isNull()) {
        return;
    }

    ImGui::Begin("Inspector");

    // Muestra el nombre del actor
    char objectName[128];
    std::string name = selectedActor->getName();

    if (name.size() < sizeof(objectName)) {
        std::copy(name.begin(), name.end(), objectName);
        objectName[name.size()] = '\0'; // Termina con null
    }

    // Campo para editar el nombre del objeto
    if (ImGui::InputText("Name", objectName, sizeof(objectName))) {
        selectedActor->setName(std::string(objectName));
    }

    // Obtiene el componente Transform del actor
    auto transform = selectedActor->getComponent<Transform>();
    if (!transform.isNull()) {

        float* m_position = new float[2];
        float* m_rotation = new float[2];
        float* m_scale = new float[2];
        vec2Control("Position", selectedActor->getComponent<Transform>()->getPosData());
        vec2Control("Rotation", selectedActor->getComponent<Transform>()->getRotData());
        vec2Control("Scale", selectedActor->getComponent<Transform>()->getSclData());
    }

    ImGui::End();
}

/**
 * @brief Muestra un menú para la creación de actores. permitiendo seleccionar nombre y forma.
 * Permite crear un actor con cualquiera de las siguintes formas(Cuadrado/Circulo/Triangulo)
 * y darle un nombre.
 */
void
GUI::vec2Control(const std::string& label, float* values, float resetValue, float columnWidth) {
    ImGuiIO& io = ImGui::GetIO();
    auto boldFont = io.Fonts->Fonts[0];

    ImGui::PushID(label.c_str());

    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, columnWidth);
    ImGui::Text(label.c_str());
    ImGui::NextColumn();

    ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

    float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
    ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("X", buttonSize)) values[0] = resetValue;
    ImGui::PopFont();
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##X", &values[0], 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("Y", buttonSize)) values[1] = resetValue;
    ImGui::PopFont();
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##Y", &values[1], 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PopStyleVar();
    ImGui::Columns(1);

    ImGui::PopID();
}