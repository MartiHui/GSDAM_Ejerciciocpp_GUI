#ifndef INTERFACE_H
#define INTERFACE_H
#include <vector>
#include <string>

#include "controller.h"
#include "database.h"
#include "datatemplate.h"
#include "data.h"

// La parte gráfica del programa
class Interface {
private:
    int getOption(std::string msg, int minLimit, int maxLimit);
    int getOption(std::string msg);
    bool isNewName(std::string name);

    int selectDatabase();

    void createNewDatabase();
    std::string getDatabaseName();
    DataTemplate getDatabaseTemplate(); // Crea una plantilla para una base de datos nueva

    void databaseMenu();

    void printDatabaseEntries(std::vector<Data> entries, DataTemplate dataTemplate);
    Data getNewDataEntry();
    void searchInEntries();

public:
    Controller* controller_;

    Interface();
    ~Interface();
    void mainMenu();int databaseMenu(std::string databaseName);
};
#endif // INTERFACE_H
