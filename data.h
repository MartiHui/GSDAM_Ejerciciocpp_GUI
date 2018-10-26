#ifndef DATA_H
#define DATA_H
#include <string>
#include <vector>

#include "datatemplate.h"

// Almacena una entrada de una base de datos
class Data {
private:
    DataTemplate template_;
    std::vector<std::string> information_;

public:
    DataTemplate getTemplate();
    void setTemplate(DataTemplate dataTemplate);
    std::string getInformation(int idx);
    void addInformation(std::string info);
};
#endif // DATA_H
