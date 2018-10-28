#ifndef M_UTILITIES
#define M_UTILITIES
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include "database.h"

template<class T>
std::string to_string(T t) {
    std::stringstream ss;
    ss << t;
    return ss.str();
}

bool isNewName(std::vector<Database> &databases, std::string name);
#endif // M_UTILITIES
