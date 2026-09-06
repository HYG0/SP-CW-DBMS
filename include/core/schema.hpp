#pragma once
#include "value.hpp"
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

enum class ColumnType : std::uint8_t {
    INT,
    STRING
};

enum ConstraintFlags : std::uint8_t {
    NONE,
    NOT_NULL,
    INDEXED
};

struct Column {
    std::string name;
    ColumnType type;
    std::uint8_t constraints = NONE;
    std::optional<Value> default_value;

    [[nodiscard]] bool is_not_null() const noexcept;
    [[nodiscard]] bool is_indexed() const noexcept;
};

using Schema = std::vector<Column>;

int find(const Schema &schema, const std::string &name);