#ifndef UNDERSCORE_H
#define UNDERSCORE_H

#include <algorithm>

namespace _ {

namespace util {

// simply check if has mapped_type
template<typename T>
class IsMappedContainer {
private:
    template<typename U>
    static typename U::mapped_type check(int);

    template<typename>
    static void check(...);
public:
    static const bool value = !std::is_void<decltype(check<T>(0))>::value;
};

template<typename T>
class HasPushBack {
private:
    template<typename U>
    static auto check(U* p) -> decltype(p->push_back(typename U::value_type()), int());

    template<typename>
    static void check(...);
public:
    static const bool value = !std::is_void<decltype(check<T>(nullptr))>::value;
};

template<typename T>
class HasInsert {
private:
    template<typename U>
    static auto check(U* p) -> decltype(p->insert(typename U::value_type()), int());

    template<typename>
    static void check(...);
public:
    static const bool value = !std::is_void<decltype(check<T>(nullptr))>::value;
};

template<typename T>
typename std::enable_if<HasPushBack<T>::value, void>::type 
add(T& c, const typename T::value_type& v) {
    c.push_back(v);
}

template<typename T>
typename std::enable_if<HasInsert<T>::value, void>::type 
add(T& c, const typename T::value_type& v) {
    c.insert(v);
}

} // namespace util


template<typename Collection, typename Function,
         typename std::enable_if<!util::IsMappedContainer<Collection>::value, int>::type = 0>
void each(Collection& obj, Function iterator) {
    std::for_each(std::begin(obj), std::end(obj), iterator);
}

template<typename Collection, typename Function,
         typename std::enable_if<util::IsMappedContainer<Collection>::value, int>::type = 0>
void each(Collection& obj, Function iterator) {
    std::for_each(std::begin(obj), std::end(obj), [&](typename Collection::value_type& v) {
        iterator(v.second, v.first);
    });
}


template<typename Collection, typename Function,
         typename std::enable_if<!util::IsMappedContainer<Collection>::value, int>::type = 0>
bool all(const Collection& obj, Function iterator) {
    return std::all_of(std::begin(obj), std::end(obj), iterator);
}

template<typename Collection, typename Function,
         typename std::enable_if<util::IsMappedContainer<Collection>::value, int>::type = 0>
bool all(const Collection& obj, Function iterator) {
    return std::all_of(std::begin(obj), std::end(obj), [&](const typename Collection::value_type& v) {
        return iterator(v.second, v.first);
    });
}


template<typename Collection, typename Function,
         typename std::enable_if<!util::IsMappedContainer<Collection>::value, int>::type = 0>
bool any(const Collection& obj, Function iterator) {
    return std::any_of(std::begin(obj), std::end(obj), iterator);
}

template<typename Collection, typename Function,
         typename std::enable_if<util::IsMappedContainer<Collection>::value, int>::type = 0>
bool any(const Collection& obj, Function iterator) {
    return std::any_of(std::begin(obj), std::end(obj), [&](const typename Collection::value_type& v) {
        return iterator(v.second, v.first);
    });
}

template<typename Collection, typename Function,
         typename std::enable_if<!util::IsMappedContainer<Collection>::value, int>::type = 0>
Collection filter(const Collection& obj, Function iterator) {
    Collection result;
    std::for_each(std::begin(obj), std::end(obj), [&](const typename Collection::value_type& v) {
        if (iterator(v)) {
        util::add(result, v);
        }
    });
    return result;
}

template<typename Collection, typename Function,
         typename std::enable_if<util::IsMappedContainer<Collection>::value, int>::type = 0>
Collection filter(const Collection& obj, Function iterator) {
    Collection result;
    std::for_each(std::begin(obj), std::end(obj), [&](const typename Collection::value_type& v) {
        if (iterator(v.second, v.first)) {
        util::add(result, v);
        }
    });
    return result;
}

} // namespace _

#endif // UNDERSCORE_H

