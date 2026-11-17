#pragma once
#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>

// A reusable STL-backed template used to store different domain object types.
template <typename T>
class Repository {
public:
    template <typename Key, typename Getter>
    bool contains(const Key& key, Getter getter) const {
        return std::any_of(items_.begin(), items_.end(), [&](const T& item) { return getter(item) == key; });
    }
    template <typename Key, typename Getter>
    T* find(const Key& key, Getter getter) {
        auto it = std::find_if(items_.begin(), items_.end(), [&](const T& item) { return getter(item) == key; });
        return it == items_.end() ? nullptr : &*it;
    }
    template <typename Key, typename Getter>
    const T* find(const Key& key, Getter getter) const {
        auto it = std::find_if(items_.begin(), items_.end(), [&](const T& item) { return getter(item) == key; });
        return it == items_.end() ? nullptr : &*it;
    }
    template <typename Key, typename Getter>
    void add(T item, const Key& key, Getter getter) {
        if (contains(key, getter)) throw std::invalid_argument("An item with that identifier already exists.");
        items_.push_back(std::move(item));
    }
    template <typename Key, typename Getter>
    bool erase(const Key& key, Getter getter) {
        auto it = std::find_if(items_.begin(), items_.end(), [&](const T& item) { return getter(item) == key; });
        if (it == items_.end()) return false;
        items_.erase(it);
        return true;
    }
    const std::vector<T>& all() const noexcept { return items_; }
    std::vector<T>& all() noexcept { return items_; }
private:
    std::vector<T> items_;
};
