#pragma once

#include <string>
#include <vector>
#include <map>
#include <sstream>

class SqlSelectQueryBuilder
{
private:
    std::vector<std::string> columns;
    std::string table;
    std::vector<std::pair<std::string, std::string>> conditions;

public:

    SqlSelectQueryBuilder& AddColumn(
        const std::string& column)
    {
        columns.push_back(column);
        return *this;
    }

    SqlSelectQueryBuilder& AddColumns(
        const std::vector<std::string>& columns) noexcept
    {
        for (const auto& column : columns)
        {
            this->columns.push_back(column);
        }

        return *this;
    }

    SqlSelectQueryBuilder& AddFrom(
        const std::string& from)
    {
        table = from;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(
        const std::string& column,
        const std::string& value)
    {
        conditions.emplace_back(column, value);
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(
        const std::map<std::string, std::string>& kv) noexcept
    {
        for (const auto& [column, value] : kv)
        {
            conditions.emplace_back(column, value);
        }

        return *this;
    }

    std::string BuildQuery() const
    {
        std::ostringstream query;

        query << "SELECT ";

        if (columns.empty())
        {
            query << "*";
        }
        else
        {
            for (size_t i = 0; i < columns.size(); ++i)
            {
                if (i > 0)
                {
                    query << ", ";
                }

                query << columns[i];
            }
        }

        if (!table.empty())
        {
            query << " FROM " << table;
        }

        if (!conditions.empty())
        {
            query << " WHERE ";

            for (size_t i = 0; i < conditions.size(); ++i)
            {
                if (i > 0)
                {
                    query << " AND ";
                }

                query << conditions[i].first
                    << "="
                    << conditions[i].second;
            }
        }

        query << ";";

        return query.str();
    }
};