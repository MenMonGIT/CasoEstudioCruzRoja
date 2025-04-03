#ifndef DONORMANAGER_H
#define DONORMANAGER_H

#include "Donor.h"
#include "UserInterface.h"
#include "FileHandler.h"
#include <vector>

// Esta clase gestiona la interacción con los donantes, incluye registro, búsqueda, eliminación y visualización
class DonorManager {
private:
    UserInterface ui; // Es la interfaz de usuario para mostrar mensajes y solicitar entradas
    FileHandler fileHandler; // Maneja la lectura y escritura de datos en archivos
    std::vector<Donor> donors; // Es la lista temporal de donantes

public:
    // Constructor que inicializa DonorManager con el nombre del archivo de datos
    DonorManager(const std::string& fileName);

    // Registra un nuevo donante solicitando sus detalles
    void getDonorDetails();

    // Busca y muestra donantes según criterios 
    void searchAndDisplay() const;

    // Elimina un donante por nombre
    void deleteDonor(const std::string& donorName);

    // Muestra todos los donantes registrados
    void displayAllDonors() const;

    // Devuelve todos los donantes, esto se utiliza para las estadísticas
    std::vector<Donor> getAllDonors() const;
};

#endif
