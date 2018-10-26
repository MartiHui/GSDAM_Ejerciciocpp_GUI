#include <string>
#include <utility>

#include "datatemplate.h"

void DataTemplate::setNumFields(int num) {
    numFields_ = num;
}

int DataTemplate::getNumFields() {
    return numFields_;
}

void DataTemplate::addField(std::string name, int len) {
    fields_.emplace_back(name, len);
}

std::pair<std::string, int> DataTemplate::getField(int idx) {
    return fields_[idx];
}
