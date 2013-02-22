#ifndef UNDERSCORE_H
#define UNDERSCORE_H

#include <algorithm>
#include <numeric>
#include <random>
#include <map>

namespace _ {

namespace util {

template<typename T>
class HasSize {
private:
    template<typename U>
    static auto check(U* p) -> decltype(p->size(), int());

    template<typename>
    static void check(...);
public:
    static const bool value = !std::is_void<decltype(check<T>(nullptr))>::value;
};

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


template<typename Collection, typename Function>
void
each(Collection&& obj, Function iterator) {
    std::for_each(std::begin(obj), std::end(obj), iterator);
}


template<template<typename ...T>
         class RetCollection = std::vector,
         typename Collection,
         typename Function>
auto
map(const Collection& obj, Function iterator)
    -> RetCollection<typename std::decay<decltype(iterator(*std::begin(obj)))>::type> {

    using R = typename std::decay<decltype(iterator(*std::begin(obj)))>::type;
    RetCollection<R> result;
    for (auto& i : obj) {
        util::add(result, iterator(i));
    }
    return result;
}


template<typename Collection, typename Function, typename Memo>
Memo
reduce(const Collection& obj, Function iterator, Memo memo) {
    return std::accumulate(std::begin(obj), std::end(obj), memo, iterator);
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
find(Collection&& obj, Function iterator)
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


template<typename Collection, typename U>
bool
contains(const Collection& obj, const U& value) {
    return std::find(std::begin(obj), std::end(obj), value) != std::end(obj);
}


template<typename Collection, typename Function, typename... Argument>
auto
invoke(Collection&& obj, Function method, Argument&&... args)
    -> typename std::enable_if<std::is_void<decltype(((*std::begin(obj)).*method)(args...))>::value, void>::type {

    for (auto& i : obj) {
        (i.*method)(std::forward<Argument>(args)...);
    }
}

template<template<typename ...T>
         class RetCollection = std::vector,
         typename Collection,
         typename Function,
         typename... Argument>
auto
invoke(Collection&& obj, Function method, Argument&&... args)
    -> typename std::enable_if<!std::is_void<decltype(((*std::begin(obj)).*method)(args...))>::value,
       RetCollection<typename std::decay<decltype(((*std::begin(obj)).*method)(args...))>::type>>::type {

    using R = typename std::decay<decltype(((*std::begin(obj)).*method)(args...))>::type;
    RetCollection<R> result;
    for (auto& i : obj) {
        util::add(result, (i.*method)(std::forward<Argument>(args)...));
    }
    return result;
}


template<template<typename ...T>
         class RetCollection = std::vector,
         typename Collection,
         typename Function>
auto
pluck(const Collection& obj, Function member)
    -> RetCollection<typename std::decay<decltype((*std::begin(obj)).*member)>::type> {

    using R = typename std::decay<decltype((*std::begin(obj)).*member)>::type;
    RetCollection<R> result;
    for (auto& i : obj) {
        util::add(result, i.*member);
    }
    return result;
}


template<typename Collection>
auto
max(Collection&& obj) 
    -> decltype(std::begin(obj)) {
    return std::max_element(std::begin(obj), std::end(obj));
}

template<typename Collection, typename Function>
auto
max(Collection&& obj, Function iterator)
    -> decltype(std::begin(obj)) {

    using R = typename std::decay<decltype(*std::begin(obj))>::type;
    return std::max_element(std::begin(obj), std::end(obj), [&](const R& a, const R& b) {
            return iterator(a) < iterator(b);
    });
}


template<typename Collection>
auto
min(Collection&& obj) 
    -> decltype(std::begin(obj)) {
    return std::min_element(std::begin(obj), std::end(obj));
}

template<typename Collection, typename Function>
auto
min(Collection&& obj, Function iterator)
    -> decltype(std::begin(obj)) {

    using R = typename std::decay<decltype(*std::begin(obj))>::type;
    return std::min_element(std::begin(obj), std::end(obj), [&](const R& a, const R& b) {
        return iterator(a) < iterator(b);
    });
}


template<typename Collection, typename Function>
Collection
sortBy(const Collection& obj, Function iterator) {
    Collection result = obj;
    using R = typename Collection::value_type;
    std::sort(std::begin(result), std::end(result), [&](const R& a, const R& b) {
        return iterator(a) < iterator(b);
    });
    return result;
}


template<typename Collection, typename Function>
auto
groupBy(const Collection& obj, Function iterator) 
    -> std::multimap<typename std::decay<decltype(iterator(*std::begin(obj)))>::type, 
                     typename std::decay<decltype(*std::begin(obj))>::type> {

    using R = std::multimap<typename std::decay<decltype(iterator(*std::begin(obj)))>::type, 
                            typename std::decay<decltype(*std::begin(obj))>::type>;
    R result;
    for (auto& i : obj) {
        result.insert(typename R::value_type(iterator(i), i)); 
    }
    return result;
}


template<typename Collection, typename Function>
auto
countBy(const Collection& obj, Function iterator) 
    -> std::map<typename std::decay<decltype(iterator(*std::begin(obj)))>::type, std::size_t> {

    using R = std::map<typename std::decay<decltype(iterator(*std::begin(obj)))>::type, std::size_t>;
    R result;
    for (auto& i : obj) {
        auto&& v = iterator(i);
        typename R::iterator it = result.find(v);
        if (it == result.end()) {
            result.insert(typename R::value_type(std::forward<decltype(v)>(v), 1)); 
        } else {
            ++it->second;
        }
    }
    return result;
}


template<typename Collection>
Collection
shuffle(const Collection& obj) {
    Collection result = obj;
    std::random_device rd;
    std::shuffle(std::begin(result), std::end(result), std::mt19937(rd()));
    return result;
}


template<template<typename ...T>
         class RetCollection = std::vector,
         typename Collection>
auto
toArray(const Collection& obj)
    -> RetCollection<typename std::decay<decltype(*std::begin(obj))>::type> {
        return RetCollection<typename std::decay<decltype(*std::begin(obj))>::type>(std::begin(obj), std::end(obj));
}


template<typename Collection>
typename std::enable_if<util::HasSize<Collection>::value, size_t>::type
size(const Collection& obj) {
    return obj.size();
}

template<typename Collection>
typename std::enable_if<!util::HasSize<Collection>::value, size_t>::type
size(const Collection& obj) {
    size_t s = 0;
    for (auto& _ : obj) {
        ++s;
    }
    return s;
}


} // namespace _

#endif // UNDERSCORE_H

