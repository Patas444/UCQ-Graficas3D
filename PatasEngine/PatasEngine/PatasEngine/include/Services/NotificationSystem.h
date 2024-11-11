#pragma once
#include "Prerequisites.h"

class NotificationService {
private:
    // Constructor privado para evitar instancias multiples
    NotificationService() {}
    // Eliminar el operador de copia y asignaci�n para evitar duplicaciones
    NotificationService(const NotificationService&) = delete;
    NotificationService& operator=(const NotificationService&) = delete;
public:

    /**
     * @brief Obtiene la instancia única de NotificationService.
     * Este método estático devuelve la única instancia de NotificationService,
     * asegurando que solo exista una en toda la aplicación.
     */
    static NotificationService& getInstance() {
        static NotificationService instance;
        return instance;
    }

    // Agrega un mensaje al registro con un código de error específico.
    void addMessage(ConsolErrorType code, const std::string& message) {
        m_programMessages[code].push_back(message);
    }

    // Agregar un mensaje informativo
    void Log(const std::string& message) {
        ConsolErrorType code = ConsolErrorType::NORMAL;
        m_programMessages[code].push_back(message);
    }

    /**
     * @brief Recupera los mensajes asociados a un código de error específico.
     * Combina todos los mensajes asociados al código de error proporcionado
     * en un solo string, cada mensaje en una nueva línea.
     */
    std::string getMessage(ConsolErrorType code) const {
        auto it = m_programMessages.find(code);
        if (it != m_programMessages.end()) {
            std::string combinedMessages;
            for (const auto& message : it->second) {
                combinedMessages += message + "\n";
            }
            return combinedMessages;
        }
        else {
            return "Message not found";
        }
    }

    /**
     * @brief Muestra en consola todos los mensajes registrados.
     * Imprime en la consola cada código de error junto con su lista de mensajes.
     */
    void showAllMessages() const {
        for (const auto& pair : m_programMessages) {
            std::cout << "Code: " << pair.first << " - Messages: " << std::endl;
            for (const auto& message : pair.second) {
                std::cout << "   " << message << std::endl;
            }
        }
    }
    // Metodo para guardar los mensajes en un archivo
    void saveMessagesToFile(const std::string& filename) const {
      std::ofstream file(filename);
      if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo para guardar los mensajes." << std::endl;
        return;
      }
      for (const auto& pair : m_programMessages) {
        file << "Code: " << pair.first << " - Messages: " << std::endl;
        for (const auto& message : pair.second) {
          file << "   " << message << "\n";
        }
      }
      file.close();
      std::cout << "Mensajes guardados en el archivo: " << filename << std::endl;
    }

    // Obtiene todas las notificaciones almacenadas.
    std::map<ConsolErrorType, std::vector<std::string>>& getNotifications() {
        return m_programMessages;
    }
private:
    // Mapa para almacenar los mensajes del programa, cada codigo de error tiene una lista de mensajes
    std::map<ConsolErrorType, std::vector<std::string>> m_programMessages;
};