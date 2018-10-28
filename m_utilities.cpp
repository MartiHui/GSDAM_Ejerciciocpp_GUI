#include "m_utilities.h"

bool isNewName(std::vector<Database> &databases, std::string name) {
    bool isNew = true;

    // Pasamos ambos string a comparar a minusculas para compararlos correctamente
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);
    for (unsigned int i = 0; i < databases.size(); i++) {
        std::string dbName = databases[i].getDatabaseName();
        std::transform(dbName.begin(), dbName.end(), dbName.begin(), ::tolower);
        if (name == dbName) {
            isNew = false;
            break;
        }
    }

    return isNew;
}
