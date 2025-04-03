#include "DonorManager.h"
#include "Utils.h"
#include <iostream>
#include "GetApi.h"

// Este constructor inicializa DonorManager con el nombre del archivo de datos.
DonorManager::DonorManager(const std::string& fileName) : fileHandler(fileName) {}

// Este es el metodo getDonorDetails que solicita y registra los detalles de un nuevo donante
// Lo hace pidendo ID, nombre, dirección, distrito, tipo de sangre y número, luego guarda los datos
void DonorManager::getDonorDetails() {
    ui.clearConsole();
    std::cout << "Ingrese los detalles del donante\n";

    Donor newDonor;
    newDonor.setDonorId(ui.getValidatedInput("Id: "));

    std::cout << "Nombre: ";
    std::string name;
    std::getline(std::cin, name);
    newDonor.setName(name);

    std::cout << "Dirección: ";
    std::string address;
    std::getline(std::cin, address);
    newDonor.setAddress(address);

    ui.displayProvinces();
    newDonor.setDistrict(ui.getValidatedInput("departamento (ingrese el número correspondiente): "));

    ui.displayBloodTypes();
    std::string bloodType = Utils::getValidatedBloodType("Tipo de sangre: ");
    newDonor.setBloodType(bloodType, false);

    std::cout << "Número: ";
    std::string number;     //DESDE ESTA SECCION ESTARA IMPLEMENTADO EL AJUSTE PARA VALIDAR EL NUMERO CON UNA API 
    std::getline(std::cin, number);
    GetApi validar;
    do
    {
        if(validar.apiverificarNumero(number)=="false"){
            std::cout<<"Digita un numero de telefono valido"<<std::endl; //aqui el control de errores por numero no valido
            std::getline(std::cin,number);
        }
    } while (validar.apiverificarNumero(number)=="false");
    newDonor.setNumber(number,true);
    donors.push_back(newDonor);
    fileHandler.writeDataToFile(newDonor);
}

// Método searchAndDisplay, busca y muestra donantes según criterios (departamento, dirección y tipo de sangre), luego filtra donantes y muestra los que coinciden con los criterios
void DonorManager::searchAndDisplay() const {
    ui.clearConsole();
    ui.displayProvinces();
    int provinceName = ui.getValidatedInput("Ingrese el número de la departamento: ");

    std::cout << "Ingrese la dirección (dejar en blanco para omitir): ";
    std::string addressFilter;
    std::getline(std::cin, addressFilter);

    ui.displayBloodTypes();
    std::cout << "Ingrese el tipo de sangre (dejar en blanco para omitir): ";
    std::string bloodTypeFilter;
    std::getline(std::cin, bloodTypeFilter);

    std::vector<Donor> foundDonors = fileHandler.searchAndDisplay(provinceName, addressFilter, bloodTypeFilter);

    if (foundDonors.empty()) {
        std::cout << "No se encontraron donantes con los criterios especificados.\n";
    } else {
        for (const auto& donor : foundDonors) {
            std::cout << "Nombre: " << donor.getName() << "\n";
            std::cout << "Dirección: " << donor.getAddress() << "\n";
            std::cout << "Departamento: " << donor.getDistrict() << "\n";
            std::cout << "Tipo de sangre: " << donor.getBloodType() << "\n";
            std::cout << "Número: " << donor.getNumber() << "\n\n";
        }
    }

    ui.waitForKeyPress();
}

// Método deleteDonor que elimina un donante por nombre. Es decir, busca y elimina al donante del archivo de datos
void DonorManager::deleteDonor(const std::string& donorName) {
    fileHandler.deleteDonor(donorName);
}

// Método displayAllDonors que muestra todos los donantes registrados. Este lee y muestra la lista completa de donantes desde el archivo de datos
void DonorManager::displayAllDonors() const {
    fileHandler.displayAllDonors();
    ui.waitForKeyPress();
}

//Este método recorre la lista de donantes para la clase de las estadísticas
std::vector<Donor> DonorManager::getAllDonors() const {
    std::ifstream inFile(fileName);
    std::vector<Donor> donors;
    std::string line;

    while (std::getline(inFile, line)) {
        donors.push_back(Donor::parseLine(line));
    }

    return donors;
}
