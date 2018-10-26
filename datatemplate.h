#ifndef DATATEMPLATE_H
#define DATATEMPLATE_H
#include <string>
#include <utility>
#include <vector>

// Plantilla para saber la estructura que tienen las entradas
// de la base de datos correspondiente.
class DataTemplate {
private:
    int numFields_;
    std::vector<std::pair<std::string, int> > fields_;

public:
    void setNumFields(int num);
    int getNumFields();
    void addField(std::string name, int len);
    std::pair<std::string, int> getField(int idx);
};
#endif // DATATEMPLATE_H
