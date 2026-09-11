#pragma once
#include "table.hpp"
#include "tree/b_plus_tree.hpp"
#include <filesystem>
#include <memory>
#include <string>
#include <vector>

class Database {
    friend class StorageManager;
public:
    explicit Database(std::string name);

    Database(std::string name, std::filesystem::path index_path);

    [[nodiscard]] const std::string &name() const noexcept;

    void create_table(const std::string &table_name, Schema schema);

    void drop_table(const std::string &table_name);

    Table &get_table(const std::string &table_name);

    [[nodiscard]] const Table &get_table(const std::string &table_name) const;

    [[nodiscard]] bool has_table(const std::string &table_name) const noexcept;

private:
    static std::filesystem::path default_index_path(const std::string &name);

    std::string name_;
    std::filesystem::path index_path_;
    std::filesystem::path table_indexes_dir_;

    BPlus_tree<std::string, std::size_t> tables_;
    std::vector<std::unique_ptr<Table> > table_storage_;
};
