#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <functional>

namespace io {
#define DEFAULT_ISTREAM std::istream& stream = std::cin

template<typename T>
T Read(DEFAULT_ISTREAM) {
    T t;
    stream >> t;
    return t;
}

template<typename T>
void Write(const T& t, std::ostream& stream = std::cout) {
    stream << t;
}

template<typename T>
std::vector<T> ReadVector(int n,
        std::function<T(std::istream&)> f = Read<T>,
        DEFAULT_ISTREAM){
    std::vector<T> v;
    v.reserve(n);
    std::generate(v.begin(), v.end(), std::bind(f, std::ref(stream)));
    return v;
}

}  // namespace io
