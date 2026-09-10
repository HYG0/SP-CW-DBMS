#pragma once
#include <filesystem>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>
#include "row.hpp"
#include "schema.hpp"

struct Index;

class Table {
public:
    using TimestampMillis = std::int64_t;

    struct RowVersion {
        RowID row_id{};
        TimestampMillis timestamp_ms{};
        Row row;
        bool deleted = false;
    };

    explicit Table(Schema schema);

    Table(Schema schema, std::filesystem::path indexes_dir);

    ~Table();

    [[nodiscard]] const Schema &schema() const noexcept { return schema_; }

    [[nodiscard]] const std::vector<Row> &data() const noexcept { return data_; }

    [[nodiscard]] bool is_deleted(RowID id) const;

    [[nodiscard]] bool has_index(const std::string &column_name) const noexcept;

    [[nodiscard]] std::vector<RowID> find_indexed(const std::string &column_name, const Value &value) const;

    [[nodiscard]] std::vector<RowID> range_indexed(
        const std::string &column_name,
        const std::optional<Value> &lower,
        bool lower_inclusive,
        const std::optional<Value> &upper,
        bool upper_inclusive) const;

    RowID insert(const Row &row);

    std::vector<RowID> insert_many(const std::vector<Row> &rows);

    void update(RowID id, Row row);

    void update_many(std::vector<std::pair<RowID, Row> > updates);

    void erase(RowID id);

    std::size_t revert_to(TimestampMillis timestamp_ms);

    [[nodiscard]] const std::vector<RowVersion> &history() const noexcept { return history_; }

    void restore_history(std::vector<RowVersion> history);

private:
    friend class StorageManager;

    Schema schema_;
    std::filesystem::path indexes_dir_;
    std::vector<Row> data_;
    std::vector<bool> deleted_;
    std::vector<RowVersion> history_;

    std::unordered_map<std::string, std::unique_ptr<Index> > indexes_;

    void validate_row(const Row &row) const;

    void restore_row(Row row, bool deleted);

    void append_version(RowID id, const Row &row, bool deleted, TimestampMillis timestamp_ms);

    void rebuild_indexes();

    static TimestampMillis current_time_ms();
};
