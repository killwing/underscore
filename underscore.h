#ifndef UNDERSCORE_H
#define UNDERSCORE_H

#include <algorithm>

namespace _ {

// simply check if has key_type and mapped_type
template<typename T>
class isAssociativeContainer {
private:
    template<typename U>
    static typename U::key_type testKey(int);

    template<typename>
    static void testKey(...);

    template<typename U>
    static typename U::mapped_type testMapped(int);

    template<typename>
    static void testMapped(...);
public:
    enum { value = (!std::is_void<decltype(testKey<T>(0))>::value &&
                    !std::is_void<decltype(testMapped<T>(0))>::value)};
};


template<typename Collection, typename Function,
         typename std::enable_if<!isAssociativeContainer<Collection>::value, int>::type = 0>
void each(Collection& obj, Function iterator) {
    std::for_each(std::begin(obj), std::end(obj), iterator);
}

template<typename Collection, typename Function,
         typename std::enable_if<isAssociativeContainer<Collection>::value, int>::type = 0>
void each(Collection& obj, Function iterator) {
    std::for_each(std::begin(obj), std::end(obj), [&](typename Collection::value_type& v) {
        iterator(v.second, v.first);
    });
}


template<typename Collection, typename Function,
         typename std::enable_if<!isAssociativeContainer<Collection>::value, int>::type = 0>
bool all(const Collection& obj, Function iterator) {
    return std::all_of(std::begin(obj), std::end(obj), iterator);
}

template<typename Collection, typename Function,
         typename std::enable_if<isAssociativeContainer<Collection>::value, int>::type = 0>
bool all(const Collection& obj, Function iterator) {
    return std::all_of(std::begin(obj), std::end(obj), [&](const typename Collection::value_type& v) {
        return iterator(v.second, v.first);
    });
}


template<typename Collection, typename Function,
         typename std::enable_if<!isAssociativeContainer<Collection>::value, int>::type = 0>
bool any(const Collection& obj, Function iterator) {
    return std::any_of(std::begin(obj), std::end(obj), iterator);
}

template<typename Collection, typename Function,
         typename std::enable_if<isAssociativeContainer<Collection>::value, int>::type = 0>
bool any(const Collection& obj, Function iterator) {
    return std::any_of(std::begin(obj), std::end(obj), [&](const typename Collection::value_type& v) {
        return iterator(v.second, v.first);
    });
}

} // namespace _

#endif // UNDERSCORE_H

