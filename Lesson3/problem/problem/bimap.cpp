#include "bimap.h"

#include <unordered_map>
#include <deque>
#include <cassert>

struct BiMap::Impl{
    Impl() = default;

    Impl(const Impl& other)
        : items_(other.items_) {
        for (auto& [k, v] : items_) {
            key_to_value_[k] = v;
            value_to_key_[v] = k;
        }
    }

    Impl& operator=(const Impl& other) = delete;

    bool Add(std::string_view key, std::string_view value) {
        if (FindValue(key) || FindKey(value)) {
            return false;
        }

        items_.push_back(Item{ std::string(key), std::string(value) });

        const auto& inserted_item = items_.back();
        std::string_view k = inserted_item.key;
        std::string_view v = inserted_item.value;

        try {
            key_to_value_.emplace(k, v);
            value_to_key_.emplace(v, k);
        }
        catch (...) {
            key_to_value_.erase(k);
            value_to_key_.erase(v);
            items_.pop_back();
            throw;
        }

        return true;
    }

    std::optional<std::string_view> FindValue(std::string_view key) const noexcept {
        if (auto it = key_to_value_.find(key); it != key_to_value_.end()) {
            return it->second;
        }
        return std::nullopt;//возможна замена на {}
    }

    std::optional<std::string_view> FindKey(std::string_view value) const noexcept {
        if (auto it = value_to_key_.find(value); it != value_to_key_.end()) {
            return it->second;
        }
        return std::nullopt;//возможна замена на {}
    }


private:
    struct Item {
        std::string key;
        std::string value;
    };

    std::deque<Item> items_;
    std::unordered_map<std::string_view, std::string_view> key_to_value_;
    std::unordered_map<std::string_view, std::string_view> value_to_key_;
};

BiMap::BiMap()
    : impl_(std::make_unique<Impl>()) {
}

BiMap::~BiMap() = default;

BiMap::BiMap(BiMap&& other) noexcept : impl_(std::move(other.impl_)) {
}

BiMap& BiMap::operator=(BiMap&& other) noexcept {
    if (this != &other) {
        impl_ = std::move(other.impl_);
    }
    return *this;
}

BiMap::BiMap(const BiMap& other)
    :impl_(other.impl_ ? std::make_unique<Impl>(*other.impl_) : nullptr){}

BiMap& BiMap::operator=(const BiMap& other) {
    if (this != std::addressof(other)) {
        impl_ = other.impl_ ? std::make_unique<Impl>(*other.impl_) : nullptr;
    }
    return *this;
}

bool BiMap::Add(std::string_view key, std::string_view value) {
    return impl_->Add(key,value);
}

std::optional<std::string_view> BiMap::FindValue(std::string_view key) const noexcept {
    return impl_->FindValue(key);
}

std::optional<std::string_view> BiMap::FindKey(std::string_view value) const noexcept {
    return impl_->FindKey(value);
}