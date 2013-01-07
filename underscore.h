#ifndef UNDERSCORE_H
#define UNDERSCORE_H

#include <algorithm>

namespace _ {

namespace util {

template<typename T>
class HasPushBack {
private:
    template<typename U>
    static auto check(U* p) -> decltype(p->push_back(std::declval<typename U::value_type>()), int());

    template<typename>
    static void check(...);
public:
    static const bool value = !std::is_void<decltype(check<T>(nullptr))>::value;
};

template<typename T>
class HasInsert {
private:
    template<typename U>
    static auto check(U* p) -> decltype(p->insert(std::declval<typename U::value_type>()), int());

    template<typename>
    static void check(...);
public:
    static const bool value = !std::is_void<decltype(check<T>(nullptr))>::value;
};

template<typename T>
class HasInsertAfter {
private:
    template<typename U>
    static auto check(U* p) -> decltype(p->insert_after(p->begin(), std::declval<typename U::value_type>()), int()); // begin is just for checking

    template<typename>
    static void check(...);
public:
    static const bool value = !std::is_void<decltype(check<T>(nullptr))>::value;
};

template<typename T, typename U>
typename std::enable_if<HasPushBack<T>::value, void>::type
add(T& c, U&& v) {
    c.push_back(std::forward<U>(v));
}

template<typename T, typename U>
typename std::enable_if<HasInsert<T>::value, void>::type
add(T& c, U&& v) {
    c.insert(std::forward<U>(v));
}

template<typename T, typename U>
typename std::enable_if<HasInsertAfter<T>::value, void>::type
add(T& c, U&& v) {
    // get to the end of the list, which is O(N) and not fast at all
    auto before_end = c.before_begin();
    for (auto& _ : c) {
        ++before_end;
    }
    c.insert_after(before_end, std::forward<U>(v));
}

} // namespace util


template<typename Collection, typename Function> void
each(Collection& obj, Function iterator) {
    for (auto& i : obj) {
        iterator(i);
    }
}


template<template<class ...T>
         class RetCollection = std::vector,
         typename Collection,
         typename Function> 
auto
map(const Collection& obj, Function iterator)
    -> RetCollection<typename std::decay<decltype(iterator(std::declval<typename Collection::value_type>()))>::type> {

    using R = typename std::decay<decltype(iterator(std::declval<typename Collection::value_type>()))>::type;
    RetCollection<R> result;
    for (auto& i : obj) {
        util::add(result, iterator(i));
    }
    return result;
}
 
template<template<class ...T>
         class RetCollection = std::vector,
         typename T,
         size_t N,
         typename Function> 
auto
map(T (&obj)[N], Function iterator)
    -> RetCollection<typename std::decay<decltype(iterator(std::declval<T>()))>::type> {

    using R = typename std::decay<decltype(iterator(std::declval<T>()))>::type;
    RetCollection<R> result;
    for (auto& i : obj) {
        util::add(result, iterator(i));
    }
    return result;
}


template<typename Collection, typename Function, typename Memo> 
Memo
reduce(const Collection& obj, Function iterator, Memo memo) {
    for (auto& i : obj) {
        memo = iterator(memo, i);
    }
    return memo;
}


template<typename Collection, typename Function, typename Memo>
Memo
reduceRight(const Collection& obj, Function iterator, Memo memo) {
    for (typename Collection::const_reverse_iterator it = obj.rbegin(); it != obj.rend(); ++it) {
        memo = iterator(memo, *it);
    }
    return memo;
}

template<typename T, size_t N, typename Function, typename Memo>
Memo
reduceRight(T (&obj)[N], Function iterator, Memo memo) {
    for (int i = N-1; i >= 0; --i) {
        memo = iterator(memo, obj[i]);
    }
    return memo;
}


template<typename Collection, typename Function>
auto
find(Collection& obj, Function iterator)
    -> decltype(std::begin(obj)) {
    return std::find_if(std::begin(obj), std::end(obj), iterator);
}


template<typename Collection, typename Function>
Collection
filter(const Collection& obj, Function iterator) {
    Collection result;
    for (auto& i : obj) {
        if (iterator(i)) {
            util::add(result, i);
        }
    }
    return result;
}


template<typename Collection, typename Function>
Collection
reject(const Collection& obj, Function iterator) {
    Collection result;
    for (auto& i : obj) {
        if (!iterator(i)) {
            util::add(result, i);
        }
    }
    return result;
}


template<typename Collection, typename Function>
bool
every(const Collection& obj, Function iterator) {
    return std::all_of(std::begin(obj), std::end(obj), iterator);
}


template<typename Collection, typename Function>
bool
some(const Collection& obj, Function iterator) {
    return std::any_of(std::begin(obj), std::end(obj), iterator);
}


template<typename Collection> 
bool
contains(const Collection& obj, const typename Collection::value_type& value) {
    return std::find(std::begin(obj), std::end(obj), value) != std::end(obj);
}

template<typename T, size_t N> 
bool
contains(T (&obj)[N], const T& value) {
    return std::find(std::begin(obj), std::end(obj), value) != std::end(obj);
}


template<typename Collection, typename Function, typename ...Argument> 
auto
invoke(Collection& obj, Function method, Argument... args)
    -> typename std::enable_if<std::is_void<decltype((std::declval<typename Collection::value_type>().*method)(args...))>::value, void>::type {

    for (auto& i : obj) {
        (i.*method)(args...);
    }
}

template<template<class ...T>
         class RetCollection = std::vector,
         typename Collection,
         typename Function,
         typename ...Argument> 
auto
invoke(Collection& obj, Function method, Argument... args)
    -> typename std::enable_if<!std::is_void<decltype((std::declval<typename Collection::value_type>().*method)())>::value, 
       RetCollection<typename std::decay<decltype((std::declval<typename Collection::value_type>().*method)())>::type>>::type {

    using R = typename std::decay<decltype((std::declval<typename Collection::value_type>().*method)())>::type;
    RetCollection<R> result;
    for (auto&i : obj) {
        util::add(result, (i.*method)(args...));
    }
    return result;
}

} // namespace _

#endif // UNDERSCORE_H

