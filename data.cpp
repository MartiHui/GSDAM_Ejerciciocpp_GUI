#include <string>
#include <vector>

#include "data.h"

DataTemplate Data::getTemplate() {
    return template_;
}

void Data::setTemplate(DataTemplate dataTemplate) {
    template_ = dataTemplate;
}

std::string Data::getInformation(int idx) {
    return information_[idx];
}

void Data::addInformation(std::string info) {
    information_.push_back(info);
}
