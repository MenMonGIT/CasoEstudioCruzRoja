#include "BloodStatistics.h"
#include "Donor.h"
#include <fstream>
#include <algorithm>
#include <limits>

BloodStatistics::BloodStatistics(DonorManager& manager) : donorManager(manager) {}

// Datos fijos sobre la distribución de sangre en Colombia
void BloodStatistics::statisticsPopulation() const {
    std::cout << "\nEn la población colombiana, la proporción de los distintos tipos de sangre están distribuidos de la siguiente manera:\n";
    std::cout << "O+: 61.3%\n";
    std::cout << "A+: 21.11%\n";
    std::cout << "B+: 7.28%\n";
    std::cout << "AB+: 1.47%\n";
    std::cout << "O-: 5.13%\n";
    std::cout << "A-: 2.7%\n";
    std::cout << "B-: 0.7%\n";
    std::cout << "AB-: 0.31%\n";
}

// Tipo de sangre más común en Colombia (dato fijo)
void BloodStatistics::statisticsBloodtype() const {
    std::cout << "\nEl tipo de sangre más común en Colombia es el O+\n";
}

// Determina el tipo de sangre más común en la base de datos (dinámico)
std::string BloodStatistics::databasePopulation() const {
    std::map<std::string, int> bloodTypeCount;
    std::vector<Donor> donors = donorManager.getAllDonors();

    for (const Donor& d : donors) {
        std::string bloodType = d.bloodType;
        std::transform(bloodType.begin(), bloodType.end(), bloodType.begin(), ::toupper);
        bloodTypeCount[bloodType]++;
    }

    std::string tipoPredominante;
    int maxCount = 0;
    for (const auto& pair : bloodTypeCount) {
        if (pair.second > maxCount) {
            maxCount = pair.second;
            tipoPredominante = pair.first;
        }
    }

    return tipoPredominante.empty() ? "No hay donantes registrados" : tipoPredominante;
}

// Muestra la distribución de tipos de sangre en la base de datos (dinámico)
void BloodStatistics::databaseBloodtype() const {
    std::map<std::string, int> bloodTypeCount;
    std::vector<Donor> donors = donorManager.getAllDonors();
    int totalDonors = donors.size();

    if (totalDonors == 0) {
        std::cout << "No hay donantes registrados en la base de datos.\n";
        return;
    }

    for (const Donor& d : donors) {
        std::string bloodType = d.bloodType;
        std::transform(bloodType.begin(), bloodType.end(), bloodType.begin(), ::toupper);
        bloodTypeCount[bloodType]++;
    }

    std::cout << "\nDistribución de tipos de sangre en la base de datos:\n";
    for (const auto& pair : bloodTypeCount) {
        double percentage = (static_cast<double>(pair.second) / totalDonors) * 100;
        std::cout << pair.first << ": " << percentage << "% (" << pair.second << " personas)\n";
    }
}
