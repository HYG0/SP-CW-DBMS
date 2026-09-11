#pragma once
#include "database.hpp"
#include "tree/b_plus_tree.hpp"
#include <filesystem>
#include <memory>
#include <string>
#include <vector>

class DBMS {
    friend class StorageManager;
public:
    DBMS();

    explicit DBMS(std::filesystem::path index_path);

    void create_database(const std::string &db_name);

    void drop_database(const std::string &db_name);

    Database &get_database(const std::string &db_name);

    [[nodiscard]] const Database &get_database(const std::string &db_name) const;

    [[nodiscard]] bool has_database(const std::string &db_name) const;

    void use(const std::string &db_name);

    Database *current_database() noexcept;

    [[nodiscard]] const Database *current_database() const noexcept;

private:
    static std::filesystem::path default_index_path();

    std::filesystem::path index_path_;
    std::filesystem::path database_indexes_dir_;
    BPlus_tree<std::string, std::size_t> databases_;
    std::vector<std::unique_ptr<Database> > database_storage_;

    Database *current_db_ = nullptr;
};
