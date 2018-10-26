#ifndef DATABASE_H
#define DATABASE_H
#include <vector>
#include <string>

#include "datatemplate.h"
#include "data.h"

// Almacena la información de una base de datos: su nombre,
// la estructura que siguen sus entradas y las entradas.
class Database {
private:
    std::string databaseName_;
    DataTemplate template_;
    std::vector<Data> entries_;

    void decrypt(std::string line, Data &data);
    std::string encrypt(Data& data);

public:
    std::string getDatabaseName();
    void setDatabaseName(std::string name);
    DataTemplate getTemplate();
    void setTemplate(DataTemplate dt);
    std::vector<Data> getEntries();
    void loadFileEntries();
    void addEntry(Data data);
    std::vector<Data> searchEntries(int fieldIdx, std::string word);
};
#endif // DATABASE_H
