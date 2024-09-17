#include <iostream>
#include <string>

class Nodo {
public:
    void* dato;
    Nodo* siguiente;

    Nodo(void* dato) : dato(dato), siguiente(nullptr) {}
};

class ListaEnlazada {
private:
    Nodo* cabeza;

public:
    ListaEnlazada() : cabeza(nullptr) {}

    void insertar(void* dato) {
        Nodo* nuevoNodo = new Nodo(dato);
        if (cabeza == nullptr) {
            cabeza = nuevoNodo;
        } else {
            Nodo* temp = cabeza;
            while (temp->siguiente != nullptr) {
                temp = temp->siguiente;
            }
            temp->siguiente = nuevoNodo;
        }
    }

    void eliminar(void* dato, const std::string& tipo) {
        if (cabeza == nullptr) {
            std::cout << "La lista está vacía." << std::endl;
            return;
        }

        if (comparar(cabeza->dato, dato, tipo)) {
            Nodo* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
            std::cout << "Elemento eliminado." << std::endl;
            return;
        }

        Nodo* temp = cabeza;
        while (temp->siguiente != nullptr) {
            if (comparar(temp->siguiente->dato, dato, tipo)) {
                Nodo* nodoAEliminar = temp->siguiente;
                temp->siguiente = temp->siguiente->siguiente;
                delete nodoAEliminar;
                std::cout << "Elemento eliminado." << std::endl;
                return;
            }
            temp = temp->siguiente;
        }
        std::cout << "Elemento no encontrado." << std::endl;
    }

    void modificar(void* datoViejo, void* datoNuevo, const std::string& tipo) {
        Nodo* temp = cabeza;
        while (temp != nullptr) {
            if (comparar(temp->dato, datoViejo, tipo)) {
                temp->dato = datoNuevo;
                std::cout << "Elemento modificado." << std::endl;
                return;
            }
            temp = temp->siguiente;
        }
        std::cout << "Elemento no encontrado." << std::endl;
    }

    void mostrar(const std::string& tipo) {
        Nodo* temp = cabeza;
        while (temp != nullptr) {
            imprimir(temp->dato, tipo);
            std::cout << " -> ";
            temp = temp->siguiente;
        }
        std::cout << "null" << std::endl;
    }

private:
    bool comparar(void* dato1, void* dato2, const std::string& tipo) {
        if (tipo == "entero") {
            return *static_cast<int*>(dato1) == *static_cast<int*>(dato2);
        } else if (tipo == "string") {
            return *static_cast<std::string*>(dato1) == *static_cast<std::string*>(dato2);
        } else if (tipo == "caracter") {
            return *static_cast<char*>(dato1) == *static_cast<char*>(dato2);
        }
        return false;
    }

    void imprimir(void* dato, const std::string& tipo) {
        if (tipo == "entero") {
            std::cout << *static_cast<int*>(dato);
        } else if (tipo == "string") {
            std::cout << *static_cast<std::string*>(dato);
        } else if (tipo == "caracter") {
            std::cout << *static_cast<char*>(dato);
        }
    }
};

int main() {
    std::string tipo;
    bool continuar = true;
    while (continuar) {
        std::cout << "Bienvenido/a al programa de lista enlazada. Seleccione el tipo de lista enlazada (entero, string, caracter): ";
        std::getline(std::cin, tipo);

        if (tipo != "entero" && tipo != "string" && tipo != "caracter") {
            std::cout << "Tipo de lista no válido. Por favor, elija 'entero', 'string' o 'caracter'." << std::endl;
            continue;
        }

        ListaEnlazada lista;

        bool submenu = true;
        while (submenu) {
            std::cout << "\nPor favor, seleccione una opción:\n";
            std::cout << "1. Insertar\n";
            std::cout << "2. Modificar\n";
            std::cout << "3. Mostrar\n";
            std::cout << "4. Eliminar\n";
            std::cout << "5. Volver al menú principal\n";
            std::cout << "6. Salir\n";

            int opcion;
            std::cin >> opcion;
            std::cin.ignore(); // Limpiar buffer

            switch (opcion) {
                case 1: {
                    std::cout << "Ingrese el dato que quiere insertar: ";
                    if (tipo == "entero") {
                        int* datoEntero = new int;
                        std::cin >> *datoEntero;
                        lista.insertar(static_cast<void*>(datoEntero));
                    } else if (tipo == "string") {
                        std::string* datoString = new std::string;
                        std::cin.ignore();
                        std::getline(std::cin, *datoString);
                        lista.insertar(static_cast<void*>(datoString));
                    } else if (tipo == "caracter") {
                        char* datoChar = new char;
                        std::cin >> *datoChar;
                        lista.insertar(static_cast<void*>(datoChar));
                    }
                    break;
                }
                case 2: {
                    std::cout << "Ingrese el dato que desea modificar: ";
                    void* datoViejo = nullptr;
                    void* datoNuevo = nullptr;

                    if (tipo == "entero") {
                        datoViejo = new int;
                        datoNuevo = new int;
                        std::cin >> *static_cast<int*>(datoViejo);
                        std::cout << "Ingrese el nuevo dato: ";
                        std::cin >> *static_cast<int*>(datoNuevo);
                    } else if (tipo == "string") {
                        datoViejo = new std::string;
                        datoNuevo = new std::string;
                        std::cin.ignore();
                        std::getline(std::cin, *static_cast<std::string*>(datoViejo));
                        std::cout << "Ingrese el nuevo dato: ";
                        std::getline(std::cin, *static_cast<std::string*>(datoNuevo));
                    } else if (tipo == "caracter") {
                        datoViejo = new char;
                        datoNuevo = new char;
                        std::cin >> *static_cast<char*>(datoViejo);
                        std::cout << "Ingrese el nuevo dato: ";
                        std::cin >> *static_cast<char*>(datoNuevo);
                    }
                    lista.modificar(datoViejo, datoNuevo, tipo);
                    break;
                }
                case 3: {
                    lista.mostrar(tipo);
                    break;
                }
                case 4: {
                    std::cout << "Ingrese el dato que desea eliminar: ";
                    if (tipo == "entero") {
                        int* datoEntero = new int;
                        std::cin >> *datoEntero;
                        lista.eliminar(static_cast<void*>(datoEntero), tipo);
                    } else if (tipo == "string") {
                        std::string* datoString = new std::string;
                        std::cin.ignore();
                        std::getline(std::cin, *datoString);
                        lista.eliminar(static_cast<void*>(datoString), tipo);
                    } else if (tipo == "caracter") {
                        char* datoChar = new char;
                        std::cin >> *datoChar;
                        lista.eliminar(static_cast<void*>(datoChar), tipo);
                    }
                    break;
                }
                case 5: {
                    submenu = false;
                    break;
                }
                case 6: {
                    submenu = false;
                    continuar = false;
                    break;
                }
                default: {
                    std::cout << "Opción no válida. Por favor, seleccione una opción del 1 al 6." << std::endl;
                }
            }
        }
    }

    return 0;
}
