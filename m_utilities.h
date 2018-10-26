#ifndef M_UTILITIES
#define M_UTILITIES
#include <string>
#include <sstream>

template<class T>
std::string to_string(T t) {
    std::stringstream ss;
    ss << t;
    return ss.str();
}
#endif // M_UTILITIES
