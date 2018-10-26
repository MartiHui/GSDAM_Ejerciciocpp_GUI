#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <algorithm>

#include "interface.h"
#include "controller.h"
#include "database.h"
#include "m_utilities.h"

Interface::Interface() {
    controller_ = new Controller;
}

Interface::~Interface() {
    delete controller_;
}

int Interface::getOption(std::string msg, int minLimit, int maxLimit) {
    std::string input = "";
    int option = 0;

    while (true) {
        std::cout << msg << std::endl;
        std::getline(std::cin, input);

        std::stringstream myStream(input);
        if (myStream >> option && option >= minLimit && option <= maxLimit) {
            break;
        }
        std::cout << "No has elegido una opcion valida." << std::endl;
    }

    return option;
}

int Interface::getOption(std::string msg) {
    std::string input = "";
    int option = 0;

    while (true) {
        std::cout << msg << std::endl;
        std::getline(std::cin, input);

        std::stringstream myStream(input);
        if (myStream >> option) {
            break;
        }
        std::cout << "No has elegido una opcion valida." << std::endl;
    }

    return option;
}

void Interface::mainMenu() {
    unsigned int option;
    bool salir = false;

    do {
        option = selectDatabase();

        if (option == 0) {
            salir = true;
        } else if (option == controller_->databases_.size()+1) {
            createNewDatabase();
        } else {
            controller_->currentDatabase_ = &controller_->databases_[option-1];
            databaseMenu();
        }
    } while (!salir);
}

int Interface::selectDatabase() {
    int dbSize = controller_->databases_.size();

    std::cout << "Gestor de bases de datos" << std::endl
            << "------------------------" << std::endl;

    int idx;
    for (idx = 0; idx < dbSize; idx++) {
        std::cout << to_string(idx+1) << " - " << controller_->databases_[idx].getDatabaseName() << std::endl;
    }
    std::cout << to_string(idx+1) << " - " << "Crear nueva base de datos." << std::endl << std::endl;
    std::cout << "0 - Salir." << std::endl;

    std::string mensaje = "Elige una opcion (0-" + to_string(dbSize+1) + "):";

    return getOption(mensaje, 0, dbSize+1);
}

void Interface::createNewDatabase() {
    std::string name = getDatabaseName();
    DataTemplate dt = getDatabaseTemplate();

    controller_->createDatabase(name, dt);
}

std::string Interface::getDatabaseName() {
    std::string name;
    bool newName = false;

    do { // Evitamos dos bases de datos con el mismo nombre para evitar problemas a la hora de crear los archivos
        std::cout << "Introduce el nombre de la nueva base de datos: " << std::endl;
        std::getline(std::cin, name);
        if (isNewName(name)) {
            newName = true;
        } else {
            std::cout << "Ya existe una base de datos con este nombre. Prueba otra vez" << std::endl;
        }
    } while (!newName);

    return name;
}

bool Interface::isNewName(std::string name) {
    bool isNew = true;

    // Pasamos ambos string a comparar a minusculas para compararlos correctamente
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);
    for (unsigned int i = 0; i < controller_->databases_.size(); i++) {
        std::string dbName = controller_->databases_[i].getDatabaseName();
        std::transform(dbName.begin(), dbName.end(), dbName.begin(), ::tolower);
        if (name == dbName) {
            isNew = false;
            break;
        }
    }

    return isNew;
}

DataTemplate Interface::getDatabaseTemplate() {
    DataTemplate ds;

    ds.setNumFields(getOption("Introduce el numero de campos:"));

    std::string name;
    int len;
    for (int i = 0; i < ds.getNumFields(); i++) {
        std::cout << "Nombre del " << to_string(i+1) << "º campo:" << std::endl;
        std::getline(std::cin, name);

        len = getOption("Introduce la longitud del campo:");

        ds.addField(name, len);
    }

    return ds;
}

void Interface::databaseMenu() {
    bool exit = false;
    controller_->currentDatabase_->loadFileEntries();

    do {
        std::cout << "~~~~~~~~~~~~ " << controller_->currentDatabase_->getDatabaseName() << " ~~~~~~~~~~~~" << std::endl
            << "1 - Ver entradas" << std::endl
            << "2 - Añadir entrada" << std::endl
            << "3 - Buscar entrada" << std::endl << std::endl
            << "0 - Salir" << std::endl;

         int option = 0;
         option = getOption("Elige una opcion:", 0, 3);

         switch (option) {
            case 0: // Salir al menú de seleccion de base de datos
                exit = true;
                break;

            case 1: // Mostrar todas las entradas de la base de datos
                printDatabaseEntries(controller_->currentDatabase_->getEntries(), controller_->currentDatabase_->getTemplate());
                break;

            case 2: // Añadir una entrada a la base de datos
                { // Limitamos el ámbito del objeto Data, de lo contrario no compila
                Data data = getNewDataEntry();
                controller_->currentDatabase_->addEntry(data);
                break;
                }

            case 3: // Buscar una palabra entre la información de las entradas
                searchInEntries();
                break;
        }
    } while (!exit);
}

void Interface::printDatabaseEntries(std::vector<Data> entries, DataTemplate dataTemplate) {
    int numEntries = entries.size();

    std::cout << "Numero de entradas: " << to_string(numEntries) << std::endl;
    for (int x = 0; x < numEntries; x++) {
        std::cout << to_string(x+1) << ".";
        for (int y = 0; y < dataTemplate.getNumFields(); y++) {
            std::cout << "\t" << dataTemplate.getField(y).first
                << ": " << entries[x].getInformation(y) << std::endl;
        }
    }

    std::cout << std::endl << "Presiona cualquier tecla para salir..." << std::endl;
    std::getchar();
}

Data Interface::getNewDataEntry() {
    Data data;
    DataTemplate ds = controller_->currentDatabase_->getTemplate();
    data.setTemplate(ds);
    std::string line;

    std::cout << "Creando una nueva entrada en la base de datos" << std::endl;
    for (int i = 0; i < ds.getNumFields(); i++) {
        std::cout << ds.getField(i).first << ": (Maximo " << ds.getField(i).second
            << " caracteres.)" << std::endl;

        std::getline(std::cin, line);
        // Nos aseguramos de que la información tenga el número de caracteres correcto.
        line.resize(ds.getField(i).second, '\0');

        data.addInformation(line);
    }

    std::cout << "Nueva entrada creada." << std::endl
        << "Presiona cualquier tecla para salir..." << std::endl;
    std::getchar();

    return data;
}

void Interface::searchInEntries() {
    std::cout << "Buscar entrada: " << std::endl
        << "Elige que campo usar para la busqueda: " << std::endl;

    DataTemplate ds = controller_->currentDatabase_->getTemplate();
    int fieldIdx = 0;

    for (int i = 0; i < ds.getNumFields(); i++) {
        std::cout << to_string(i+1) << " - " << ds.getField(i).first << std::endl;
    }
    fieldIdx = getOption("", 1, ds.getNumFields()) - 1;

    std::string word;
    std::cout << "Introduce el termino a buscar: " << std::endl;
    std::getline(std::cin, word);

    printDatabaseEntries(controller_->currentDatabase_->searchEntries(fieldIdx, word), ds);
}

