#pragma once
#include "TSharedPointer.h"

namespace EngineUtilities {
	/**
		 * Clase TWeakPointer para observar objetos gestionados por TSharedPointer sin aumentar el recuento de referencias.
		 *
		 * La clase TWeakPointer proporciona una manera de observar un objeto gestionado por un TSharedPointer
		 * sin tener influencia sobre el recuento de referencias del objeto. Permite acceder al objeto solo si
		 * aún existe.
		 */
	template<typename T>
	class TWeakPointer
	{
	public:

		// Constructor por defecto.
		TWeakPointer() : ptr(nullptr), refCount(nullptr) {}

		// Constructor que toma un TSharedPointer.
		TWeakPointer(const TSharedPointer<T>& sharedPtr)
			: ptr(sharedPtr.ptr), refCount(sharedPtr.refCount) {}

		// Convertir TWeakPointer a TSharedPointer.
		TSharedPointer<T> lock() const
		{
			if (refCount && *refCount > 0)
			{
				return TSharedPointer<T>(ptr, refCount);
			}
			return TSharedPointer<T>();
		}

		// Hacer que TSharedPointer sea un amigo para acceder a los miembros privados.
		template<typename U>
		friend class TSharedPointer;

	private:
		// Puntero al objeto observado.
		T* ptr;
		// Puntero al recuento de referencias del TSharedPointer original.
		int* refCount; 
	};

	/*
	#include "TSharedPointer.h"
#include "TWeakPointer.h"

class MyClass
{
public:
		MyClass(int val) : value(val) {}
		void display() const { std::cout << "Value: " << value << std::endl; }

private:
		int value;
};

int main()
{
		{
				// Crear un TSharedPointer que gestiona un objeto MyClass
				EngineUtilities::TSharedPointer<MyClass> sp1 = EngineUtilities::MakeShared<MyClass>(10);
				sp1->display();

				// Crear un TWeakPointer a partir del TSharedPointer
				EngineUtilities::TWeakPointer<MyClass> wp1(sp1);

				// Intentar obtener un TSharedPointer a partir del TWeakPointer
				EngineUtilities::TSharedPointer<MyClass> sp2 = wp1.lock();
				if (!sp2.isNull())
				{
						sp2->display(); // Debería mostrar el valor 10
				}
				else
				{
						std::cout << "wp1 expired." << std::endl;
				}

				// Crear un nuevo TSharedPointer y mover el puntero compartido
				EngineUtilities::TSharedPointer<MyClass> sp3 = EngineUtilities::MakeShared<MyClass>(20);
				sp3 = std::move(sp1); // Mueve la propiedad de sp1 a sp3

				// El puntero compartido original (sp1) ahora está vacío
				EngineUtilities::TSharedPointer<MyClass> sp4 = wp1.lock();
				if (sp4.isNull())
				{
						std::cout << "sp1 has been moved and is now null." << std::endl;
				}

				// Intentar obtener un TSharedPointer después del movimiento
				if (sp3.isNull())
				{
						std::cout << "sp3 is null." << std::endl;
				}
				else
				{
						sp3->display(); // Debería mostrar el valor 20
				}
		} // Aquí, tanto sp2 como sp4 se destruyen y la memoria de MyClass se libera automáticamente

		return 0;
}
*/
}