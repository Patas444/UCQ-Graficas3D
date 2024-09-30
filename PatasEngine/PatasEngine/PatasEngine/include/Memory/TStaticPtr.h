#pragma once
namespace EngineUtilities {
   /**
   * Clase TStaticPtr para manejo de un puntero estático.
   *
   * La clase TStaticPtr gestiona un único objeto estático y proporciona métodos
   * para acceder al objeto, verificar si el puntero es nulo y realizar operaciones
   * básicas de manejo de memoria.
   */
    template<typename T>
    class TStaticPtr
    {
    public:
        // Inicializa el puntero estático al objeto.
        TStaticPtr() = default;

        // Constructor que toma un puntero crudo.
        explicit TStaticPtr(T* rawPtr)
        {
            if (instance != nullptr)
            {
                delete instance;
            }
            instance = rawPtr;
        }

        //  Destructor.
        ~TStaticPtr()
        {
            if (instance != nullptr)
            {
                delete instance;
                instance = nullptr;
            }
        }

        // Obtener el puntero crudo.
        static T* get()
        {
            return instance;
        }

        // Verificar si el puntero es nulo.
        static bool isNull()
        {
            return instance == nullptr;
        }

        // Reiniciar el puntero estático con un nuevo objeto.
        static void reset(T* rawPtr = nullptr)
        {
            if (instance != nullptr)
            {
                delete instance;
            }
            instance = rawPtr;
        }

    private:
        // Puntero estático al objeto gestionado.
        static T* instance; 
    };

    /*
    // Inicializar el puntero estático
    template<typename T>
    T* TStaticPtr<T>::instance = nullptr;

    // Ejemplo de uso de TStaticPtr
    class MyClass
    {
    public:
      MyClass(int value) : value(value)
      {
        std::cout << "MyClass constructor: " << value << std::endl;
      }

      ~MyClass()
      {
        std::cout << "MyClass destructor: " << value << std::endl;
      }

      void display() const
      {
        std::cout << "Value: " << value << std::endl;
      }

    private:
      int value;
    };

    int main()
    {
      {
        // Crear un TStaticPtr usando un puntero crudo
        TStaticPtr<MyClass>::reset(new MyClass(10));
        TStaticPtr<MyClass>::get()->display(); // Output: Value: 10

        // Comprobar si el puntero no es nulo
        if (!TStaticPtr<MyClass>::isNull())
        {
          std::cout << "TStaticPtr is not null" << std::endl;
        }

        // Reiniciar TStaticPtr con un nuevo objeto
        TStaticPtr<MyClass>::reset(new MyClass(20));
        TStaticPtr<MyClass>::get()->display(); // Output: Value: 20

        // Reiniciar con nullptr
        TStaticPtr<MyClass>::reset();
        if (TStaticPtr<MyClass>::isNull())
        {
          std::cout << "TStaticPtr is null after reset" << std::endl;
        }
      }

      return 0;
    }
    */
}