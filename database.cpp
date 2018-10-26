#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "database.h"
#include "datatemplate.h"
#include "data.h"
#include "m_utilities.h"

std::string Database::getDatabaseName() {
    return databaseName_;
}

void Database::setDatabaseName(std::string name) {
    databaseName_ = name;
}

DataTemplate Database::getTemplate() {
    return template_;
}

void Database::setTemplate(DataTemplate dt) {
    template_ = dt;
}

std::vector<Data> Database::getEntries() {
    return entries_;
}

void Database::loadFileEntries() {
    std::ifstream myFile;
    myFile.open(databaseName_ + ".txt");

    entries_.clear(); // Nos aseguramos de que no queden entradas de otras bases de datos

    while (myFile.peek() != EOF) {
        Data data;
        std::string linea;

        data.setTemplate(template_);

        std::getline(myFile, linea);
        decrypt(linea, data);

        entries_.push_back(data);
    }

    myFile.close();
}

// Obtiene los diferentes campos contenidos en la linea de informacion
// y los guarda en el objeto Data
void Database::decrypt(std::string line, Data& data) {
    int infoBegin = 0;
    int infoLen = 0;
    // El método substr toma como primer parámetro la posición del string
    // a partir del cual empezara el trozo de string que deseemos, y como
    // segundo parámetro la cantidad de carácteres a coger
    for (int i = 0; i < data.getTemplate().getNumFields(); i++) {
        // Actualizamos la posición del carácter inicial del substring que buscamos
        infoBegin += infoLen;
        infoLen = data.getTemplate().getField(i).second;
        data.addInformation(line.substr(infoBegin, infoLen));
    }
}

// Añade la entrada en el vector del objeto Database y también lo introduce al final
// del archivo correspondiente
void Database::addEntry(Data data) {
    entries_.push_back(data);

    std::string info = encrypt(data);

    std::ofstream myFile;
    myFile.open(databaseName_ + ".txt", std::ios::app);
    myFile << info << std::endl;

    myFile.close();
}

// Junta toda la información del objeto Data en una sola línea para introducirlo
// en el archivo de la base de datos
std::string Database::encrypt(Data& data) {
    std::string info = "";

    for (int i = 0; i < data.getTemplate().getNumFields(); i++) {
        info += data.getInformation(i);
    }

    return info;
}

// Recorre todas las entradas y devuelve aquellas cuya información contenga (no tiene
// que ser idéntico) la palabra que se busca.
std::vector<Data> Database::searchEntries(int fieldIdx, std::string word) {
    std::vector<Data> data;

    for (unsigned int i = 0; i < entries_.size(); i++) {
        if (entries_[i].getInformation(fieldIdx).find(word) != std::string::npos) {
            data.push_back(entries_[i]);
        }
    }

    return data;
}
