#pragma once
#include "ast.hpp"
#include "../core/dbms.hpp"
#include <string>
#include <unordered_map>


class Executor {
public:
    explicit Executor(DBMS &dbms);
    [[nodiscard]] std::string execute(const Statement &stmt) const;

private:
    DBMS &dbms_;
    [[nodiscard]] std::string exec_create_database(const CreateDatabaseStmt &s) const;

    [[nodiscard]] std::string exec_drop_database(const DropDatabaseStmt &s) const;

    [[nodiscard]] std::string exec_use(const UseStmt &s) const;

    [[nodiscard]] std::string exec_create_table(const CreateTableStmt &s) const;

    [[nodiscard]] std::string exec_drop_table(const DropTableStmt &s) const;

    [[nodiscard]] std::string exec_insert(const InsertStmt &s) const;

    [[nodiscard]] std::string exec_update(const UpdateStmt &s) const;

    [[nodiscard]] std::string exec_delete(const DeleteStmt &s) const;

    [[nodiscard]] std::string exec_select(const SelectStmt &s) const;

    [[nodiscard]] std::string exec_revert(const RevertStmt &s) const;

    //region helpers

    [[nodiscard]] Database &resolve_db(const std::string &db_name) const;

    [[nodiscard]] Table &resolve_table(const std::string &db_name, const std::string &table_name) const;

    static bool eval_condition(
        const Condition &cond,
        const Row &row,
        const std::unordered_map<std::string, int> &column_indexes);

    static Value eval_expr(
        const Expr &expr,
        const Row &row,
        const std::unordered_map<std::string, int> &column_indexes);

    static std::string rows_to_json(const std::vector<Row> &rows, const std::vector<std::string> &col_names);

    //endregion helpers
};
