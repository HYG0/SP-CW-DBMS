#pragma once

#include "query/executor.hpp"

#include <string>
#include <vector>

std::vector<Statement> parse_sql(const std::string &sql);

std::string run_statements(const std::vector<Statement> &statements, const Executor &exec);

std::string run_sql(const std::string &sql, const Executor &exec);
