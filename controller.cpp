#include <iostream>
#include <fstream>

#include "database.h"
#include "datatemplate.h"
#include "data.h"
#include "controller.h"
#include "m_utilities.h"

Controller::Controller() {
    getDatabases();
}

Controller::~Controller() {
    if (currentDatabase_) {
        delete currentDatabase_;
    }
}

// Recupero las estructuras de todas las bases de datos guardadas (nombre y plantilla de las entradas)
void Controller::getDatabases() {
    std::ifstream myFile;
    myFile.open(filename_);

    Database db;
    DataTemplate ds;
    while (myFile.peek() != EOF) {
        std::string line;

        // Obtener nombre de la base de datos
        std::getline(myFile, line);
        db.setDatabaseName(line);

        // Obtener número de campos de la estructura
        std::getline(myFile, line);
        ds.setNumFields(std::stoi(line));

        // Obtener el nombre de los campos y su longitud
        for (int i = 0; i < ds.getNumFields(); i++) {
            std::string fieldName;
            std::string fieldLen;

            std::getline(myFile, fieldName);
            std::getline(myFile, fieldLen);
            ds.addField(fieldName, std::stoi(fieldLen));
        }

        db.setTemplate(ds);
        databases_.push_back(db);
    }

    myFile.close();
}

void Controller::saveDatabase(Database& db) {
    std::ofstream myFile;
    myFile.open(filename_, std::ios_base::app);

    myFile << db.getDatabaseName() << std::endl;

    DataTemplate ds = db.getTemplate();
    myFile << ds.getNumFields() << std::endl;
    for (int i = 0; i < ds.getNumFields(); i++) {
        // En una fila guardo el nombre del campo y en la siguiente la longitud
        myFile << ds.getField(i).first << std::endl
            << to_string(ds.getField(i).second) << std::endl;
    }

    myFile.close();
}

void Controller::createDatabase(std::string databaseName, DataTemplate dataTemplate) {
    Database db;

    db.setDatabaseName(databaseName);
    db.setTemplate(dataTemplate);

    saveDatabase(db);
    databases_.push_back(db);
}
